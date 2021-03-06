/*****************************************************************************

 @(#) $RCSfile: testmod.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:56 $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2012  Monavacon Limited <http://www.monavacon.com/>
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

 $Log: testmod.c,v $
 Revision 1.1.2.4  2011-09-02 08:46:56  brian
 - sync up lots of repo and build changes from git

 Revision 1.1.2.3  2011-05-31 09:46:11  brian
 - new distros

 Revision 1.1.2.2  2010-11-28 14:22:07  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:40:36  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: testmod.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:56 $";

/*
 * This is TESTMOD a STREAMS test module that provides some specialized input-output controls meant
 * for testing purposes only.  It is pushed onto another driver (such as the nuls or echo driver) to
 * perform some more specialized functions.
 */

#ifdef NEED_LINUX_AUTOCONF_H
#include NEED_LINUX_AUTOCONF_H
#endif
#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

#include <sys/kmem.h>
#include <sys/stream.h>
#include <sys/strconf.h>
#include <sys/strsubr.h>
#include <sys/ddi.h>

#include <sys/testmod.h>

#include "sys/config.h"

#define TESTMOD_DESCRIP		"SVR 4.2 Test Module for Linux Fast-STREAMS"
#define TESTMOD_EXTRA		"Part of UNIX SYSTEM V RELEASE 4.2 FAST STREAMS FOR LINUX"
#define TESTMOD_COPYRIGHT	"Copyright (c) 2008-2012  Monavacon Limited.  All Rights Reserved."
#define TESTMOD_REVISION	"LfS $RCSfile: testmod.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:56 $"
#define TESTMOD_DEVICE		"SVR 4.2 Test Module for STREAMS"
#define TESTMOD_CONTACT		"Brian Bidulock <bidulock@openss7.org>"
#define TESTMOD_LICENSE		"GPL"
#define TESTMOD_BANNER		TESTMOD_DESCRIP		"\n" \
				TESTMOD_EXTRA		"\n" \
				TESTMOD_COPYRIGHT	"\n" \
				TESTMOD_REVISION	"\n" \
				TESTMOD_DEVICE		"\n" \
				TESTMOD_CONTACT		"\n"
#define TESTMOD_SPLASH		TESTMOD_DEVICE		" - " \
				TESTMOD_REVISION	"\n"

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
MODULE_AUTHOR(TESTMOD_CONTACT);
MODULE_DESCRIPTION(TESTMOD_DESCRIP);
MODULE_SUPPORTED_DEVICE(TESTMOD_DEVICE);
MODULE_LICENSE(TESTMOD_LICENSE);
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif				/* MODULE_VERSION */
#endif				/* CONFIG_STREAMS_TESTMOD_MODULE */

#ifndef CONFIG_STREAMS_TESTMOD_NAME
#error "CONFIG_STREAMS_TESTMOD_NAME must be defined."
#endif
#ifndef CONFIG_STREAMS_TESTMOD_MODID
#error "CONFIG_STREAMS_TESTMOD_MODID must be defined."
#endif

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-testmod");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

#ifndef CONFIG_STREAMS_TESTMOD_MODULE
static
#endif
modID_t modid = CONFIG_STREAMS_TESTMOD_MODID;

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
#ifndef module_param
MODULE_PARM(modid, "h");
#else
module_param(modid, ushort, 0444);
#endif
MODULE_PARM_DESC(modid, "Module ID for TESTMOD.");
#endif				/* CONFIG_STREAMS_TESTMOD_MODULE */

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-modid-" __stringify(CONFIG_STREAMS_TESTMOD_MODID));
MODULE_ALIAS("streams-module-testmod");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

static struct module_info testmod_minfo = {
	.mi_idnum = CONFIG_STREAMS_TESTMOD_MODID,
	.mi_idname = CONFIG_STREAMS_TESTMOD_NAME,
	.mi_minpsz = STRMINPSZ,
	.mi_maxpsz = STRMAXPSZ,
	.mi_hiwat = STRHIGH,
	.mi_lowat = STRLOW,
};

static struct module_stat testmod_rstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));
static struct module_stat testmod_wstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

/* 
 *  -------------------------------------------------------------------------
 *
 *  PUT routines
 *
 *  -------------------------------------------------------------------------
 */

static streamscall int
testmod_rput(queue_t *q, mblk_t *mp)
{
	/* we don't queue so we don't need to worry about M_FLUSH */
	putnext(q, mp);
	return (0);
}

static streamscall int
testmod_wput(queue_t *q, mblk_t *mp)
{
	union ioctypes *ioc = (typeof(ioc)) mp->b_rptr;
	int err = EINVAL;
	int rval = 0;

	/* we don't queue so we don't need to worry about M_FLUSH */
	switch (mp->b_datap->db_type) {
	case M_IOCTL:
		switch (ioc->iocblk.ioc_cmd) {
		case TM_IOC_HANGUP:
			/* It is convenient to by able to synthesize an M_HANGUP message upstream
			   so that the test program can test the response of a hung up stream to
			   various system calls and input-output commands.  This ioctl accomplishes 
			   that. */
			if (putnextctl(OTHERQ(q), M_HANGUP))
				goto ack;
			err = ENOSR;
			goto nak;
		case TM_IOC_RDERR:
		{
			int rwerr;

			rwerr = *(unsigned long *) mp->b_cont->b_rptr;
			/* Synthesize a M_ERROR message with a read error (equal to the arg) */
			if (putnextctl2(OTHERQ(q), M_ERROR, rwerr, NOERROR))
				goto ack;
			err = ENOSR;
			goto nak;
		}
		case TM_IOC_WRERR:
		{
			int rwerr;

			rwerr = *(unsigned long *) mp->b_cont->b_rptr;
			/* Synthesize a M_ERROR message with a write error (equal to the arg) */
			if (putnextctl2(OTHERQ(q), M_ERROR, NOERROR, rwerr))
				goto ack;
			err = ENOSR;
			goto nak;
		}
		case TM_IOC_RWERR:
		{
			int rwerr;

			rwerr = *(unsigned long *) mp->b_cont->b_rptr;
			/* Synthesize a M_ERROR message with an error (equal to the arg) */
			if (putnextctl1(OTHERQ(q), M_ERROR, rwerr))
				goto ack;
			err = ENOSR;
			goto nak;
		}
		case TM_IOC_PSIGNAL:
		{
			int signum;

			signum = *(unsigned long *) mp->b_cont->b_rptr;
			/* Synthesize an M_SIG message with a signal (equal to the arg) */
			if (putnextctl1(OTHERQ(q), M_PCSIG, signum))
				goto ack;
			err = ENOSR;
			goto nak;
		}
		case TM_IOC_NSIGNAL:
		{
			int signum;

			signum = *(unsigned long *) mp->b_cont->b_rptr;
			/* Synthesize an M_SIG message with a signal (equal to the arg) */
			if (putnextctl1(OTHERQ(q), M_SIG, signum))
				goto ack;
			err = ENOSR;
			goto nak;
		}
		case TM_IOC_COPYIN:
		{
			caddr_t uaddr;

			if (ioc->iocblk.ioc_count != TRANSPARENT || mp->b_cont == NULL
			    || mp->b_cont->b_datap->db_lim - mp->b_cont->b_datap->db_base <
			    FASTBUF) {
				err = EINVAL;
				goto nak;
			}
#if defined __LP64__
			if (ioc->iocblk.ioc_flag == IOC_ILP32)
				uaddr = (caddr_t) (unsigned long) (uint32_t)
				    *(unsigned long *) mp->b_cont->b_rptr;
			else
#endif				/* defined __LP64__ */
				uaddr = (caddr_t) *(unsigned long *) mp->b_cont->b_rptr;
			mp->b_cont->b_wptr = mp->b_cont->b_rptr + FASTBUF;
			memset(mp->b_cont->b_rptr, 0xa5, FASTBUF);

			mp->b_datap->db_type = M_COPYIN;
			ioc->copyreq.cq_addr = uaddr;
			ioc->copyreq.cq_size = FASTBUF;
			ioc->copyreq.cq_flag = 0;
			ioc->copyreq.cq_private = NULL;
			goto reply;
		}
		case TM_IOC_COPYOUT:
		{
			caddr_t uaddr;

			if (ioc->iocblk.ioc_count != TRANSPARENT || mp->b_cont == NULL
			    || mp->b_cont->b_datap->db_lim - mp->b_cont->b_rptr < FASTBUF) {
				err = EINVAL;
				goto nak;
			}
#if defined __LP64__
			if (ioc->iocblk.ioc_flag == IOC_ILP32)
				uaddr = (caddr_t) (unsigned long) (uint32_t)
				    *(unsigned long *) mp->b_cont->b_rptr;
			else
#endif				/* defined __LP64__ */
				uaddr = (caddr_t) *(unsigned long *) mp->b_cont->b_rptr;
			mp->b_cont->b_wptr = mp->b_cont->b_rptr + FASTBUF;
			memset(mp->b_cont->b_rptr, 0xa5, FASTBUF);

			mp->b_datap->db_type = M_COPYOUT;
			ioc->copyreq.cq_addr = uaddr;
			ioc->copyreq.cq_size = FASTBUF;
			ioc->copyreq.cq_flag = 0;
			ioc->copyreq.cq_private = NULL;
			goto reply;
		}
		case TM_IOC_IOCTL:
		{
			if (ioc->iocblk.ioc_count == TRANSPARENT) {
				err = EINVAL;
				goto nak;
			}
			if (mp->b_cont == NULL
			    || mp->b_cont->b_wptr - mp->b_cont->b_rptr != ioc->iocblk.ioc_count) {
				err = EINVAL;
				goto nak;
			}
			memset(mp->b_cont->b_rptr, 0xa5, ioc->iocblk.ioc_count);
			mp->b_datap->db_type = M_IOCACK;
			ioc->iocblk.ioc_rval = 0;
			ioc->iocblk.ioc_error = 0;
			goto reply;
		}
		case TM_IOC_COPYIO:
		{
			caddr_t uaddr;

			if (ioc->iocblk.ioc_count != TRANSPARENT || mp->b_cont == NULL
			    || mp->b_cont->b_datap->db_lim - mp->b_cont->b_datap->db_base <
			    FASTBUF) {
				err = EINVAL;
				goto nak;
			}
#if defined __LP64__
			if (ioc->iocblk.ioc_flag == IOC_ILP32)
				uaddr = (caddr_t) (unsigned long) (uint32_t)
				    *(unsigned long *) mp->b_cont->b_rptr;
			else
#endif				/* defined __LP64__ */
				uaddr = (caddr_t) *(unsigned long *) mp->b_cont->b_rptr;
			mp->b_cont->b_wptr = mp->b_cont->b_rptr + FASTBUF;
			memset(mp->b_cont->b_rptr, 0xa5, FASTBUF);

			mp->b_datap->db_type = M_COPYIN;
			ioc->copyreq.cq_addr = uaddr;
			ioc->copyreq.cq_size = FASTBUF;
			ioc->copyreq.cq_flag = 0;
			ioc->copyreq.cq_private = (mblk_t *) uaddr;
			goto reply;
		}
		default:
			/* pass along anything we don't understand */
			break;
		}
		break;
	case M_IOCDATA:
		switch (ioc->copyresp.cp_cmd) {
		case TM_IOC_HANGUP:
		case TM_IOC_RDERR:
		case TM_IOC_WRERR:
		case TM_IOC_RWERR:
		case TM_IOC_PSIGNAL:
		case TM_IOC_NSIGNAL:
			if (ioc->copyresp.cp_rval != NULL)
				/* abort operations */
				goto free_it;
			break;
		case TM_IOC_COPYIN:
		{
			int i;

			if (ioc->copyresp.cp_rval != NULL)
				/* abort operations */
				goto free_it;
			if (!mp->b_cont || mp->b_cont->b_wptr - mp->b_cont->b_rptr != FASTBUF) {
				err = EINVAL;
				goto nak;
			}
			for (i = 0; i < FASTBUF; i++)
				if ((unsigned char) mp->b_cont->b_rptr[i] != (unsigned char) 0xa5)
					break;
			if (i == FASTBUF) {
				err = EINVAL;
				goto nak;
			}
			rval = 0;
			goto ack;
		}
		case TM_IOC_COPYOUT:
		{
			if (ioc->copyresp.cp_rval != NULL)
				/* abort operations */
				goto free_it;
			rval = 0;
			goto ack;
		}
		case TM_IOC_COPYIO:
		{
			int i;

			if (ioc->copyresp.cp_rval != NULL)
				/* abort operations */
				goto free_it;
			if (ioc->copyresp.cp_private != NULL) {
				if (!mp->b_cont
				    || mp->b_cont->b_wptr - mp->b_cont->b_rptr != FASTBUF) {
					err = EINVAL;
					goto nak;
				}
				for (i = 0; i < FASTBUF; i++)
					if ((unsigned char) mp->b_cont->b_rptr[i] !=
					    (unsigned char) 0xa5)
						break;
				if (i == FASTBUF) {
					err = EINVAL;
					goto nak;
				}
				memset(mp->b_cont->b_rptr, 0xa5, FASTBUF);

				mp->b_datap->db_type = M_COPYOUT;
				ioc->copyreq.cq_addr = (caddr_t) ioc->copyreq.cq_private;
				ioc->copyreq.cq_flag = 0;
				ioc->copyreq.cq_private = NULL;
				goto reply;
			}
			rval = 0;
			goto ack;
		}
		default:
			/* pass along anything we don't understand */
			break;
		}
		break;
	      ack:
		mp->b_datap->db_type = M_IOCACK;
		ioc->iocblk.ioc_count = 0;
		ioc->iocblk.ioc_rval = rval;
		ioc->iocblk.ioc_error = 0;
		goto reply;
	      nak:
		mp->b_datap->db_type = M_IOCNAK;
		ioc->iocblk.ioc_count = 0;
		ioc->iocblk.ioc_rval = -1;
		ioc->iocblk.ioc_error = err;
		goto reply;
	}
	putnext(q, mp);
	return (0);
      free_it:
	freemsg(mp);
	return (0);
      reply:
	qreply(q, mp);
	return (0);
}

/* 
 *  -------------------------------------------------------------------------
 *
 *  OPEN and CLOSE
 *
 *  -------------------------------------------------------------------------
 */
static streamscall int
testmod_open(queue_t *q, dev_t *devp, int oflag, int sflag, cred_t *crp)
{
	queue_t *wq;

	if (q->q_ptr != NULL) {
		return (0);	/* already open */
	}
	wq = WR(q);
	if (sflag == MODOPEN || wq->q_next != NULL) {
		/* inherit packet sizes of what we are pushed over */
		wq->q_minpsz = wq->q_next->q_minpsz;
		wq->q_maxpsz = wq->q_next->q_maxpsz;
		q->q_ptr = wq->q_ptr = q;	/* just set it to something */
		qprocson(q);
		return (0);
	}
	return (EIO);		/* can't be opened as driver */
}
static streamscall int
testmod_close(queue_t *q, int oflag, cred_t *crp)
{
	(void) oflag;
	(void) crp;
	if (!q->q_ptr)
		return (ENXIO);
	qprocsoff(q);
	q->q_ptr = WR(q)->q_ptr = NULL;
	return (0);
}

/* 
 *  -------------------------------------------------------------------------
 *
 *  Registration and initialization
 *
 *  -------------------------------------------------------------------------
 */
static struct qinit testmod_rinit = {
	.qi_putp = testmod_rput,
	.qi_qopen = testmod_open,
	.qi_qclose = testmod_close,
	.qi_minfo = &testmod_minfo,
	.qi_mstat = &testmod_rstat,
};

static struct qinit testmod_winit = {
	.qi_putp = testmod_wput,
	.qi_minfo = &testmod_minfo,
	.qi_mstat = &testmod_wstat,
};

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
static
#endif
struct streamtab testmodinfo = {
	.st_rdinit = &testmod_rinit,
	.st_wrinit = &testmod_winit,
};

static struct fmodsw testmod_fmod = {
	.f_name = CONFIG_STREAMS_TESTMOD_NAME,
	.f_str = &testmodinfo,
	.f_flag = D_MP,
	.f_kmod = THIS_MODULE,
};

struct tm_ioctl {
	unsigned int cmd;
	void *opaque;
};

static struct tm_ioctl tm_map[] = {
	{.cmd = TM_IOC_HANGUP,}
	, {.cmd = TM_IOC_RDERR,}
	, {.cmd = TM_IOC_WRERR,}
	, {.cmd = TM_IOC_RWERR,}
	, {.cmd = TM_IOC_PSIGNAL,}
	, {.cmd = TM_IOC_NSIGNAL,}
	, {.cmd = TM_IOC_IOCTL,}
	, {.cmd = TM_IOC_COPYIN,}
	, {.cmd = TM_IOC_COPYOUT,}
	, {.cmd = TM_IOC_COPYIO,}
	, {.cmd = 0,}
};

static void
tm_unregister_ioctl32(void)
{
	struct tm_ioctl *i;

	for (i = tm_map; i->cmd != 0; i++)
		if (i->opaque != NULL)
			unregister_ioctl32(i->opaque);
}
static int
tm_register_ioctl32(void)
{
	struct tm_ioctl *i;

	for (i = tm_map; i->cmd != 0; i++) {
		if ((i->opaque = register_ioctl32(i->cmd)) == NULL) {
			tm_unregister_ioctl32();
			return (-ENOMEM);
		}
	}
	return (0);
}

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
static
#endif
int __init
testmodinit(void)
{
	int err;

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
	printk(KERN_INFO TESTMOD_BANNER);
#else
	printk(KERN_INFO TESTMOD_SPLASH);
#endif
	testmod_minfo.mi_idnum = modid;
	if ((err = tm_register_ioctl32()) < 0)
		return (err);
	if ((err = register_strmod(&testmod_fmod)) < 0) {
		tm_unregister_ioctl32();
		return (err);
	}
	if (modid == 0 && err > 0)
		modid = err;
	return (0);
};

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
static
#endif
void __exit
testmodexit(void)
{
	unregister_strmod(&testmod_fmod);
	tm_unregister_ioctl32();
};

#ifdef CONFIG_STREAMS_TESTMOD_MODULE
module_init(testmodinit);
module_exit(testmodexit);
#endif
