/*****************************************************************************

 @(#) $Id: strconf.h,v 1.1.2.2 2010-11-28 14:21:52 brian Exp $

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

 Last Modified $Date: 2010-11-28 14:21:52 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: strconf.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:52  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:26:49  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __SYS_OS7_STRCONF_H__
#define __SYS_OS7_STRCONF_H__

#ifndef __SYS_STRCONF_H__
#warning "Do not include sys/os7/strconf.h directly, include sys/strconf.h instead."
#endif

#ifndef __KERNEL__
#error "Do not use kernel headers for user space programs"
#endif				/* __KERNEL__ */

#ifndef __EXTERN_INLINE
#define __EXTERN_INLINE extern __inline__
#endif

#ifndef __OS7_EXTERN_INLINE
#define __OS7_EXTERN_INLINE __EXTERN_INLINE streamscall
#endif				/* __OS7_EXTERN_INLINE */

#ifndef __OS7_EXTERN
#define __OS7_EXTERN extern streamscall
#endif

#ifndef _OS7_SOURCE
#warning "_OS7_SOURCE not defined but OS7 strconf.h included"
#endif

#include <sys/openss7/config.h>

#if defined(CONFIG_STREAMS_COMPAT_OS7) || defined(CONFIG_STREAMS_COMPAT_OS7_MODULE)

#else
#ifdef _OS7_SOURCE
#warning "_OS7_SOURCE defined but not CONFIG_STREAMS_COMPAT_OS7"
#endif
#endif				/* CONFIG_STREAMS_COMPAT_OS7 */

#endif				/* __SYS_OS7_STRCONF_H__ */
