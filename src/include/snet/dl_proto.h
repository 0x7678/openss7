/*****************************************************************************

 @(#) $Id: dl_proto.h,v 1.1.2.3 2011-02-07 04:54:42 brian Exp $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2011  Monavacon Limited <http://www.monavacon.com/>
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

 Last Modified $Date: 2011-02-07 04:54:42 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: dl_proto.h,v $
 Revision 1.1.2.3  2011-02-07 04:54:42  brian
 - code updates for new distro support

 Revision 1.1.2.2  2010-11-28 14:21:45  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:25:32  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __SYS_SNET_DL_PROTO_H__
#define __SYS_SNET_DL_PROTO_H__

#define DATAL_TYPE	'R'
#define DATAL_RESPONSE	'D'
#define DATAL_PARAMS	'P'
#define DATAL_TX	't'
#define DATAL_RX	'r'

typedef struct data1_type {
	uint8_t prim_type;
	uint8_t version;
	uint16_t pad;
	uint16_t lwb;
	uint16_t upb;
	uint16_t frgsz;
	uint8_t addr[0];
} S_DATAL_TYPE;

typedef struct datal_response {
	uint8_t prim_type;
	uint8_t version;
	uint8_t mac_type;
	uint8_t addr_len;
	uint16_t lwb;
	uint16_t upb;
	uint16_t frgsz;
	uint8_t addr[0];
} S_DATAL_RESPONSE;

#define HW_ETHERNET	1
#define HW_TOKEN_RING	4
#define HW_802		6

typedef struct datal_params {
	uint8_t prim_type;
	uint8_t version;
	uint8_t mac_type;
	uint8_t addr_len;
	uint16_t frgsz;
	uint8_t addr[0];
} S_DATAL_PARAMS;

typedef struct datal_tx {
	uint8_t prim_type;
	uint8_t version;
	uint16_t pad;
	uint8_t route_length;
	uint8_t addr_length;
	uint16_t type;
	uint8_t dst[0];
} S_DATAL_TX;

typedef struct datal_rx {
	uint8_t prim_type;
	uint8_t version;
	uint16_t pad;
	uint8_t route_length;
	uint8_t addr_length;
	uint16_t type;
	uint8_t src[0];
} S_DATAL_RX;

typedef union datal_proto {
	uint8_t type;
	struct datal_type dltype;
	struct datal_response dlresp;
	struct datal_params dlparm;
	struct datal_tx dltx;
	struct datal_rx dlrx;
} S_DATAL_PROTO;

#endif				/* __SYS_SNET_DL_PROTO_H__ */
