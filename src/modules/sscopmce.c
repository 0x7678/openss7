/*****************************************************************************

 @(#) $RCSfile: sscopmce.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-20 09:51:41 $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2011  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 -----------------------------------------------------------------------------

 Last Modified $Date: 2011-09-20 09:51:41 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: sscopmce.c,v $
 Revision 1.1.2.4  2011-09-20 09:51:41  brian
 - updates from git

 Revision 1.1.2.3  2011-09-02 08:46:56  brian
 - sync up lots of repo and build changes from git

 Revision 1.1.2.2  2010-11-28 14:22:06  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:40:35  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: sscopmce.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-20 09:51:41 $";

/*
 * This is an SSCOPE-MCE module for use with MTP3b.  It can be pushed over a UDP or IP Stream to
 * provide the SSCF interface needed by MTP3b.  For the upper interface boundary, see Q.2211
 * (SSCOPE-MCE) and NPI.  For the lower interface boundary, see NPI-UDP or TPI-UDP.
 */

#define _SVR4_SOURCE	1
#define _MPS_SOURCE	1

#include <sys/os7/compat.h>
#include <sys/strsun.h>
#include <sys/strconf.h>

#include <sys/npi.h>
#include <sys/npi_ip.h>

#define SSCOPMCE_DESCRIP	"MTP3B-SSCOPMCE STREAMS Module"
#define SSCOPMCE_EXTRA		"Part of the OpenSS7 ATM Stack for Linux Fast-STREAMS"
#define SSCOPMCE_REVISION	"OpenSS7 $RCSfile: sscopmce.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-20 09:51:41 $"
#define SSCOPMCE_COPYRIGHT	"Copyright (c) 2008-2011  Monavacon Limited.  All Rights Reserved."
#define SSCOPMCE_DEVICE		"Provides OpenSS7 MTP3B-I.432.3-SSCOPMCE module."
#define SSCOPMCE_CONTACT	"Brian Bidulock <bidulock@openss7.org>"
#define SSCOPMCE_LICENSE	"GPL"
#define SSCOPMCE_BANNER		SSCOPMCE_DESCRIP	"\n" \
				SSCOPMCE_EXTRA		"\n" \
				SSCOPMCE_REVISION	"\n" \
				SSCOPMCE_COPYRIGHT	"\n" \
				SSCOPMCE_DEVICE		"\n" \
				SSCOPMCE_CONTACT	"\n"
#define SSCOPMCE_SPLASH		SSCOPMCE_DEVICE		" - " \
				SSCOPMCE_REVISION	"\n"

#ifdef LINUX
MODULE_AUTHOR(SSCOPMCE_CONTACT);
MODULE_DESCRIPTION(SSCOPMCE_DESCRIP);
MODULE_SUPPORTED_DEVICE(SSCOPMCE_DEVICE);
#ifdef MODULE_LICENSE
MODULE_LICENSE(SSCOPMCE_LICENSE);
#endif				/* MODULE_LICENSE */
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-sscopmce");
#endif				/* MODULE_ALIAS */
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif				/* MODULE_VERSION */
#endif				/* LINUX */

#define SSCOPMCE_MOD_ID	CONFIG_STREAMS_SSCOPMCE_MODID
#define SSCOPMCE_MOD_NAME	CONFIG_STREAMS_SSCOPMCE_NAME

#define MOD_ID		SSCOPMCE_MOD_ID
#define MOD_NAME	SSCOPMCE_MOD_NAME
#ifdef MODULE
#define MOD_BANNER	SSCOPMCE_BANNER
#else				/* MODULE */
#define MOD_BANNER	SSCOPMCE_SPLASH
#endif				/* MODULE */

/*
 * PRIVATE STRUCTURE
 */

struct state {
	uint32_t state;
	uint32_t pending;
};


struct np {
	struct np *np;
	queue_t *iq;
	queue_t *oq;
	struct state state, oldstate;
	N_info_ack_t info;
	uint32_t ppa;
	mblk_t *dmsg;
	mblk_t *dlen;
};

struct priv {
	queue_t *rq;
	queue_t *wq;
	struct np npu;
	struct np npl;
};

#if	defined DEFINE_RWLOCK
static DEFINE_RWLOCK(sc_lock);
#elif	defined __RW_LOCK_UNLOCKED
static rwlock_t sc_lock = __RW_LOCK_UNLOCKED(sc_lock);
#elif	defined RW_LOCK_UNLOCKED
static rwlock_t sc_lock = RW_LOCK_UNLOCKED;
#else
#error cannot initialize read-write locks
#endif
static caddr_t sc_opens;

/*
 * PRINTING STUFF
 */
/*
 * Printing primitives
 */
static inline fastcall const char *
np_primname(const np_ulong prim)
{
	switch (prim) {
	case N_CONN_REQ:
		return ("N_CONN_REQ");
	case N_CONN_RES:
		return ("N_CONN_RES");
	case N_DISCON_REQ:
		return ("N_DISCON_REQ");
	case N_DATA_REQ:
		return ("N_DATA_REQ");
	case N_EXDATA_REQ:
		return ("N_EXDATA_REQ");
	case N_INFO_REQ:
		return ("N_INFO_REQ");
	case N_BIND_REQ:
		return ("N_BIND_REQ");
	case N_UNBIND_REQ:
		return ("N_UNBIND_REQ");
	case N_UNITDATA_REQ:
		return ("N_UNITDATA_REQ");
	case N_OPTMGMT_REQ:
		return ("N_OPTMGMT_REQ");
	case N_CONN_IND:
		return ("N_CONN_IND");
	case N_CONN_CON:
		return ("N_CONN_CON");
	case N_DISCON_IND:
		return ("N_DISCON_IND");
	case N_DATA_IND:
		return ("N_DATA_IND");
	case N_EXDATA_IND:
		return ("N_EXDATA_IND");
	case N_INFO_ACK:
		return ("N_INFO_ACK");
	case N_BIND_ACK:
		return ("N_BIND_ACK");
	case N_ERROR_ACK:
		return ("N_ERROR_ACK");
	case N_OK_ACK:
		return ("N_OK_ACK");
	case N_UNITDATA_IND:
		return ("N_UNITDATA_IND");
	case N_UDERROR_IND:
		return ("N_UDERROR_IND");
	case N_DATACK_REQ:
		return ("N_DATACK_REQ");
	case N_DATACK_IND:
		return ("N_DATACK_IND");
	case N_RESET_REQ:
		return ("N_RESET_REQ");
	case N_RESET_IND:
		return ("N_RESET_IND");
	case N_RESET_RES:
		return ("N_RESET_RES");
	case N_RESET_CON:
		return ("N_RESET_CON");
	default:
		return ("(unknown)");
	}
}

/*
 * Printing States
 */

static inline fastcall const char *
np_statename(const np_ulong state)
{
	switch (state) {
	case NS_UNBND:
		return ("NS_UNBND");
	case NS_WACK_BREQ:
		return ("NS_WACK_BREQ");
	case NS_WACK_UREQ:
		return ("NS_WACK_UREQ");
	case NS_IDLE:
		return ("NS_IDLE");
	case NS_WACK_OPTREQ:
		return ("NS_WACK_OPTREQ");
	case NS_WACK_RRES:
		return ("NS_WACK_RRES");
	case NS_WCON_CREQ:
		return ("NS_WCON_CREQ");
	case NS_WRES_CIND:
		return ("NS_WRES_CIND");
	case NS_WACK_CRES:
		return ("NS_WACK_CRES");
	case NS_DATA_XFER:
		return ("NS_DATA_XFER");
	case NS_WCON_RREQ:
		return ("NS_WCON_RREQ");
	case NS_WRES_RIND:
		return ("NS_WRES_RIND");
	case NS_WACK_DREQ6:
		return ("NS_WACK_DREQ6");
	case NS_WACK_DREQ7:
		return ("NS_WACK_DREQ7");
	case NS_WACK_DREQ9:
		return ("NS_WACK_DREQ9");
	case NS_WACK_DREQ10:
		return ("NS_WACK_DREQ10");
	case NS_WACK_DREQ11:
		return ("NS_WACK_DREQ11");
	case NS_NOSTATES:
		return ("NS_NOSTATES");
	default:
		return ("(unknown)");
	}
}

static inline fastcall const char *
np_errname(const np_long error)
{
	switch (error) {
	case NBADADDR:
		return ("NBADADDR");
	case NBADOPT:
		return ("NBADOPT");
	case NACCESS:
		return ("NACCESS");
	case NNOADDR:
		return ("NNOADDR");
	case NOUTSTATE:
		return ("NOUTSTATE");
	case NBADSEQ:
		return ("NBADSEQ");
	case NSYSERR:
		return ("NSYSERR");
	case NBADDATA:
		return ("NBADDATA");
	case NBADFLAG:
		return ("NBADFLAG");
	case NNOTSUPPORT:
		return ("NNOTSUPPORT");
	case NBOUND:
		return ("NBOUND");
	case NBADQOSPARAM:
		return ("NBADQOSPARAM");
	case NBADQOSTYPE:
		return ("NBADQOSTYPE");
	case NBADTOKEN:
		return ("NBADTOKEN");
	case NNOPROTOID:
		return ("NNOPROTOID");
	default:
		return ("(unknown)");
	}
}

static inline fastcall const char *
np_strerror(const np_ulong error)
{
	switch (error) {
	case NBADADDR:
		return ("Incorrect address format/illegal address information");
	case NBADOPT:
		return ("Options in incorrect format or contain illegal information");
	case NACCESS:
		return ("User did not have proper permissions");
	case NNOADDR:
		return ("NS Provider could not allocate address");
	case NOUTSTATE:
		return ("Primitive was issues in wrong sequence");
	case NBADSEQ:
		return ("Sequence number in primitive was incorrect/illegal");
	case NSYSERR:
		return ("UNIX system error occurred");
	case NBADDATA:
		return ("User data spec. outside range supported by NS provider");
	case NBADFLAG:
		return ("Flags specified in primitive were illegal/incorrect");
	case NNOTSUPPORT:
		return ("Primitive type not supported by the NS provider");
	case NBOUND:
		return ("Illegal second attempt to bind listener or default listener");
	case NBADQOSPARAM:
		return ("QOS values specified are outside the range supported by the NS provider");
	case NBADQOSTYPE:
		return ("QOS structure type specified is not supported by the NS provider");
	case NBADTOKEN:
		return ("Token used is not associated with an open stream");
	case NNOPROTOID:
		return ("Protocol id could not be allocated");
	default:
		return ("Unknown error");
	}
}

/*
 * STATE CHANGES
 */

static inline fastcall np_ulong
np_get_state(struct np *np)
{
	return np->state.state;
}
static inline fastcall np_ulong
np_set_state(struct np *np, const np_ulong newstate)
{
	const np_ulong oldstate = np_get_state(np);

	if (likely(oldstate != newstate)) {
		mi_strlog(np->iq, STRLOGST, SL_TRACE, "%s <- %s", np_statename(newstate),
			  np_statename(oldstate));
		np->state.state = newstate;
		np->info.CURRENT_state = newstate;
	}
	return (newstate);
}
static inline fastcall np_ulong
np_save_state(struct np *np)
{
	np->oldstate = np->state;
	return (np->state.state);
}
static inline fastcall np_ulong
np_restore_state(struct np *np)
{
	np->state = np->oldstate;
	return (np->info.CURRENT_state = np->state.state);
}
static inline fastcall np_ulong
np_set_pending(struct np *np, const np_ulong pending)
{
	return (np->state.pending = pending);
}
static inline fastcall np_ulong
np_get_pending(struct np *np)
{
	return np->state.pending;
}
static inline fastcall np_ulong
np_clear_pending(struct np *np)
{
	const np_ulong pending = np->state.pending;

	np->state.pending = -1U;
	return (pending);
}

/*
 * MESSAGE LOGGING
 */

#define STRLOGERR	0	/* log error information */
#define STRLOGNO	0	/* log notice information */
#define STRLOGST	1	/* log state transitions */
#define STRLOGTO	2	/* log timeouts */
#define STRLOGRX	3	/* log primitives received */
#define STRLOGTX	4	/* log primitives issued */
#define STRLOGTE	5	/* log timer events */
#define STRLOGIO	6	/* log additional data */
#define STRLOGDA	7	/* log data */

static inline fastcall void
sc_stripmsg(mblk_t *msg, mblk_t *dp)
{
	mblk_t *b, *b_next = msg;

	while ((b = b_next) && b != dp) {
		b_next = b->b_next;
		freeb(b);
	}
	return;
}

noinline fastcall int
np_txprim(struct np *np, queue_t *q, mblk_t *msg, mblk_t *mp, np_ulong prim)
{
	if (likely(pcmsg(DB_TYPE(mp)) || bcanputnext(np->oq, mp->b_band))) {
		int level;

		switch (__builtin_expect(prim, N_DATA_IND)) {
		case N_DATA_IND:
		case N_DATA_REQ:
			level = STRLOGDA;
			break;
		default:
			level = STRLOGTX;
			break;
		}
		mi_strlog(np->oq, level, SL_TRACE, "<- %s", np_primname(prim));
		sc_stripmsg(msg, mp->b_cont);
		putnext(np->oq, mp);
		return (0);
	}
	freeb(mp);
	return (-EBUSY);
}


noinline fastcall void
np_rxprim(struct np *np, queue_t *q, mblk_t *mp, np_ulong prim)
{
	int level;

	switch (__builtin_expect(prim, N_DATA_REQ)) {
	case N_DATA_REQ:
	case N_DATA_IND:
		level = STRLOGDA;
		break;
	default:
		level = STRLOGRX;
		break;
	}
	mi_strlog(np->iq, level, SL_TRACE, "-> %s", np_primname(prim));
	return;
}


static inline fastcall int
m_error(queue_t *q, mblk_t *msg, int rerror, int werror)
{
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, 2, BPRI_MED)))) {
		DB_TYPE(mp) = M_ERROR;
		mp->b_wptr[0] = rerror;
		mp->b_wptr[1] = werror;
		mp->b_wptr += 2;
		mi_strlog(q, STRLOGERR, SL_ERROR | SL_TRACE, "<- M_ERROR");
		freemsg(msg);
		qreply(q, mp);
		return (0);
	}
	return (-ENOBUFS);
}

/*
 * NP USER TO NP PROVIDER PRIMITIVES
 */

static inline fastcall int
n_conn_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_conn_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_CONN_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_CONN_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_conn_con(struct np *np, queue_t *q, mblk_t *msg)
{
	N_conn_con_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_CONN_CON;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_CONN_CON);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_discon_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_discon_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_DISCON_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_DISCON_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_data_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_data_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_DATA_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_DATA_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_exdata_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_exdata_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_EXDATA_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_EXDATA_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_info_ack(struct np *np, queue_t *q, mblk_t *msg)
{
	N_info_ack_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_INFO_ACK;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_INFO_ACK);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_bind_ack(struct np *np, queue_t *q, mblk_t *msg)
{
	N_bind_ack_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_BIND_ACK;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_BIND_ACK);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_error_ack(struct np *np, queue_t *q, mblk_t *msg, np_ulong prim, np_long error)
{
	N_error_ack_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_ERROR_ACK;
		p->ERROR_prim = prim;
		p->NPI_error = error < 0 ? NSYSERR : error;
		p->UNIX_error = error < 0 ? -error : 0;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_ERROR_ACK);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_reply_error(struct np *np, queue_t *q, mblk_t *msg, np_ulong prim, np_long error)
{
	switch (error) {
	case 0:
		freemsg(msg);
		return (0);
	case -EAGAIN:
	case -ENOBUFS:
	case -ENOMEM:
	case -EDEADLK:
	case -EBUSY:
		return (error);
	}
	switch (prim) {
	case N_DATA_REQ:
	case N_EXDATA_REQ:
		goto merror;
	default:
		goto errorack;
	}
      errorack:
	mi_strlog(np->iq, STRLOGERR, SL_TRACE, "ERROR: %s: (%s) %s", np_primname(prim),
		  np_errname(error), np_strerror(error));
	return n_error_ack(np, q, msg, prim, error);
      merror:
	mi_strlog(np->iq, STRLOGERR, SL_ERROR | SL_TRACE, "<- M_ERROR");
	return m_error(q, msg, EPROTO, EPROTO);
}
static inline fastcall int
n_ok_ack(struct np *np, queue_t *q, mblk_t *msg)
{
	N_ok_ack_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_OK_ACK;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_OK_ACK);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_unitdata_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_unitdata_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_UNITDATA_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_UNITDATA_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_uderror_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_uderror_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_UDERROR_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_UDERROR_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_datack_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_datack_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_DATACK_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_DATACK_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_reset_ind(struct np *np, queue_t *q, mblk_t *msg)
{
	N_reset_ind_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_RESET_IND;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_RESET_IND);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_reset_con(struct np *np, queue_t *q, mblk_t *msg)
{
	N_reset_con_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_RESET_CON;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_RESET_CON);
	}
	return (-ENOBUFS);
}

/*
 * NP USER TO NP PROVIDER PRIMITIVES
 */

static inline fastcall int
n_conn_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_conn_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_CONN_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_CONN_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_conn_res(struct np *np, queue_t *q, mblk_t *msg)
{
	N_conn_res_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_CONN_RES;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_CONN_RES);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_discon_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_discon_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_DISCON_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_DISCON_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_data_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_data_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_DATA_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_DATA_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_exdata_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_exdata_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_EXDATA_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_EXDATA_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_info_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_info_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_INFO_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_INFO_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_bind_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_bind_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_BIND_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_BIND_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_unbind_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_unbind_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_UNBIND_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_UNBIND_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_unitdata_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_unitdata_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_UNITDATA_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_UNITDATA_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_optmgmt_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_optmgmt_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_OPTMGMT_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_OPTMGMT_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_datack_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_datack_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_DATACK_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_DATACK_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_reset_req(struct np *np, queue_t *q, mblk_t *msg)
{
	N_reset_req_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_RESET_REQ;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_RESET_REQ);
	}
	return (-ENOBUFS);
}
static inline fastcall int
n_reset_res(struct np *np, queue_t *q, mblk_t *msg)
{
	N_reset_res_t *p;
	mblk_t *mp;
	static const size_t mlen = sizeof(*p);

	if (likely(!!(mp = mi_allocb(q, mlen, BPRI_MED)))) {
		DB_TYPE(mp) = M_PROTO;
		p = (typeof(p)) mp->b_wptr;
		p->PRIM_type = N_RESET_RES;
		mp->b_wptr += sizeof(*p);
		return np_txprim(np, q, msg, mp, N_RESET_RES);
	}
	return (-ENOBUFS);
}

noinline fastcall __unlikely int
np_reply_error(struct np *np, queue_t *q, mblk_t *msg, np_ulong prim, np_long error)
{
	switch (error) {
	case 0:
		freemsg(msg);
		return (0);
	case -EAGAIN:
	case -ENOBUFS:
	case -ENOMEM:
	case -EDEADLK:
	case -EBUSY:
		return (error);
	}
	mi_strlog(np->oq, STRLOGNO, SL_TRACE, "ERROR: %s: (%s) %s", np_primname(prim),
		  np_errname(error), np_strerror(error));
	freemsg(msg);
	return (0);
}

/*
 * NP USER TO NP PROVIDER PRIMITIVES
 */

noinline fastcall __unlikely int
n_w_info_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_info_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_bind_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_bind_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_unbind_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_unbind_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
static inline fastcall __hot_write int
n_write(struct np *np, queue_t *q, mblk_t *msg, mblk_t *dp)
{
	/* FIXME: for now */
	return NNOTSUPPORT;
}
noinline fastcall __unlikely int
n_w_optmgmt_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_optmgmt_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_conn_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_conn_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_conn_res(struct np *np, queue_t *q, mblk_t *mp)
{
	N_conn_res_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_discon_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_discon_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_data_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_data_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_exdata_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_exdata_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_unitdata_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_unitdata_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_datack_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_datack_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_reset_req(struct np *np, queue_t *q, mblk_t *mp)
{
	N_reset_req_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_w_reset_res(struct np *np, queue_t *q, mblk_t *mp)
{
	N_reset_res_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}

/*
 * NP PROVIDER TO NP USER PRIMITIVES
 */

noinline fastcall __unlikely int
n_r_info_ack(struct np *np, queue_t *q, mblk_t *mp)
{
	N_info_ack_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_bind_ack(struct np *np, queue_t *q, mblk_t *mp)
{
	N_bind_ack_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_error_ack(struct np *np, queue_t *q, mblk_t *mp)
{
	N_error_ack_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_ok_ack(struct np *np, queue_t *q, mblk_t *mp)
{
	N_ok_ack_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_conn_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_conn_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_conn_con(struct np *np, queue_t *q, mblk_t *mp)
{
	N_conn_con_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_discon_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_discon_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_data_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_data_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_exdata_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_exdata_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_unitdata_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_unitdata_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_uderror_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_uderror_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_datack_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_datack_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_reset_ind(struct np *np, queue_t *q, mblk_t *mp)
{
	N_reset_ind_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}
noinline fastcall __unlikely int
n_r_reset_con(struct np *np, queue_t *q, mblk_t *mp)
{
	N_reset_con_t *p = (typeof(p)) mp->b_wptr;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(*p))))
		goto tooshort;
	goto notsupport;
      notsupport:
	err = NNOTSUPPORT;
	goto error;
      tooshort:
	err = -EMSGSIZE;
	goto error;
      error:
	return (err);
}

static inline fastcall __hot_read int
n_read(struct np *np, queue_t *q, mblk_t *msg, mblk_t *dp)
{
	/* FIXME: For now */
	return NNOTSUPPORT;
}

/*
 * STREAMS MESSAGE TYPE HANDLING
 */

/**
 * np_w_data: - process received M_DATA message from above
 * @np: DL private structure (locked)
 * @q: active queue (upper write queue)
 * @mp: the M_DATA message
 */
static fastcall int
np_w_data(struct np *np, queue_t *q, mblk_t *mp)
{
	int err;

	np_save_state(np);
	err = n_write(np, q, NULL, mp);
	if (likely(err == 0))
		return (err);
	np_restore_state(np);
	return np_reply_error(np, q, mp, -1U, err);
}
static fastcall int
np_r_data(struct np *np, queue_t *q, mblk_t *mp)
{
	int err;

	np_save_state(np);
	err = n_read(np, q, NULL, mp);
	if (likely(err == 0))
		return (err);
	np_restore_state(np);
	return np_reply_error(np, q, mp, -1U, err);
}

static fastcall int
np_w_proto(struct np *np, queue_t *q, mblk_t *mp)
{
	np_ulong prim = -1U;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(prim))))
		goto tooshort;
	prim = *(typeof(prim) *) mp->b_rptr;
	np_rxprim(np, q, mp, prim);
	np_save_state(np);
	switch (prim) {
	case N_INFO_REQ:
		err = n_w_info_req(np, q, mp);
		break;
	case N_BIND_REQ:
		err = n_w_bind_req(np, q, mp);
		break;
	case N_UNBIND_REQ:
		err = n_w_unbind_req(np, q, mp);
		break;
	case N_OPTMGMT_REQ:
		err = n_w_optmgmt_req(np, q, mp);
		break;
	case N_CONN_REQ:
		err = n_w_conn_req(np, q, mp);
		break;
	case N_CONN_RES:
		err = n_w_conn_res(np, q, mp);
		break;
	case N_DISCON_REQ:
		err = n_w_discon_req(np, q, mp);
		break;
	case N_DATA_REQ:
		err = n_w_data_req(np, q, mp);
		break;
	case N_EXDATA_REQ:
		err = n_w_exdata_req(np, q, mp);
		break;
	case N_UNITDATA_REQ:
		err = n_w_unitdata_req(np, q, mp);
		break;
	case N_DATACK_REQ:
		err = n_w_datack_req(np, q, mp);
		break;
	case N_RESET_REQ:
		err = n_w_reset_req(np, q, mp);
		break;
	case N_RESET_RES:
		err = n_w_reset_res(np, q, mp);
		break;
	default:
		err = NNOTSUPPORT;
		break;
	}
	if (likely(err == 0))
		return (err);
      out:
	np_restore_state(np);
	return np_reply_error(np, q, mp, prim, err);
      tooshort:
	err = -EMSGSIZE;
	goto out;
}
static fastcall int
np_r_proto(struct np *np, queue_t *q, mblk_t *mp)
{
	np_ulong prim = -1U;
	int err;

	if (unlikely(!MBLKIN(mp, 0, sizeof(prim))))
		goto tooshort;
	prim = *(typeof(prim) *) mp->b_rptr;
	np_rxprim(np, q, mp, prim);
	np_save_state(np);
	switch (prim) {
	case N_INFO_ACK:
		err = n_r_info_ack(np, q, mp);
		break;
	case N_BIND_ACK:
		err = n_r_bind_ack(np, q, mp);
		break;
	case N_ERROR_ACK:
		err = n_r_error_ack(np, q, mp);
		break;
	case N_OK_ACK:
		err = n_r_ok_ack(np, q, mp);
		break;
	case N_CONN_IND:
		err = n_r_conn_ind(np, q, mp);
		break;
	case N_CONN_CON:
		err = n_r_conn_con(np, q, mp);
		break;
	case N_DISCON_IND:
		err = n_r_discon_ind(np, q, mp);
		break;
	case N_DATA_IND:
		err = n_r_data_ind(np, q, mp);
		break;
	case N_EXDATA_IND:
		err = n_r_exdata_ind(np, q, mp);
		break;
	case N_UNITDATA_IND:
		err = n_r_unitdata_ind(np, q, mp);
		break;
	case N_UDERROR_IND:
		err = n_r_uderror_ind(np, q, mp);
		break;
	case N_DATACK_IND:
		err = n_r_datack_ind(np, q, mp);
		break;
	case N_RESET_IND:
		err = n_r_reset_ind(np, q, mp);
		break;
	case N_RESET_CON:
		err = n_r_reset_con(np, q, mp);
		break;
	default:
		err = NNOTSUPPORT;
		break;
	}
	if (likely(err == 0))
		return (err);
      out:
	np_restore_state(np);
	return np_reply_error(np, q, mp, prim, err);
      tooshort:
	err = -EMSGSIZE;
	goto out;
}

static fastcall int
np_w_ctl(struct np *np, queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}
static fastcall int
np_r_ctl(struct np *np, queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}

static fastcall int
np_w_ioctl(struct np *np, queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}
static fastcall int
np_r_ioctl(struct np *np, queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}

static fastcall int
m_w_flush(queue_t *q, mblk_t *mp)
{
	if (mp->b_rptr[0] & FLUSHW) {
		if (mp->b_rptr[0] & FLUSHBAND)
			flushband(q, mp->b_rptr[1], FLUSHDATA);
		else
			flushq(q, FLUSHDATA);
	}
	putnext(q, mp);
	return (0);
}
static fastcall int
m_r_flush(queue_t *q, mblk_t *mp)
{
	if (mp->b_rptr[0] & FLUSHR) {
		if (mp->b_rptr[0] & FLUSHBAND)
			flushband(q, mp->b_rptr[1], FLUSHDATA);
		else
			flushq(q, FLUSHDATA);
	}
	putnext(q, mp);
	return (0);
}
static fastcall int
m_r_error(queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}

static fastcall int
m_w_other(queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}
static fastcall int
m_r_other(queue_t *q, mblk_t *mp)
{
	/* FIXME: for now */
	freemsg(mp);
	return (0);
}

/*
 * STREAMS MESSAGE HANDLING
 */

static fastcall int
np_wsrv_msg(struct np *np, queue_t *q, mblk_t *mp)
{
	switch (__builtin_expect(DB_TYPE(mp), M_DATA)) {
	case M_DATA:
	case M_HPDATA:
		return np_w_data(np, q, mp);
	case M_PROTO:
	case M_PCPROTO:
		return np_w_proto(np, q, mp);
	case M_CTL:
	case M_PCCTL:
		return np_w_ctl(np, q, mp);
	case M_IOCTL:
	case M_IOCDATA:
		return np_w_ioctl(np, q, mp);
	case M_FLUSH:
		return m_w_flush(q, mp);
	default:
		return m_w_other(q, mp);
	}
}
static fastcall int
np_rsrv_msg(struct np *np, queue_t *q, mblk_t *mp)
{
	switch (__builtin_expect(DB_TYPE(mp), M_DATA)) {
	case M_DATA:
	case M_HPDATA:
		return np_r_data(np, q, mp);
	case M_PROTO:
	case M_PCPROTO:
		return np_r_proto(np, q, mp);
	case M_CTL:
	case M_PCCTL:
		return np_r_ctl(np, q, mp);
	case M_IOCACK:
	case M_IOCNAK:
	case M_COPYIN:
	case M_COPYOUT:
		return np_r_ioctl(np, q, mp);
	case M_FLUSH:
		return m_r_flush(q, mp);
	case M_ERROR:
	case M_HANGUP:
		return m_r_error(q, mp);
	default:
		return m_r_other(q, mp);
	}
}

static fastcall int
np_wput_msg(queue_t *q, mblk_t *mp)
{
	unsigned char type;

	switch (__builtin_expect((type = DB_TYPE(mp)), M_DATA)) {
	case M_DATA:
	case M_PROTO:
	case M_CTL:
	case M_IOCTL:
		return (-EAGAIN);	/* for speed */
	case M_HPDATA:
	case M_PCPROTO:
	case M_PCCTL:
	case M_IOCDATA:
	{
		struct priv *priv;
		int err;

		if (likely(!!(priv = (typeof(priv)) mi_trylock(q)))) {
			switch (__builtin_expect(type, M_PCPROTO)) {
			case M_HPDATA:
				err = np_w_data(&priv->npu, q, mp);
				break;
			case M_PCPROTO:
				err = np_w_proto(&priv->npu, q, mp);
				break;
			case M_PCCTL:
				err = np_w_ctl(&priv->npu, q, mp);
				break;
			case M_IOCDATA:
				err = np_w_ioctl(&priv->npu, q, mp);
				break;
			default:
				err = -EFAULT;
				break;
			}
			mi_unlock((caddr_t) priv);
		} else
			err = -EDEADLK;
		return (err);
	}
	case M_FLUSH:
		return m_w_flush(q, mp);
	default:
		return m_w_other(q, mp);
	}
}
static fastcall int
np_rput_msg(queue_t *q, mblk_t *mp)
{
	unsigned char type;

	switch (__builtin_expect((type = DB_TYPE(mp)), M_DATA)) {
	case M_DATA:
	case M_PROTO:
	case M_CTL:
		return (-EAGAIN);	/* for speed */
	case M_HPDATA:
	case M_PCPROTO:
	case M_PCCTL:
	case M_IOCACK:
	case M_IOCNAK:
	case M_COPYIN:
	case M_COPYOUT:
	{
		struct priv *priv;
		int err;

		if (likely(!!(priv = (typeof(priv)) mi_trylock(q)))) {
			switch (__builtin_expect(type, M_PCPROTO)) {
			case M_HPDATA:
				err = np_r_data(&priv->npl, q, mp);
				break;
			case M_PCPROTO:
				err = np_r_proto(&priv->npl, q, mp);
				break;
			case M_PCCTL:
				err = np_r_ctl(&priv->npl, q, mp);
				break;
			case M_IOCACK:
			case M_IOCNAK:
			case M_COPYIN:
			case M_COPYOUT:
				err = np_r_ioctl(&priv->npl, q, mp);
				break;
			default:
				err = -EFAULT;
				break;
			}
			mi_unlock((caddr_t) priv);
		} else
			err = -EDEADLK;
		return (err);
	}
	case M_FLUSH:
		return m_r_flush(q, mp);
	case M_ERROR:
	case M_HANGUP:
		return m_r_error(q, mp);
	default:
		return m_r_other(q, mp);
	}
}

/*
 * QUEUE PUT AND SERVICE PROCEDURES
 */

static streamscall int
np_wput(queue_t *q, mblk_t *mp)
{
	if (unlikely((!pcmsg(DB_TYPE(mp)) && (q->q_first || (q->q_flag & QSVCBUSY)))
		     || np_wput_msg(q, mp))) {
		if (unlikely(!putq(q, mp))) {
			mp->b_band = 0;
			putq(q, mp);
		}
	}
	return (0);
}
static streamscall int
np_wsrv(queue_t *q)
{
	struct priv *priv;
	mblk_t *mp;

	if (likely(!!(priv = (typeof(priv)) mi_trylock(q)))) {
		while (likely(!!(mp = getq(q)))) {
			if (unlikely(np_wsrv_msg(&priv->npu, q, mp))) {
				if (unlikely(!putbq(q, mp))) {
					mp->b_band = 0;
					putbq(q, mp);
				}
				break;
			}
		}
		mi_unlock((caddr_t) priv);
	}
	return (0);
}
static streamscall int
np_rsrv(queue_t *q)
{
	struct priv *priv;
	mblk_t *mp;

	if (likely(!!(priv = (typeof(priv)) mi_trylock(q)))) {
		while (likely(!!(mp = getq(q)))) {
			if (unlikely(np_rsrv_msg(&priv->npl, q, mp))) {
				if (unlikely(!putbq(q, mp))) {
					mp->b_band = 0;
					putbq(q, mp);
				}
				break;
			}
		}
		mi_unlock((caddr_t) priv);
	}
	return (0);
}
static streamscall int
np_rput(queue_t *q, mblk_t *mp)
{
	if (unlikely((!pcmsg(DB_TYPE(mp)) && (q->q_first || (q->q_flag & QSVCBUSY)))
		     || np_rput_msg(q, mp))) {
		if (unlikely(!putq(q, mp))) {
			mp->b_band = 0;
			putq(q, mp);
		}
	}
	return (0);
}

/*
 * STREAMS OPEN AND CLOSE ROUTINES
 */

/**
 * sc_qopen: - STREAMS open routine
 * @q: read queue of opened (pushed) queue pair
 * @devp: pointer to device number of driver
 * @oflags: open flags
 * @sflag: STREAMS flag
 * @crp: credentials of opening (pushing) process
 */
static streamscall int
sc_qopen(queue_t *q, dev_t *devp, int oflags, int sflag, cred_t *crp)
{
	N_info_req_t *r;
	struct priv *priv;
	mblk_t *rp;
	int err;

	if (q->q_ptr)
		return (0);
	if (sflag != MODOPEN)
		return (ENXIO);
	if (unlikely(!!(rp = allocb(sizeof(*r), BPRI_WAITOK))))
		return (ENOSR);
	write_lock(&sc_lock);
	if ((err = mi_open_comm(&sc_opens, sizeof(*priv), q, devp, oflags, sflag, crp))) {
		write_unlock(&sc_lock);
		freeb(rp);
		return (err);
	}
	priv = (struct priv *) (q->q_ptr);
	bzero(priv, sizeof(*priv));
	priv->rq = RD(q);
	priv->wq = WR(q);
	priv->npu.np = &priv->npl;
	priv->npu.iq = WR(q);
	priv->npu.oq = RD(q);
	priv->npu.state.state = NS_UNBND;
	priv->npu.oldstate.state = NS_UNBND;
	priv->npu.info.PRIM_type = N_INFO_ACK;

	priv->npl.np = &priv->npu;
	priv->npl.iq = RD(q);
	priv->npl.oq = WR(q);
	priv->npl.state.state = NS_UNBND;
	priv->npl.oldstate.state = NS_UNBND;
	priv->npl.info.PRIM_type = N_INFO_ACK;

	write_unlock(&sc_lock);
	r = (typeof(r)) rp->b_wptr;
	r->PRIM_type = N_INFO_REQ;
	rp->b_wptr += sizeof(*r);
	qprocson(q);
	putnext(WR(q), rp);
	return (0);
}

static streamscall int
sc_qclose(queue_t *q, int oflags, cred_t *crp)
{
	qprocsoff(q);
	write_lock(&sc_lock);
	mi_close_comm(&sc_opens, q);
	write_unlock(&sc_lock);
	return (0);
}

static modID_t modid = MOD_ID;

#ifdef LINUX
#ifdef module_param
module_param(modid, ushort, 0444);
#else				/* module_param */
MODULE_PARM(modid, "h");
#endif				/* module_param */
MODULE_PARM_DESC(modid, "Module ID for SSCOPMCE module. (0 for allocation.)");
#endif				/* LINUX */

static struct module_info sc_minfo = {
	.mi_idnum = MOD_ID,
	.mi_idname = MOD_NAME,
	.mi_minpsz = STRMINPSZ,
	.mi_maxpsz = STRMAXPSZ,
	.mi_hiwat = STRHIGH,
	.mi_lowat = STRLOW,
};

static struct module_stat sc_rstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));
static struct module_stat sc_wstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

static struct qinit sc_rdinit = {
	.qi_putp = np_rput,
	.qi_srvp = np_rsrv,
	.qi_qopen = sc_qopen,
	.qi_qclose = sc_qclose,
	.qi_minfo = &sc_minfo,
	.qi_mstat = &sc_rstat,
};

static struct qinit sc_wrinit = {
	.qi_putp = np_wput,
	.qi_srvp = np_wsrv,
	.qi_minfo = &sc_minfo,
	.qi_mstat = &sc_wstat,
};

struct streamtab sscopmceinfo = {
	.st_rdinit = &sc_rdinit,
	.st_wrinit = &sc_wrinit,
};

static struct fmodsw sc_fmod = {
	.f_name = MOD_NAME,
	.f_str = &sscopmceinfo,
	.f_flag = D_MP,
	.f_kmod = THIS_MODULE,
};

static int __init
sscopmceinit(void)
{
	int err;

	cmn_err(CE_NOTE, MOD_BANNER);
	if ((err = register_strmod(&sc_fmod)) < 0) {
		cmn_err(CE_WARN, "%s: could not register module %d, err = %d\n", MOD_NAME,
			(int) modid, -err);
		return (err);
	}
	if (modid == 0)
		modid = err;
	return (0);
}

static int
sscopmceterminate(void)
{
	int err;

	if ((err = unregister_strmod(&sc_fmod)) < 0) {
		cmn_err(CE_WARN, "%s: could not unregister module %d, err = %d\n", MOD_NAME,
			(int) modid, -err);
		return (err);
	}
	modid = 0;
	return (0);
}

static void __exit
sscopmceexit(void)
{
	sscopmceterminate();
}

module_init(sscopmceinit);
module_exit(sscopmceexit);
