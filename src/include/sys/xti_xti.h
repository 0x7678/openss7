/*****************************************************************************

 @(#) $Id: xti_xti.h,v 1.1.2.2 2010-11-28 14:21:50 brian Exp $

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

 $Log: xti_xti.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:50  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:25:39  brian
 - added files to new distro

 *****************************************************************************/

#ifndef _SYS_XTI_XTI_H
#define _SYS_XTI_XTI_H

/* This file can be processed with doxygen(1). */

/** @addtogroup xnet
  * @{ */

/** @file
  * XTI Generic options header file.
  *
  * In accordance with OpenGroup Single UNIX Specifications, the symbols in this
  * file are exposed by including the <xti.h> header file.  */

/*
 *  XTI Generic options header file.
 */

#ifndef t_scalar_t
typedef int32_t t_scalar_t;

#define t_scalar_t t_scalar_t
#endif

/* OPTIONS ON XTI LEVEL */

/**
  * XTI Level.
  */
#define XTI_GENERIC	0xffff	/**< XTI Generic option level. */

/** @name XTI-Level Options
  * @{ */
#define XTI_DEBUG	0x0001	/**< Enable debugging. */
#define XTI_LINGER	0x0080	/**< Linger on close if data present. */
#define XTI_SNDBUF	0x1001	/**< Send buffer size. */
#define XTI_RCVBUF	0x1002	/**< Receive buffer size. */
#define XTI_SNDLOWAT	0x1003	/**< Send low-water mark. */
#define XTI_RCVLOWAT	0x1004	/**< Receive low-water mark. */
/** @} */

/** @name Additional extension XTI-level Options
  * @{ */
#define XTI_REUSEADDR	0x2001	/**< Reuse addresses. */
#define XTI_DONTROUTE	0x2002	/**< Do not route. */
#define XTI_BROADCAST	0x2003	/**< Permit broadcast. */
#define XTI_KEEPALIVE	0x2004	/**< Keep connections alive. */
#define XTI_PRIORITY	0x2005	/**< Set connection priority. */
/** @} */

/** Structure used with linger option. */
struct t_linger {
	t_scalar_t l_onoff;		/**< Option on/off. */
	t_scalar_t l_linger;		/**< Linger time. */
};

#endif				/* _SYS_XTI_XTI_H */

/** @} */

// vim: com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS
