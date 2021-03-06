/*****************************************************************************

 @(#) $RCSfile: sctp_adler32.c,v $ $Name:  $($Revision: 1.1.2.3 $) $Date: 2011-05-31 09:46:05 $

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

 Last Modified $Date: 2011-05-31 09:46:05 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: sctp_adler32.c,v $
 Revision 1.1.2.3  2011-05-31 09:46:05  brian
 - new distros

 Revision 1.1.2.2  2010-11-28 14:21:35  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:20:52  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: sctp_adler32.c,v $ $Name:  $($Revision: 1.1.2.3 $) $Date: 2011-05-31 09:46:05 $";

#undef _DEBUG
#undef SCTP_CONFIG_DEBUG

#ifdef NEED_LINUX_AUTOCONF_H
#include NEED_LINUX_AUTOCONF_H
#endif
#include <linux/version.h>
#include <linux/compiler.h>
#include <linux/types.h>

#include "sctp_adler32.h"

/*
 *  -------------------------------------------------------------------------
 *
 *  Adler-32 Checksum
 *
 *  -------------------------------------------------------------------------
 *  Compute the adler32 checksum.  This follows the description in RFC 2960
 *  Appendix B.  Borrowed from zlib.c.
 */
#define DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);
uint32_t
adler32(uint32_t adler, void *buf, size_t len)
{
	register uint32_t s1 = adler;
	register uint32_t s2 = (adler >> 16) & 0xffff;
	register uint8_t *ptr = buf;
	register int k;

	if (!ptr)
		return 1L;
	while (len > 0) {
		k = len < NMAX ? len : NMAX;
		len -= k;
		while (k >= 16) {
			DO16(ptr);
			ptr += 16;
			k -= 16;
		}
		if (k != 0)
			do {
				s1 += *ptr++;
				s2 += s1;
			}
			while (--k);
		s1 %= BASE;
		s2 %= BASE;
	}
	return (s2 << 16) | s1;
}
