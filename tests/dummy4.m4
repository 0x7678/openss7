# vim: ft=config sw=4 noet nocin nosi com=b\:#,b\:dnl,b\:***,b\:@%\:@ fo+=tcqlorn
# =============================================================================
# BEGINNING OF SEPARATE COPYRIGHT MATERIAL
# =============================================================================
# 
# @(#) $RCSfile: dummy4.m4,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:49:03 $
#
# -----------------------------------------------------------------------------
#
# Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>
#
# All Rights Reserved.
# 
# Unauthorized distribution or duplication is prohibited.
# 
# This software and related documentation is protected by copyright and
# distributed under licenses restricting its use, copying, distribution and
# decompilation.  No part of this software or related documentation may be
# reproduced in any form by any means without the prior written authorization
# of the copyright holder, and licensors, if any.
# 
# The recipient of this document, by its retention and use, warrants that the
# recipient will protect this information and keep it confidential, and will
# not disclose the information contained in this document without the written
# permission of its owner.
# 
# The author reserves the right to revise this software and documentation for
# any reason, including but not limited to, conformity with standards
# promulgated by various agencies, utilization of advances in the state of the
# technical arts, or the reflection of changes in the design of any techniques,
# or procedures embodied, described, or referred to herein.  The author is
# under no obligation to provide any feature listed herein.
#
# -----------------------------------------------------------------------------
# 
# As an exception to the above, this software may be distributed under the GNU
# Affero General Public License (GPL) Version 3, so long as the software is
# distributed with, and only used for the testing of, OpenSS7 modules, drivers,
# and libraries.
#
# -----------------------------------------------------------------------------
#
# U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
# behalf of the U.S. Government ("Government"), the following provisions apply
# to you.  If the Software is supplied by the Department of Defense ("DoD"), it
# is classified as "Commercial Computer Software" under paragraph 252.227-7014
# of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
# successor regulations) and the Government is acquiring only the license rights
# granted herein (the license rights customarily provided to non-Government
# users).  If the Software is supplied to any unit or agency of the Government
# other than DoD, it is classified as "Restricted Computer Software" and the
# Government's rights in the Software are defined in paragraph 52.227-19 of the
# Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
# the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
# (or any successor regulations).
#
# -----------------------------------------------------------------------------
#
# Commercial licensing and support of this software is available from OpenSS7
# Corporation at a fee.  See http://www.openss7.com/
#
# -----------------------------------------------------------------------------
#
# Last Modified $Date: 2009-06-21 11:49:03 $ by $Author: brian $
#
# =============================================================================

AT_SETUP([dummy test4])
AT_KEYWORDS([dummy])
AT_CHECK([exit 0], [], [ignore])
AT_XFAIL_IF(true)
echo "This is another dummy test"
exit 1
AT_CLEANUP

# =============================================================================
#
# $Log: dummy4.m4,v $
# Revision 1.1.2.1  2009-06-21 11:49:03  brian
# - added files to new distro
#
# Revision 0.9.2.8  2008-05-03 13:23:32  brian
# - added strx25 sub-package and package updates
#
# Revision 0.9.2.7  2008-04-28 12:54:12  brian
# - update file headers for release
#
# Revision 0.9.2.6  2007/12/15 20:20:22  brian
# - updates
#
# Revision 0.9.2.5  2007/08/13 22:46:42  brian
# - GPLv3 header updates
#
# Revision 0.9.2.4  2006/09/18 00:48:49  brian
# - updated testsuite headers
#
# Revision 0.9.2.3  2005/07/04 20:07:55  brian
# - fixed spelling of CVS keyword
#
# Revision 0.9.2.2  2005/05/14 23:59:23  brian
# - getting autotest up and running
#
# =============================================================================
# 
# Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>
# 
# =============================================================================
# ENDING OF SEPARATE COPYRIGHT MATERIAL
# =============================================================================
# vim: ft=config sw=4 noet nocin nosi com=b\:#,b\:dnl,b\:***,b\:@%\:@ fo+=tcqlorn
