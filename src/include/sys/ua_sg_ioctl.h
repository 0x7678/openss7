/*****************************************************************************

 @(#) $Id: ua_sg_ioctl.h,v 1.1.2.2 2010-11-28 14:21:49 brian Exp $

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

 Last Modified $Date: 2010-11-28 14:21:49 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: ua_sg_ioctl.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:49  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:25:39  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __SYS_UA_SG_IOCTL_H__
#define __SYS_UA_SG_IOCTL_H__

/* This file can be processed by doxygen(1). */

#ifndef UA_IOC_MAGIC
#define UA_IOC_MAGIC			('U')
#endif

/*
 * Rather than get too detailed with the object model, we define a more complete address for UA.
 */

#define UA_CLEI_MAX	32

struct m2ua_ppa {
	int sgid;
	ushort sdti;
	ushort sdli;
	uint iid;
	char iid_text[UA_CLEI_MAX];
	uint tmode;
};

/*
 *  IDENTIFICATION
 *  =========================================================================
 */

typedef struct ua_oid {
	uint type;			/* object type */
	uint id;			/* object id */
} ua_oid_t;

#define UA_OBJ_TYPE_DF	0	/* Defaults */
#define UA_OBJ_TYPE_LM	1	/* Layer Management */
#define UA_OBJ_TYPE_UP	2	/* User Part */
#define UA_OBJ_TYPE_AS	3	/* Application Server */
#define UA_OBJ_TYPE_SG	4	/* Signalling Gateway */
#define UA_OBJ_TYPE_SP	5	/* Application Server Process */
#define UA_OBJ_TYPE_GP	6	/* Signalling Gateway Process */
#define UA_OBJ_TYPE_XP	7	/* SCTP Transport Provider */

/*
 *  CONFIGURATION
 *  =========================================================================
 *  Note, for UA_IOCLCONFIG, id is zero (0) and "count" is the count of the
 *  number of objects of type "type" to return.  For UA_IOCGCONFIG, id is
 *  specified and "num" is the number of associated object oids that can be
 *  returned.
 */

typedef struct ua_config {
	uint type;			/* object type */
	uint id;			/* object id */
	uint cmd;			/* object command */
	uint count;			/* object count */
	/* followed by object-specific config structure and list */
} ua_config_t;

#define UA_GET	0
#define UA_ADD	1
#define UA_CHA	2
#define UA_MOD	3
#define UA_DEL	4

#define UA_IOCGCONFIG	((UA_IOC_MAGIC<<8)|002)	/* ua_config_t */
#define UA_IOCSCONFIG	((UA_IOC_MAGIC<<8)|003)	/* ua_config_t */
#define UA_IOCTCONFIG	((UA_IOC_MAGIC<<8)|004)	/* ua_config_t */
#define UA_IOCCCONFIG	((UA_IOC_MAGIC<<8)|005)	/* ua_config_t */
#define UA_IOCLCONFIG	((UA_IOC_MAGIC<<8)|021)	/* ua_config_t */

typedef struct ua_conf_df {
} ua_conf_df_t;

typedef struct ua_conf_lm {
	uint sgid;			/* LM Controls-And-Manages this SG id */
} ua_conf_lm_t;

typedef struct ua_conf_up {
} ua_conf_up_t;

typedef struct ua_conf_as {
	uint sgid;			/* AS Obtains-Service-From this SG id */
} ua_conf_as_t;

typedef struct ua_conf_sg {
	ua_oid_t gpids[0];		/* SG Contains these GP ids */
	ua_oid_t asids[0];		/* SG Serves these AS ids */
} ua_conf_sg_t;

typedef struct ua_conf_sp {
	uint aspid;			/* SP uses this External ASPID */
	ua_oid_t sgids[0];		/* SP Connects-To these SG ids */
	ua_oid_t gpids[0];		/* SP Connects-To these GP ids */
} ua_conf_sp_t;

typedef struct ua_conf_gp {
	uint sgid;			/* GP Is-Contained-By this SG id */
	uint position;			/* GP Is-Located in this SG position (small integer) */
	ua_oid_t spids[0];		/* GP Connects-To these SP ids */
} ua_conf_gp_t;

typedef struct ua_conf_xp {
	uint spid;			/* SP that this XP Connects-To */
	uint gpid;			/* GP that this XP Connects-To */
} ua_conf_xp_t;

/*
 *  OPTIONS
 *  =========================================================================
 */

typedef struct ua_option {
	uint type;			/* object type */
	uint id;			/* object id */
	/* followed by object-specific option structure */
} ua_option_t;

#define UA_IOCGOPTIONS	((UA_IOC_MAGIC<<8)|000)	/* ua_option_t */
#define UA_IOCSOPTIONS	((UA_IOC_MAGIC<<8)|001)	/* ua_option_t */

#define UA_TMODE_NONE		0
#define UA_TMODE_OVERRIDE	1
#define UA_TMODE_LOADSHARE	2
#define UA_TMODE_BROADCAST	3

/* protocol variants */
#define UA_VERSION_NONE		0	/* interoperable */
#define UA_VERSION_RFC3331	1	/* per RFC 3331 */
#define UA_VERSION_RFC3332	1	/* per RFC 3332 */
#define UA_VERSION_RFC4666	1	/* per RFC 4666 */
#define UA_VERSION_RFC3868	1	/* per RFC 3868 */
#define UA_VERSION_TS102141	2	/* per ETSI TS 102 141 */
#define UA_VERSION_TS102142	2	/* per ETSI TS 102 142 */
#define UA_VERSION_TS102143	2	/* per ETSI TS 102 143 */
#define UA_VERSION_DEFAULT	UA_VERSION_RFC3331

/* protocol options */
#define UA_ASPEXT		(1<<0)	/* SG supports draft-bidulock-sigtran-aspext */
#define UA_SGINFO		(1<<1)	/* SG supports draft-bidulock-sigtran-sginfo */
#define UA_LOADSEL		(1<<2)
#define UA_LOADGRP		(1<<3)
#define UA_CORID		(1<<4)
#define UA_REGEXT		(1<<5)
#define UA_SESSID		(1<<6)
#define UA_DYNAMIC		(1<<7)	/* SG supports dynamic registration */
#define UA_RESERVED		(1<<8)	/* reserved */
#define UA_ASPCONG		(1<<9)
#define UA_TEXTIID		(1<<10)	/* SG supports text interface identifiers */

typedef struct ua_opt_conf_lm {
} ua_opt_conf_lm_t;

typedef struct ua_opt_conf_up {
	struct lmi_option options;	/* protocol variant and options */
	uint max_sdu;			/* maximum sdu size */
	uint opt_sdu;			/* optimal sdu size */
	uint max_cdata;			/* maximum amount of connection data */
	uint max_ddata;			/* maximum amount of disconnection data */
	uint max_esdu;			/* maximum esdu size */
	uint testab;			/* duration of establish timer (TS 102 141) */
} ua_opt_conf_up_t;

typedef struct ua_opt_conf_as {
	uint tmode;			/* traffic mode */
	uint loadgrp;			/* load group */
	uint loadsel;			/* load selection */
	uint tack;			/* duration of ack timer */
	uint tbeat;			/* duration of heartbeat time */
} ua_opt_conf_as_t;

typedef struct ua_opt_conf_sg {
	struct lmi_option options;	/* protocol variant and options */
	uint tmode;			/* traffic mode for sg */
} ua_opt_conf_sg_t;

typedef struct ua_opt_conf_sp {
	struct lmi_option options;	/* Protocol variant and options */
	uint aspid;			/* External UA ASP Identifier */
	uint tack;			/* duration of ack timer */
	uint tbeat;			/* duration of heartbeat timer */
	uint tidle;			/* duration of idle timer */
} ua_opt_conf_sp_t;

/* 
 *  Signalling Gateway Process (GP) options
 *  -------------------------------------------------------------------------
 *  None for the moment.
 */
typedef struct ua_opt_conf_gp {
};

typedef struct ua_opt_conf_df {
	struct ua_opt_conf_lm lm;	/* LM defaults */
	struct ua_opt_conf_up up;	/* UP defaults */
	struct ua_opt_conf_as as;	/* AS defaults */
	struct ua_opt_conf_sg sg;	/* SG defaults */
	struct ua_opt_conf_sp sp;	/* SP defaults */
	struct ua_opt_conf_gp gp;	/* GP defaults */
	struct ua_opt_conf_xp xp;	/* XP defaults */
} ua_opt_conf_df_t;

typedef struct ua_opt_conf_xp {
	uint ppi;			/* payload protocol identifier */
} ua_opt_conf_xp_t;

typedef struct ua_statem_df {
} ua_statem_df_t;

/*
 *  STATE
 *  =========================================================================
 */

typedef struct ua_statem {
	uint type;			/* object type */
	uint id;			/* object id */
	uint flags;			/* object flags */
	uint state;			/* object state */
	uint count;			/* sub-state structures available */
	/* followed by object-specific state structure */
} ua_statem_t;

#define UA_IOCGSTATEM	((UA_IOC_MAGIC<<8)|006)	/* ua_statem_t */
#define UA_IOCCMRESET	((UA_IOC_MAGIC<<8)|007)	/* ua_statem_t */

/* AS State */
#define AS_DOWN		0
#define AS_WACK_RREQ	1
#define AS_WACK_DREQ	2
#define AS_INACTIVE	3
#define AS_WACK_ASPAC	4
#define	AS_WACK_ASPIA	5
#define AS_ACTIVE	7

/* ASP State */
#define ASP_DOWN	0
#define ASP_WACK_ASPUP	1
#define ASP_WACK_ASPDN	2
#define ASP_UP		3

typedef struct ua_statem_lm {
} ua_statem_lm_t;

typedef struct ua_statem_up {
} ua_statem_up_t;

typedef struct ua_statem_as {
	struct ua_statem sg_list[0];	/* The AS-State of this AS for each SG. */
	struct ua_statem sp_list[0];	/* The AS-State of this AS for each ASP. */
	struct ua_statem gp_list[0];	/* The AS-State of this AS for each SGP. */
} ua_statem_as_t;

typedef struct ua_statem_sg {
	struct ua_statem gp_list[0];	/* The ASP-State of each SGP for this SG. */
	struct ua_statem as_list[0];	/* The AS-State of each AS for this SG. */
} ua_statem_sg_t;

typedef struct ua_statem_sp {
	struct ua_statem gp_list[0];	/* The ASP-State of each SGP for this ASP. */
	struct ua_statem as_list[0];	/* The AS-State of each AS for this ASP. */
} ua_statem_sp_t;

typedef struct ua_statem_gp {
	struct ua_statem sp_list[0];	/* The ASP-State of each ASP for this SGP. */
	struct ua_statem as_list[0];	/* The AS-State of each AS for this SGP. */
} ua_statem_gp_t;

typedef struct ua_statem_xp {
} ua_statem_xp_t;

/*
 *  STATISTICS
 *  =========================================================================
 */
typedef struct ua_stats {
	uint type;			/* object type */
	uint id;			/* object id */
	uint header;			/* object stats header */
	/* followed by object-specific stats structure */
} ua_stats_t;

#define UA_IOCGSTATSP	((UA_IOC_MAGIC<<8)|010)	/* ua_stats_t */
#define UA_IOCSSTATSP	((UA_IOC_MAGIC<<8)|011)	/* ua_stats_t */
#define UA_IOCGSTATS	((UA_IOC_MAGIC<<8)|012)	/* ua_stats_t */
#define UA_IOCCSTATS	((UA_IOC_MAGIC<<8)|013)	/* ua_stats_t */

typedef struct ua_stats_df {
} ua_stats_df_t;

typedef struct ua_stats_lm {
} ua_stats_lm_t;

typedef struct ua_stats_up {
} ua_stats_up_t;

typedef struct ua_stats_as {
} ua_stats_as_t;

typedef struct ua_stats_sg {
} ua_stats_sg_t;

typedef struct ua_stats_sp {
} ua_stats_sp_t;

typedef struct ua_stats_gp {
} ua_stats_gp_t;

typedef struct ua_stats_xp {
} ua_stats_xp_t;

/*
 *  EVENTS
 *  =========================================================================
 */
typedef struct ua_notify {
	uint type;			/* object type */
	uint id;			/* object id */
	lmi_notify_t notify;		/* notifications */
} ua_notify_t;

#define UA_IOCGNOTIFY	((UA_IOC_MAGIC<<8)|014)	/* ua_notify_t */
#define UA_IOCSNOTIFY	((UA_IOC_MAGIC<<8)|015)	/* ua_notify_t */
#define UA_IOCCNOTIFY	((UA_IOC_MAGIC<<8)|016)	/* ua_notify_t */

/*
 *  MANAGEMENT
 *  =========================================================================
 */
typedef struct ua_mgmt {
	uint type;			/* object type */
	uint id;			/* object id */
	uint cmd;			/* object command */
} ua_mgmt_t;

#define UA_MGMT_UP			1
#define UA_MGMT_DOWN			2
#define UA_MGMT_ACTIVATE		3
#define UA_MGMT_DEACTIVATE		4
#define UA_MGMT_UP_BLOCK		5
#define UA_MGMT_UP_UNBLOCK		6
#define UA_MGMT_ACT_BLOCK		7
#define UA_MGMT_ACT_UNBLOCK		8

#define UA_IOCCMGMT	((UA_IOC_MAGIC<<8)|017)	/* ua_mgmt_t */

/*
 *  CONTROL LOWER
 *  =========================================================================
 */
typedef struct ua_pass {
	uint muxid;
	uint type;
	uint band;
	uint ctl_length;
	uint dat_length;
	/* followed by cntl and data part of message to pass to lower */
} ua_pass_t;

#define UA_IOCCPASS	((UA_IOC_MAGIC<<8)|020)	/* ua_pass_t */

#define UA_IOC_FIRST		000
#define UA_IOC_LAST		021
#define UA_IOC_PRIVATE	030

#endif				/* __SYS_UA_SG_IOCTL_H__ */
