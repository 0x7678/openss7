/*****************************************************************************

 @(#) $RCSfile: pipemod.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:54 $

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

 Last Modified $Date: 2011-09-02 08:46:54 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: pipemod.c,v $
 Revision 1.1.2.4  2011-09-02 08:46:54  brian
 - sync up lots of repo and build changes from git

 Revision 1.1.2.3  2011-05-31 09:46:11  brian
 - new distros

 Revision 1.1.2.2  2010-11-28 14:22:04  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:40:33  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: pipemod.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:54 $";

/* 
 *  This is PIPEMOD a STREAMS-based pipe (s_pipe(3)) module that reverses the
 *  send of the M_FLUSH message.  It is pushed on one side of STREAMS-based
 *  pipes.
 *
 *  This is an absurdly simple module.
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

#include "sys/config.h"

#define PIPEMOD_DESCRIP		"SVR 4.2 Pipe Module (PIPEMOD) STREAMS Module"
#define PIPEMOD_EXTRA		"Part of UNIX SYSTEM V RELEASE 4.2 FAST STREAMS FOR LINUX"
#define PIPEMOD_COPYRIGHT	"Copyright (c) 2008-2012  Monavacon Limited.  All Rights Reserved."
#define PIPEMOD_REVISION	"LfS $RCSfile: pipemod.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-09-02 08:46:54 $"
#define PIPEMOD_DEVICE		"SVR 4.2 Pipe Module for STREAMS-based Pipes"
#define PIPEMOD_CONTACT		"Brian Bidulock <bidulock@openss7.org>"
#define PIPEMOD_LICENSE		"GPL"
#define PIPEMOD_BANNER		PIPEMOD_DESCRIP		"\n" \
				PIPEMOD_EXTRA		"\n" \
				PIPEMOD_COPYRIGHT	"\n" \
				PIPEMOD_REVISION	"\n" \
				PIPEMOD_DEVICE		"\n" \
				PIPEMOD_CONTACT		"\n"
#define PIPEMOD_SPLASH		PIPEMOD_DEVICE		" - " \
				PIPEMOD_REVISION	"\n"

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
MODULE_AUTHOR(PIPEMOD_CONTACT);
MODULE_DESCRIPTION(PIPEMOD_DESCRIP);
MODULE_SUPPORTED_DEVICE(PIPEMOD_DEVICE);
MODULE_LICENSE(PIPEMOD_LICENSE);
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif				/* MODULE_VERSION */
#endif				/* CONFIG_STREAMS_PIPEMOD_MODULE */

#ifndef CONFIG_STREAMS_PIPEMOD_NAME
//#define CONFIG_STREAMS_PIPEMOD_NAME "pipemod"
#error "CONFIG_STREAMS_PIPEMOD_NAME must be defined."
#endif
#ifndef CONFIG_STREAMS_PIPEMOD_MODID
//#define CONFIG_STREAMS_PIPEMOD_MODID 13
#error "CONFIG_STREAMS_PIPEMOD_MODID must be defined."
#endif

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-pipemod");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

#ifndef CONFIG_STREAMS_PIPEMOD_MODULE
static
#endif
modID_t modid = CONFIG_STREAMS_PIPEMOD_MODID;

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
#ifndef module_param
MODULE_PARM(modid, "h");
#else
module_param(modid, ushort, 0444);
#endif
MODULE_PARM_DESC(modid, "Module ID for PIPEMOD.");
#endif				/* CONFIG_STREAMS_PIPEMOD_MODULE */

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-modid-" __stringify(CONFIG_STREAMS_PIPEMOD_MODID));
MODULE_ALIAS("streams-module-pipemod");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

static struct module_info pipemod_minfo = {
	.mi_idnum = CONFIG_STREAMS_PIPEMOD_MODID,
	.mi_idname = CONFIG_STREAMS_PIPEMOD_NAME,
	.mi_minpsz = STRMINPSZ,
	.mi_maxpsz = STRMAXPSZ,
	.mi_hiwat = STRHIGH,
	.mi_lowat = STRLOW,
};

static struct module_stat pipemod_mstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

/* 
 *  -------------------------------------------------------------------------
 *
 *  PUT routines
 *
 *  -------------------------------------------------------------------------
 */

static streamscall int
pipemod_put(queue_t *q, mblk_t *mp)
{
	if (unlikely(mp->b_datap->db_type == M_FLUSH)) {
		switch (mp->b_rptr[0] & (FLUSHR | FLUSHW)) {
		case FLUSHR:
			mp->b_rptr[0] &= ~FLUSHR;
			mp->b_rptr[0] |= FLUSHW;
			break;
		case FLUSHW:
			mp->b_rptr[0] &= ~FLUSHW;
			mp->b_rptr[0] |= FLUSHR;
			break;
		}
	}
	putnext(q, mp);
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
pipemod_open(queue_t *q, dev_t *devp, int oflag, int sflag, cred_t *crp)
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
pipemod_close(queue_t *q, int oflag, cred_t *crp)
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
static struct qinit pipemod_qinit = {
	.qi_putp = pipemod_put,
	.qi_qopen = pipemod_open,
	.qi_qclose = pipemod_close,
	.qi_minfo = &pipemod_minfo,
	.qi_mstat = &pipemod_mstat,
};

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
static
#endif
struct streamtab pipemodinfo = {
	.st_rdinit = &pipemod_qinit,
	.st_wrinit = &pipemod_qinit,
};

static struct fmodsw pipemod_fmod = {
	.f_name = CONFIG_STREAMS_PIPEMOD_NAME,
	.f_str = &pipemodinfo,
	.f_flag = D_MP,
	.f_kmod = THIS_MODULE,
};

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
static
#endif
int __init
pipemodinit(void)
{
	int err;

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
	printk(KERN_INFO PIPEMOD_BANNER);
#else
	printk(KERN_INFO PIPEMOD_SPLASH);
#endif
	pipemod_minfo.mi_idnum = modid;
	if ((err = register_strmod(&pipemod_fmod)) < 0)
		return (err);
	if (modid == 0 && err > 0)
		modid = err;
	return (0);
};

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
static
#endif
void __exit
pipemodexit(void)
{
	int err;

	if ((err = unregister_strmod(&pipemod_fmod)) < 0)
		return (void) (err);
	return (void) (0);
};

#ifdef CONFIG_STREAMS_PIPEMOD_MODULE
module_init(pipemodinit);
module_exit(pipemodexit);
#endif
