# =============================================================================
# 
# @(#) $RCSfile: Makefile.am,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 10:48:59 $
#
# -----------------------------------------------------------------------------
#
# Copyright (c) 2001-2007  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>
#
# All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; version 3 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>, or write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
# Last Modified $Date: 2009-06-21 10:48:59 $ by $Author: brian $
#
# =============================================================================

include ../../../am/openss7.am

info_TEXINFOS		=

if DEVELOPMENT
## DEVELOPMENT

info_TEXINFOS		+= ss.texi

ss_TEXINFOS		= \
			$(top_srcdir)/scripts/texi/macros.texi \
			$(top_srcdir)/scripts/texi/versions.texi \
			$(top_srcdir)/scripts/texi/fdl.texi

if MAINTAINER_MODE
if AMDEP
ss_TEXINFOS		+= \
			$(top_builddir)/scripts/texi/args.texi
endif
endif

EXTRA_info_TEXINFOS	= \
			$(top_builddir)/scripts/texi/args.texi \
			$(info_TEXINFOS) \
			$(ss_TEXINFOS)

if PKG_BUILD_INDEP
## PKG_BUILD_INDEP

FIG_FIGS		=

PNG_PNGS		=

PS_PSS			=

## PKG_BUILD_INDEP
endif

## DEVELOPMENT
endif

include ../../../am/info.am

# =============================================================================
#
# $Log: Makefile.am,v $
# Revision 1.1.2.1  2009-06-21 10:48:59  brian
# - added files to new distro
#
# Revision 0.9.2.4  2008-11-26 12:23:03  brian
# - correction for FDL update
#
# Revision 0.9.2.3  2008-11-26 12:01:23  brian
# - updated to FDL 1.3
#
# Revision 0.9.2.2  2008-08-31 06:57:10  brian
# - do not customize docs unless maintainer modes and dependency tracking
#
# Revision 0.9.2.1  2007/11/06 12:54:57  brian
# - added more top-level documentation
#
# =============================================================================
# vim: ft=automake comments=b\:#,b\:##,b\:#\! formatoptions+=tcqlor
