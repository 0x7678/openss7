/*****************************************************************************

 @(#) $RCSfile: specfs.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-03-17 07:01:29 $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2010  Monavacon Limited <http://www.monavacon.com/>
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

 Last Modified $Date: 2011-03-17 07:01:29 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: specfs.c,v $
 Revision 1.1.2.4  2011-03-17 07:01:29  brian
 - build and repo system improvements

 Revision 1.1.2.3  2010-11-28 14:21:56  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.2  2009-09-01 09:09:51  brian
 - added text image files

 Revision 1.1.2.1  2009-06-21 11:37:16  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: specfs.c,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-03-17 07:01:29 $";

/* can we just include these into one big compilation unit? */

#define BIG_COMPILE 1
#define BIG_STATIC static
#define BIG_STATIC_INLINE static streams_inline

#define BIG_COMPILE_SPECFS 1

#define __EXTERN_INLINE
#define __STRSCHD_EXTERN_INLINE static inline streams_fastcall
#define __STRUTIL_EXTERN_INLINE static inline streams_fastcall

/* initialization for specfs */
BIG_STATIC int strlookup_init(void);
BIG_STATIC void strlookup_exit(void);

#ifndef CONFIG_STREAMS_WRAPPER_MODULE
#undef ident
#define ident ident_wrapper
#include "wrapper.c"
#endif				/* CONFIG_STREAMS_WRAPPER_MODULE */
#undef ident
#define ident ident_strlock
#include "strlock.c"
#undef ident
#define ident ident_strspecfs
#include "strspecfs.c"
#undef ident
#define ident ident_strlookup
#include "strlookup.c"
#undef ident
#define ident ident_strattach
#include "strattach.c"
#undef ident
#define ident ident_strpipe
#include "strpipe.c"
