/*****************************************************************************

 @(#) $Id: smi_ioctl.h,v 1.1.2.2 2010-11-28 14:21:47 brian Exp $

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

 Last Modified $Date: 2010-11-28 14:21:47 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: smi_ioctl.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:47  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:25:34  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __SMI_IOCTL_H__
#define __SMI_IOCTL_H__

/* This file can be processed by doxygen(1). */

/*
 *  Protocol variants and options
 */

typedef struct smi_option {
	smi_ulong pvar;
	smi_ulong popt;
} smi_option_t;

enum {
	SS7_PVAR_ITUT_88,		/* ITU-T protocol variant */
	SS7_PVAR_ITUT_93,		/* ITU-T protocol variant */
	SS7_PVAR_ITUT_96,		/* ITU-T protocol variant */
	SS7_PVAR_ITUT_00,		/* ITU-T protocol variant */
	SS7_PVAR_ANSI_88,		/* ANSI protocol variant */
	SS7_PVAR_ANSI_92,		/* ANSI protocol variant */
	SS7_PVAR_ETSI_88,		/* ETSI protocol variant */
	SS7_PVAR_ETSI_93,		/* ETSI protocol variant */
	SS7_PVAR_ETSI_96,		/* ETSI protocol variant */
	SS7_PVAR_ETSI_00,		/* ETSI protocol variant */
	SS7_PVAR_JTTC_94,		/* JTTC protocol variant */
	SS7_PVAR_MAX = SS7_PVAR_JTTC_94
};

enum {
	SS7_POPT_MPLEV = 0x00000001,	/* multiple priority/congestion levels */
	SS7_POPT_PCR = 0x00000002,	/* preventative cyclic retransmission */
	SS7_POPT_HSL = 0x00000004,	/* high speed links */
	SS7_POPT_XSN = 0x00000008,	/* extended sequence numbers */
	SS7_POPT_MASK = 0x0000000f	/* all options */
};

#endif				/* __SMI_IOCTL_H__ */
