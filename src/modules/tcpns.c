/*****************************************************************************

 @(#) $RCSfile: tcpns.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:56 $

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

 Last Modified $Date: 2011-09-02 08:46:56 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: tcpns.c,v $
 Revision 1.1.2.4  2011-09-02 08:46:56  brian
 - sync up lots of repo and build changes from git

 Revision 1.1.2.3  2010-11-28 14:22:07  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.2  2009-06-29 07:35:46  brian
 - SVR 4.2 => SVR 4.2 MP

 Revision 1.1.2.1  2009-06-21 11:40:36  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: tcpns.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:56 $";


/*
 *  ISO Transport over TCP/IP (ISOT)
 *
 *  ISOT implements ISO Transport Protocol Class 0 (TP0) over TCP/IP in
 *  accordance with RFC 1006.  This module implements the lower layer protocol
 *  module that converts TCP to a specialized NS-Provider.  This module
 *  presents an NPI interface to an upper layer module that implements the
 *  modified ISO Transport Protocol.
 *
 *  This module is meant to be pushed over a TCP Transport Provider Interface
 *  (TPI) stream and then an "isot" module pushed over this one to provide an
 *  ISO TPI interface to the TS-User.
 */

#include <sys/os7/compat.h>

/*
 * These are for TPI definitions.
 */
#if defined HAVE_TIDHR_H
#   include <tihdr.h>
#else
#   include <sys/tihdr.h>
#endif

#include <sys/npi.h>
#include <net/sock.h>
#include <net/ip.h>

#define TCPNS_DESCRIP	"RFC 1006/2126 ISOT/ITOT NS (TCPNS) STREAMS Module"
#define TCPNS_EXTRA	"Part of the OpenSS7 OSI Stack for Linux Fast-STREAMS"
#define TCPNS_COPYRIGHT	"Copyright (c) 2008-2011  Monavacon Limited.  All Rights Reserved."
#define TCPNS_REVISION	"OpenSS7 $RCSfile: tcpns.c,v $ $Name:  $ ($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:56 $"
#define TCPNS_DEVICE	"SVR 4.2 MP STREAMS NS Module for RFC 1006/2126 ISOT/ITOT"
#define TCPNS_CONTACT	"Brian Bidulock <bidulock@openss7.org>"
#define TCPNS_LICENSE	"GPL"
#define TCPNS_BANNER	TCPNS_DESCRIP	"\n" \
			TCPNS_EXTRA	"\n" \
			TCPNS_COPYRIGHT	"\n" \
			TCPNS_REVISION	"\n" \
			TCPNS_DEVICE	"\n" \
			TCPNS_CONTACT
#define TCPNS_SPLASH	TCPNS_DEVICE	" - " \
			TCPNS_REVISION

#ifdef LINUX
MODULE_AUTHOR(TCPNS_CONTACT);
MODULE_DESCRIPTION(TCPNS_DESCRIP);
MODULE_SUPPORTED_DEVICE(TCPNS_DEVICE);
#ifdef MODULE_LICENSE
MODULE_LICENSE(TCPNS_LICENSE);
#endif				/* MODULE_LICENSE */
#if defined MODULE_ALIAS
MODULE_ALIAS("streams-tcpns");
#endif
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif
#endif				/* LINUX */

#ifndef TCPNS_MOD_NAME
#define TCPNS_MOD_NAME		"tcpns"
#endif

#ifndef TCPNS_MOD_ID
#define TCPNS_MOD_ID		0
#endif

/*
 *  =========================================================================
 *
 *  STREAMS Definitions
 *
 *  =========================================================================
 */

#define MOD_ID		TCPNS_MOD_ID
#define MOD_NAME	TCPNS_MOD_NAME
#ifdef MODULE
#define MOD_BANNER	TCPNS_BANNER
#else				/* MODULE */
#define MOD_BANNER	TCPNS_SPLASH
#endif				/* MODULE */

static struct module_info tcpns_minfo = {
	.mi_idnum = MOD_ID,		/* Module ID number */
	.mi_idname = MOD_NAME,		/* Module name */
	.mi_minpsz = 0,			/* Min packet size accepted */
	.mi_maxpsz = INFPSZ,		/* Max packet size accepted */
	.mi_hiwat = 1,			/* Hi water mark */
	.mi_lowat = 0,			/* Lo water mark */
};

static struct module_stat tcpns_rstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));
static struct module_stat tcpns_wstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

static streamscall int tcpns_open(queue_t *, dev_t *, int, int, cred_t *);
static streamscall int tcpns_close(queue_t *, int, cred_t *);

static streamscall int tcpns_rput(queue_t *, mblk_t *);
static streamscall int tcpns_wput(queue_t *, mblk_t *);

static struct qinit tcpns_rinit = {
	.qi_putp = tcpns_rput,		/* Read put (message from below) */
	.qi_qopen = tcpns_open,		/* Each open */
	.qi_qclose = tcpns_close,	/* Last close */
	.qi_minfo = &tcpns_minfo,	/* Information */
	.qi_mstat = &tcpns_rstat,	/* Statistics */
};

static struct qinit tcpns_winit = {
	.qi_putp = tcpns_wput,		/* Write put (message from above) */
	.qi_minfo = &tcpns_minfo,	/* Information */
	.qi_mstat = &tcpns_wstat,	/* Statistics */
};

MODULE_STATIC struct streamtab tcpnsinfo = {
	.st_rdinit = &tcpns_rinit,	/* Upper read queue */
	.st_wrinit = &tcpns_winit,	/* Upper write queue */
};

/*
 *  -------------------------------------------------------------------------
 *
 *  Private Datastructure ctors and dtors
 *  
 *  -------------------------------------------------------------------------
 */
struct tcpns {
	queue_t *rq;			/* module read queue */
	queue_t *wq;			/* module write queue */
	queue_t *hq;			/* stream head read queue */
	ulong state;			/* module state */
	ulong oldstate;			/* module state */
	ulong flags;			/* module flags */
	mblk_t *iocblk;			/* ioctl being processed */
	ulong qlen;			/* bind ack queue length */
	ulong cons;			/* outstanding connection indications */
};

static kmem_cachep_t tcpns_priv_cachep = NULL;

static int
tcpns_init_caches(void)
{
	if (!tcpns_priv_cachep
	    && !(tcpns_priv_cachep =
		 kmem_create_cache(MOD_NAME, sizeof(struct tcpns), 0, SLAB_HWCACHE_ALIGN, NULL, NULL)
		 )) {
		cmn_err(CE_WARN, "%s: %s: Cannot allocate tcpns_priv_cachep", MOD_NAME,
			__FUNCTION__);
		return (-ENOMEM);
	}
	return (0);
}

static int
tcpns_term_caches(void)
{
	if (tcpns_priv_cachep) {
#ifdef HAVE_KTYPE_KMEM_CACHE_T_P
		if (kmem_cache_destroy(tcpns_priv_cachep)) {
			cmn_err(CE_WARN, "%s: %s: did not destroy tcpns_priv_cachep", MOD_NAME,
				__FUNCTION__);
			return (-EBUSY);
		}
#else
		kmem_cache_destroy(tcpns_priv_cachep);
#endif
	}
	return (0);
}

static struct tcpns *
tcpns_alloc_priv(queue_t *q)
{
	struct tcpns *priv;

	if ((priv = kmem_cache_alloc(tcpns_priv_cachep, GFP_ATOMIC))) {
		bzero(priv, sizeof(*priv));
		priv->rq = q;
		priv->wq = WR(q);
		priv->hq = q->q_next;
		priv->state = TS_UNBND;	/* assume we are in the correct initial state */
		priv->oldstate = -1UL;
		priv->flags = 0;
		priv->qlen = 0;
		priv->cons = 0;
		/* we are a module with no service routine so our hiwat, lowat shouldn't matter;
		   however, our minpsz, maxpsz do because we are the first queue under the stream
		   head.  We do not want to alter the characteristics of the transport packet sizes
		   so we copy them here. This will allow the stream head to exhibit the same
		   behaviour as before we were pushed. */
		priv->wq->q_minpsz = priv->wq->q_next->q_minpsz;
		priv->wq->q_maxpsz = priv->wq->q_next->q_maxpsz;
		/* Note that qprocson has not been called so we do not have to freeze the stream to 
		   set these values. */
		q->q_ptr = WR(q)->q_ptr = priv;
	}
	return (priv);
}

static void
tcpns_free_priv(queue_t *q)
{
	struct tcpns *priv;

	if ((priv = (typeof(priv)) q->q_ptr)) {
		q->q_ptr = WR(q)->q_ptr = NULL;
		priv->rq = NULL;
		priv->wq = NULL;
		priv->hq = NULL;
		priv->state = -1UL;
		priv->oldstate = -1UL;
		priv->flags = 0;
		priv->qlen = 0;
		priv->cons = 0;
		if (priv->iocblk)
			freemsg(xchg(&priv->iocblk, NULL));
		kmem_cache_free(tcpns_priv_cachep, priv);
	}
	return;
}

/*
 *  -------------------------------------------------------------------------
 *
 *  PUT routine
 *  
 *  -------------------------------------------------------------------------
 */

static streamscall int
tcpns_rput(queue_t *q, mblk_t *mp)
{
	// struct tcpns *priv = q->q_ptr;

	switch (mp->b_datap->db_type) {
	case M_PROTO:
	case M_PCPROTO:
	{
		union T_primitives *p = (union T_primitives *) mp->b_rptr;

		if (mp->b_wptr < mp->b_rptr + sizeof(p->type))
			goto fault;
		switch (p->type) {
		case T_CONN_IND:
		{
			struct T_conn_ind tpi;
			struct sockaddr_in sin;
			N_conn_ind_t *n;

			bcopy(mp->b_rptr, &tpi, sizeof(tpi));
			bcopy(mp->b_rptr + tpi.SRC_offset, &sin, tpi.SRC_length);
			n = (N_conn_ind_t *) mp->b_rptr;
			mp->b_wptr = mp->b_rptr;
			n->PRIM_type = N_CONN_IND;
			n->SRC_length = tpi.SRC_length;
			n->SRC_offset = (tpi.SRC_length > 0 ? sizeof(*n) : 0);
			/* TCP does not provide destination address (unless we pull it out of the
			   options).  TODO: pull destination address out of the options. */
			n->DEST_length = 0;
			n->DEST_offset = 0;
			n->SEQ_number = tpi.SEQ_number;
			/* RFC 1006 says to discard options, but we could fill out QOS parameters
			   somehow... */
			n->CONN_flags = 0;
			n->QOS_length = 0;
			n->QOS_offset = 0;
			mp->b_wptr += sizeof(*n);
			if (n->SRC_length > 0) {
				bcopy(&sin, mp->b_wptr, n->SRC_length);
				mp->b_wptr += n->SRC_length;
			}
			putnext(q, mp);
			return (0);
		}
		case T_CONN_CON:
		{
			struct T_conn_con tpi;
			struct sockaddr_in sin;
			N_conn_con_t *n;

			bcopy(mp->b_rptr, &tpi, sizeof(tpi));
			bcopy(mp->b_rptr + tpi.RES_offset, &sin, tpi.RES_length);
			n = (N_conn_con_t *) mp->b_rptr;
			mp->b_wptr = mp->b_rptr;
			n->PRIM_type = N_CONN_CON;
			n->RES_length = tpi.RES_length;
			n->RES_offset = tpi.RES_offset;
			/* RFC 1006 says to discard options, but we could fill out QOS parameters
			   somehow... */
			n->CONN_flags = 0;
			n->QOS_length = 0;
			n->QOS_offset = 0;
			mp->b_wptr += sizeof(*n);
			if (n->RES_length > 0) {
				bcopy(&sin, mp->b_wptr, n->RES_length);
				mp->b_wptr += n->RES_length;
			}
			putnext(q, mp);
			return (0);
		}
		case T_DATA_IND:
		{
		}
		case T_EXDATA_IND:
		{
		}
		case T_DISCON_IND:
		{
		}
		case T_ORDREL_IND:
		{
		}
		default:
		{
		}
		}
	}
	case M_DATA:
	{
	}
	default:
		putnext(q, mp);
		return (0);
	}
      fault:
	swerr();
	return (0);
}

static streamscall int
tcpns_wput(queue_t *q, mblk_t *mp)
{
	return (0);
}

static streamscall int
tcpns_open(queue_t *q, dev_t *devp, int flag, int sflag, cred_t *crp)
{
	int err = 0;

	if (q->q_ptr != NULL)
		goto quit;	/* already open */
	err = ENXIO;
	if (sflag != MODOPEN || WR(q)->q_next == NULL)
		goto quit;
	err = ENOMEM;
	if (!(tcpns_alloc_priv(q)))
		goto quit;
	qprocson(q);
	return (0);
      quit:
	return (err);
}

/*
 *  Open and Close
 */
static streamscall int
tcpns_close(queue_t *q, int oflag, cred_t *crp)
{
	(void) oflag;
	(void) crp;
	qprocsoff(q);
	tcpns_free_priv(q);
	return (0);
}

/*
 *  Registration and initialization
 */
#ifdef LINUX
/*
 *  Linux registration
 */
unsigned short modid = MOD_ID;

#ifndef module_param
MODULE_PARM(modid, "h");
#else
module_param(modid, ushort, 0444);
#endif
MODULE_PARM_DESC(modid, "Module ID for TCPNS module. (0 for allocation.)");

/*
 *  Linux Fast-STREAMS Registration
 */
STATIC struct fmodsw tcpns_fmod = {
	.f_name = MOD_NAME,
	.f_str = &tcpnsinfo,
	.f_flag = D_MP,
	.f_kmod = THIS_MODULE,
};

STATIC __unlikely int
tcpns_register_strmod(void)
{
	int err;

	if ((err = register_strmod(&tcpns_fmod)) < 0)
		return (err);
	return (0);
}

STATIC __unlikely int
tcpns_unregister_strmod(void)
{
	int err;

	if ((err = unregister_strmod(&tcpns_fmod)) < 0)
		return (err);
	return (0);
}

MODULE_STATIC int __init
tcpnsinit(void)
{
	int err;

	cmn_err(CE_NOTE, MOD_BANNER);
	if ((err = tcpns_init_caches())) {
		cmn_err(CE_WARN, "%s: could nod init caches, err = %d", MOD_NAME, err);
		return (err);
	}
	if ((err = tcpns_register_strmod())) {
		cmn_err(CE_WARN, "%s: could not regsiter module, err = %d", MOD_NAME, err);
		tcpns_term_caches();
		return (err);
	}
	if (modid == 0)
		modid = err;
	return (0);
}

MODULE_STATIC void __exit
tcpnsterminate(void)
{
	int err;

	if ((err = tcpns_unregister_strmod()))
		cmn_err(CE_WARN, "%s: could not unregister module", MOD_NAME);
	if ((err = tcpns_term_caches()))
		cmn_err(CE_WARN, "%s: could not terminate caches", MOD_NAME);
	return;
}

/*
 *  Linux Kernel Module Initialization
 */
module_init(tcpnsinit);
module_exit(tcpnsterminate);

#endif				/* LINUX */
