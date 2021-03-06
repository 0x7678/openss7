/*****************************************************************************

 @(#) $Id: strlookup.h,v 1.1.2.2 2010-11-28 14:21:56 brian Exp $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2010  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation; version 3 of the License.

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

 Last Modified $Date: 2010-11-28 14:21:56 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: strlookup.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:56  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:37:25  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __LOCAL_STRLOOKUP_H__
#define __LOCAL_STRLOOKUP_H__

#ifndef __EXTERN
#define __EXTERN extern
#endif

#ifndef __STREAMS_EXTERN
#define __STREAMS_EXTERN __EXTERN streams_fastcall
#endif

extern rwlock_t cdevsw_lock;
extern rwlock_t fmodsw_lock;

extern int cdev_count;
extern int fmod_count;

extern struct list_head cdevsw_list;
extern struct list_head fmodsw_list;

__STREAMS_EXTERN void fmod_add(struct fmodsw *fmod, modID_t modid);
__STREAMS_EXTERN void fmod_del(struct fmodsw *fmod);
__STREAMS_EXTERN int sdev_ini(struct cdevsw *cdev, modID_t modid);
__STREAMS_EXTERN int sdev_add(struct cdevsw *cdev);
__STREAMS_EXTERN void sdev_del(struct cdevsw *cdev);
__STREAMS_EXTERN void sdev_rel(struct cdevsw *cdev);
__STREAMS_EXTERN void cmaj_add(struct devnode *cmaj, struct cdevsw *cdev, major_t major);
__STREAMS_EXTERN void cmaj_del(struct devnode *cmaj, struct cdevsw *cdev);
__STREAMS_EXTERN int cmin_ini(struct devnode *cmin, struct cdevsw *cdev, minor_t minor);
__STREAMS_EXTERN int cmin_add(struct devnode *cmin, struct cdevsw *cdev);
__STREAMS_EXTERN void cmin_del(struct devnode *cmin, struct cdevsw *cdev);
__STREAMS_EXTERN void cmin_rel(struct devnode *cmin);

__STREAMS_EXTERN struct fmodsw *fmod_str(const struct streamtab *str);
__STREAMS_EXTERN struct cdevsw *cdev_str(const struct streamtab *str);

#ifndef BIG_COMPILE
/* initialization for specfs */
__STREAMS_EXTERN int strlookup_init(void);
__STREAMS_EXTERN void strlookup_exit(void);
#endif

#endif				/* __LOCAL_STRLOOKUP_H__ */
