/*****************************************************************************

 @(#) $Id: stream.h,v 1.1.2.2 2010-11-28 14:21:50 brian Exp $

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

 Last Modified $Date: 2010-11-28 14:21:50 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: stream.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:50  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:26:45  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __SYS_AIX_STREAM_H__
#define __SYS_AIX_STREAM_H__

#ifndef __SYS_STREAM_H__
#warning "Do not include sys/aix/stream.h directly, include sys/stream.h instead."
#endif

#ifndef __KERNEL__
#error "Do not include kernel header files in user space programs."
#endif

#ifndef __EXTERN_INLINE
#define __EXTERN_INLINE extern __inline__
#endif

#ifndef __AIX_EXTERN_INLINE
#define __AIX_EXTERN_INLINE __EXTERN_INLINE streamscall
#endif

#ifndef __AIX_EXTERN
#define __AIX_EXTERN extern streamscall
#endif				/* __AIX_EXTERN_INLINE */

#ifndef _AIX_SOURCE
#warning "_AIX_SOURCE not defined but AIX stream.h included."
#endif

#include <sys/openss7/config.h>

#if defined CONFIG_STREAMS_COMPAT_AIX || defined CONFIG_STREAMS_COMPAT_AIX_MODULE

#ifndef dev_t
#define dev_t __streams_dev_t
#endif

/* These are MPS definitions exposed by AIX, but implemented in mpscompat.c */
__AIX_EXTERN int mi_open_comm(caddr_t *mi_list, uint size, queue_t *q, dev_t *dev, int flag, int sflag,
			cred_t *credp);
__AIX_EXTERN int mi_close_comm(caddr_t *mi_list, queue_t *q);
__AIX_EXTERN caddr_t mi_next_ptr(caddr_t strptr);
__AIX_EXTERN caddr_t mi_prev_ptr(caddr_t strptr);
__AIX_EXTERN void mi_bufcall(queue_t *q, int size, int priority);

__AIX_EXTERN int wantio(queue_t *q, struct wantio *w);

__AIX_EXTERN_INLINE int
wantmsg(queue_t *q, int streamscall (*func) (mblk_t *))
{
	if (!q->q_qinfo->qi_srvp) {
		q->q_ftmsg = func;
		return (1);
	}
	return (0);
}

#else
#ifdef _AIX_SOURCE
#warning "_AIX_SOURCE defined by not CONFIG_STREAMS_COMPAT_AIX"
#endif
#endif

#endif				/* __SYS_AIX_STREAM_H__ */
