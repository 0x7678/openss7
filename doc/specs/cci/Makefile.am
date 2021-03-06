## vim: ft=automake comments=b\:#,b\:##,b\:#\! formatoptions+=tcqlor
## =============================================================================
## 
# @(#) $RCSfile: Makefile.am,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2010-11-28 13:44:39 $
##
## -----------------------------------------------------------------------------
##
## Copyright (c) 2008-2010  Monavacon Limited <http://www.monavacon.com/>
## Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
## Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>
##
## All Rights Reserved.
##
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU Affero General Public License as published by the Free
## Software Foundation; version 3 of the License.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
## FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
## details.
##
## You should have received a copy of the GNU Affero General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>, or
## write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
## 02139, USA.
##
## -----------------------------------------------------------------------------
##
## U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
## behalf of the U.S. Government ("Government"), the following provisions apply
## to you.  If the Software is supplied by the Department of Defense ("DoD"), it
## is classified as "Commercial Computer Software" under paragraph 252.227-7014
## of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
## successor regulations) and the Government is acquiring only the license rights
## granted herein (the license rights customarily provided to non-Government
## users).  If the Software is supplied to any unit or agency of the Government
## other than DoD, it is classified as "Restricted Computer Software" and the
## Government's rights in the Software are defined in paragraph 52.227-19 of the
## Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
## the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
## (or any successor regulations).
##
## -----------------------------------------------------------------------------
##
## Commercial licensing and support of this software is available from OpenSS7
## Corporation at a fee.  See http://www.openss7.com/
##
## -----------------------------------------------------------------------------
##
## Last Modified $Date: 2010-11-28 13:44:39 $ by $Author: brian $
##
## =============================================================================

include ../../../am/openss7.am

info_TEXINFOS		=

if DEVELOPMENT
## DEVELOPMENT

info_TEXINFOS		+= cci.texi

cci.h: $(top_srcdir)/src/include/ss7/cci.h
	$(AM_V_GEN)cat $< | sed -e '1,/\*\//d;/doxygen/d;/#ident/d;/^\/\/\//d' | cat -s | expand > $@

isupi.h: $(top_srcdir)/src/include/ss7/isupi.h
	$(AM_V_GEN)cat $< | sed -e '1,/\*\//d;/doxygen/d;/#ident/d;/^\/\/\//d' | cat -s | expand > $@

isdni.h: $(top_srcdir)/src/include/ss7/isdni.h
	$(AM_V_GEN)cat $< | sed -e '1,/\*\//d;/doxygen/d;/#ident/d;/^\/\/\//d' | cat -s | expand > $@

CLEANFILES += cci.h isupi.h isdni.h

cci_TEXINFOS		= \
			  cci.h \
			  isupi.h \
			  isdni.h \
			  $(top_srcdir)/scripts/texi/macros.texi \
			  $(top_srcdir)/scripts/texi/versions.texi \
			  $(top_srcdir)/scripts/texi/fdl.texi

if MAINTAINER_MODE
if AMDEP
cci_TEXINFOS		+= \
			  $(top_builddir)/scripts/texi/args.texi
endif
endif

EXTRA_info_TEXINFOS	= \
			  $(top_builddir)/scripts/texi/args.texi \
			  $(info_TEXINFOS) \
			  $(cci_TEXINFOS)

if PKG_BUILD_INDEP
## PKG_BUILD_INDEP

FIG_FIGS		= \
			cci01a.fig \
			cci01b.fig \
			cci01.fig \
			cci02.fig \
			cci03.fig \
			cci04.fig \
			cci05.fig \
			cci06.fig \
			cci07.fig \
			cci08.fig \
			cci09.fig \
			cci10b.fig \
			cci10c.fig \
			cci10d.fig \
			cci10.fig \
			cci11b.fig \
			cci11.fig \
			cci12.fig \
			cci13.fig \
			cci14.fig \
			cci15.fig \
			cci16.fig \
			cci17.fig \
			cci18.fig \
			cci19.fig \
			cci20.fig \
			cci21.fig \
			cci22.fig \
			cci23.fig \
			cci24.fig \
			cci25.fig \
			cci26.fig \
			cci27.fig \
			cci28.fig \
			cci30.fig \
			cci31.fig \
			cci32.fig \
			cci33.fig \
			cci34.fig \
			cci35.fig \
			cci36.fig \
			cci37.fig \
			cci38.fig \
			cci39.fig \
			cci40.fig \
			cci41.fig \
			cci42.fig \
			cci43.fig \
			cci44.fig \
			cci45.fig \
			cci46.fig \
			cci47.fig \
			cci48.fig \
			cci49.fig

TBL_TBLS		= \
			cci_tab1.tbl \
			cci_tab2.tbl \
			cci_tab3.tbl

## PKG_BUILD_INDEP
endif

## DEVELOPMENT
endif

include ../../../am/info.am

## =============================================================================
##
## $Log: Makefile.am,v $
## Revision 1.1.2.2  2010-11-28 13:44:39  brian
## - update makefiles
##
## Revision 1.1.2.1  2009-06-21 10:52:47  brian
## - added files to new distro
##
## =============================================================================
## vim: ft=automake comments=b\:#,b\:##,b\:#\! formatoptions+=tcqlor
