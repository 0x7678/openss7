# vim: ft=config sw=4 noet nocin nosi com=b\:#,b\:dnl,b\:***,b\:@%\:@ fo+=tcqlorn
# =============================================================================
# BEGINNING OF SEPARATE COPYRIGHT MATERIAL
# =============================================================================
# 
# @(#) $RCSfile: swig.m4,v $ $Name:  $($Revision: 1.1.2.7 $) $Date: 2011-05-31 09:46:02 $
#
# -----------------------------------------------------------------------------
#
# Copyright (c) 2008-2011  Monavacon Limited <http://www.monavacon.com/>
# Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>
#
# All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU Affero General Public License as published by the Free
# Software Foundation; version 3 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
# details.
#
# You should have received a copy of the GNU Affero General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>, or write to
# the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
# Last Modified $Date: 2011-05-31 09:46:02 $ by $Author: brian $
#
# =============================================================================

# =============================================================================
# AC_PROG_SWIG
# -----------------------------------------------------------------------------
# Checks for the swig command.  This command is used to generate interface
# files for various languages like java, tcl, etc.  We distribute the
# secondary result of this command so that the building system does not need
# swig installed to work, only when building from CVS.  The missing script
# should simply touch the target files.
# -----------------------------------------------------------------------------
m4_define([AC_PROG_SWIG], [dnl
    tmp_PATH="${PATH:+$PATH:}/usr/local/bin:/usr/bin:/bin";
    AC_ARG_VAR([SWIG],
	[Swig command. @<@default=swig@:>@])
    _BLD_PATH_PROG([SWIG], [swig], [${am_missing4_run}swig], [$tmp_PATH], [dnl
	AC_MSG_WARN([Cannot find swig program in PATH.])])
])# AC_PROG_SWIG
# =============================================================================

# =============================================================================
# _SWIG_XXX
# -----------------------------------------------------------------------------
AC_DEFUN([_SWIG_XXX], [dnl
])# _SWIG_XXX
# =============================================================================

# =============================================================================
#
# $Log: swig.m4,v $
# Revision 1.1.2.7  2011-05-31 09:46:02  brian
# - new distros
#
# Revision 1.1.2.6  2011-02-07 04:48:32  brian
# - updated configure and build scripts
#
# Revision 1.1.2.5  2009-07-21 11:06:13  brian
# - changes from release build
#
# Revision 1.1.2.4  2009-07-13 07:13:27  brian
# - changes for multiple distro build
#
# Revision 1.1.2.3  2009-07-04 03:51:33  brian
# - updates for release
#
# Revision 1.1.2.2  2009-06-29 07:35:38  brian
# - improvements to build process
#
# Revision 1.1.2.1  2009-06-21 11:06:05  brian
# - added files to new distro
#
# =============================================================================
# 
# Copyright (c) 2008-2011  Monavacon Limited <http://www.monavacon.com/>
# Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>
# 
# =============================================================================
# ENDING OF SEPARATE COPYRIGHT MATERIAL
# =============================================================================
# vim: ft=config sw=4 noet nocin nosi com=b\:#,b\:dnl,b\:***,b\:@%\:@ fo+=tcqlorn

