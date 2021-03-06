# vim: ft=config sw=4 noet nocin nosi com=b\:#,b\:dnl,b\:***,b\:@%\:@ fo+=tcqlorn
# =============================================================================
# BEGINNING OF SEPARATE COPYRIGHT MATERIAL
# =============================================================================
# 
# @(#) $RCSfile: strconf.m4,v $ $Name:  $($Revision: 1.1.2.4 $) $Date: 2011-02-07 04:48:32 $
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
# Last Modified $Date: 2011-02-07 04:48:32 $ by $Author: brian $
#
# =============================================================================

# =============================================================================
# _STRCONF
# -----------------------------------------------------------------------------
AC_DEFUN([_STRCONF], [dnl
    AC_MSG_NOTICE([+-------------------------------------+])
    AC_MSG_NOTICE([| STREAMS Configuration Script Checks |])
    AC_MSG_NOTICE([+-------------------------------------+])
    _STRCONF_OPTIONS
    _STRCONF_SETUP
    _STRCONF_OUTPUT
])# _STRCONF
# =============================================================================

# =============================================================================
# _STRCONF_OPTIONS
# -----------------------------------------------------------------------------
AC_DEFUN([_STRCONF_OPTIONS], [dnl
])# _STRCONF_OPTIONS
# =============================================================================

# =============================================================================
# _STRCONF_SETUP
# -----------------------------------------------------------------------------
AC_DEFUN([_STRCONF_SETUP], [dnl
    AC_MSG_CHECKING([for strconf prefix])
    if test :${strconf_prefix+set} != :set ; then
	strconf_prefix='strconf'
    fi
    AC_MSG_RESULT([$strconf_prefix])
    AC_MSG_CHECKING([for strconf stem file name])
    eval "STRCONF_STEM=\${${strconf_prefix}_cv_stem:-streams.conf}"
    eval "${strconf_prefix}_cv_stem=\"\$STRCONF_STEM\""
    AC_MSG_RESULT([$STRCONF_STEM])
    AC_MSG_CHECKING([for strconf config files in $srcdir])
dnl
dnl It's complicated but this is how we prune a whole bunch of directories
dnl when the build and source directory are the same and the build directory
dnl is already configured.  One should really do a distclean, but hey.
dnl
    STRCONF_CONFIGS=
    for strconf_tmp in `find $srcdir -type f \
	\( -name "$STRCONF_STEM" -o -name "$STRCONF_STEM.in" \) \
	-not \( \( \
	    -path ${srcdir}/${PACKAGE}/'*' -o \
	    -path ${srcdir}/${PACKAGE}-${VERSION}/'*' -o \
	    -path ${srcdir}/${PACKAGE}-bin-${VERSION}/'*' -o \
	    -path ${srcdir}/${PACKAGE_LCNAME}/'*' -o \
	    -path ${srcdir}/${PACKAGE_LCNAME}-${VERSION}/'*' -o \
	    -path ${srcdir}/${PACKAGE_LCNAME}-bin-${VERSION}/'*' -o \
	    -path ${srcdir}/debian/'*' -o \
	    -path ${srcdir}/_build/'*' -o \
	    -path ${srcdir}/_install/'*' \
	\) -prune \)`
    do
	if test -f "$strconf_tmp" ; then
	    STRCONF_CONFIGS="$strconf_tmp${STRCONF_CONFIGS:+ $STRCONF_CONFIGS}"
	fi
    done
    AC_MSG_RESULT([$STRCONF_CONFIGS])
    AC_MSG_CHECKING([for strconf script])
dnl STRCONF_SCRIPT="$ac_aux_dir/strconf-sh"
    STRCONF_SCRIPT="$ac_aux_dir/strconf.awk"
    AC_MSG_RESULT([${STRCONF_SCRIPT}])
    AC_MSG_CHECKING([for strconf command])
dnl STRCONF="$SHELL $STRCONF_SCRIPT"
    STRCONF="${AWK} -f ${STRCONF_SCRIPT} --"
    AC_MSG_RESULT([${STRCONF}])
dnl
dnl There is really no need to allow the name of the normal master file to be
dnl changed by configure
dnl
    AC_ARG_WITH([strconf-master],
	[AS_HELP_STRING([--with-strconf-master=FILENAME],
	    [configuration master file @<:@default=Config.master@:>@])])
    AC_MSG_CHECKING([for strconf master file])
    if test :"${with_strconf_master:-no}" != :no ; then
	STRCONF_INPUT="$with_strconf_master"
    else
	eval "STRCONF_INPUT=\"\${${strconf_prefix}_cv_input:-Config.master}\""
    fi
    eval "${strconf_prefix}_cv_input=\"\$STRCONF_INPUT\""
    AC_MSG_RESULT([${STRCONF_INPUT}])
    AC_ARG_WITH([base-major],
	[AS_HELP_STRING([--with-base-major=MAJOR],
	    [base major device number @<:@default=230@:>@])])
    AC_MSG_CHECKING([for strconf base major device number])
    if test :"${with_base_major:-no}" != :no ; then
	STRCONF_MAJBASE="$with_base_major"
    else
	eval "STRCONF_MAJBASE=\"\${${strconf_prefix}_cv_majbase:-231}\""
    fi
    eval "${strconf_prefix}_cv_majbase=\"\$STRCONF_MAJBASE\""
    AC_MSG_RESULT([${STRCONF_MAJBASE}])
    AC_ARG_WITH([base-modid],
	[AS_HELP_STRING([--with-base-modid=MODID],
	    [base module id number default=1@:>@])])
    AC_MSG_CHECKING([for strconf base module id number])
    if test :"${with_base_modid:-no}" != :no ; then
	STRCONF_MIDBASE="$with_base_modid"
    else
	eval "STRCONF_MIDBASE=\"\${${strconf_prefix}_cv_midbase:-1}\""
    fi
    eval "${strconf_prefix}_cv_midbase=\"\$STRCONF_MIDBASE\""
    AC_MSG_RESULT([${STRCONF_MIDBASE}])
    AC_MSG_CHECKING([for strconf configuration header file name])
    eval "STRCONF_CONFIG=\"\${${strconf_prefix}_cv_sconfig:-strconf.h}\""
    eval "${strconf_prefix}_cv_sconfig=\"\$STRCONF_CONFIG\""
    AC_MSG_RESULT([${STRCONF_CONFIG}])
    AC_MSG_CHECKING([for strconf modules include file name])
    eval "STRCONF_MODCONF=\"\${${strconf_prefix}_cv_modconf:-modconf.h}\""
    eval "${strconf_prefix}_cv_modconf=\"\$STRCONF_MODCONF\""
    AC_MSG_RESULT([${STRCONF_MODCONF}])
    AC_MSG_CHECKING([for strconf modules makefile include file name])
    eval "STRCONF_DRVCONF=\"\${${strconf_prefix}_cv_drvconf:-drvconf.mk}\""
    eval "${strconf_prefix}_cv_drvconf=\"\$STRCONF_DRVCONF\""
    AC_MSG_RESULT([${STRCONF_DRVCONF}])
    AC_MSG_CHECKING([for strconf kernel modules configuration file name])
    eval "STRCONF_CONFMOD=\"\${${strconf_prefix}_cv_confmod:-conf.modules}\""
    eval "${strconf_prefix}_cv_confmod=\"\$STRCONF_CONFMOD\""
    AC_MSG_RESULT([${STRCONF_CONFMOD}])
    AC_MSG_CHECKING([for strconf rpm devices list file name])
    eval "STRCONF_MAKEDEV=\"\${${strconf_prefix}_cv_makedev:-devices.lst}\""
    eval "${strconf_prefix}_cv_makedev=\"\$STRCONF_MAKEDEV\""
    AC_MSG_RESULT([${STRCONF_MAKEDEV}])
    AC_MSG_CHECKING([for strconf makenodes source file name])
    eval "STRCONF_MKNODES=\"\${${strconf_prefix}_cv_mknodes:-${PACKAGE_TARNAME}_mknod.c}\""
    eval "${strconf_prefix}_cv_mknodes=\"\$STRCONF_MKNODES\""
    STRMAKENODES=`basename "$STRCONF_MKNODES" .c`
    AC_MSG_RESULT([${STRCONF_MKNODES}])
    AC_MSG_CHECKING([for strconf strsetup configuration file name])
    eval "STRCONF_STSETUP=\"\${${strconf_prefix}_cv_strsetup:-strsetup.conf}\""
    eval "${strconf_prefix}_cv_strsetup=\"\$STRCONF_STSETUP\""
    AC_MSG_RESULT([${STRCONF_STSETUP}])
    AC_MSG_CHECKING([for strconf strload configuration file name])
    eval "STRCONF_STRLOAD=\"\${${strconf_prefix}_cv_strload:-strload.conf}\""
    eval "${strconf_prefix}_cv_strload=\"\$STRCONF_STRLOAD\""
    AC_MSG_RESULT([${STRCONF_STRLOAD}])
    AC_MSG_CHECKING([for strconf mkdevices script file name])
    eval "STRCONF_DEVICES=\"\${${strconf_prefix}_cv_mkdevices:-${PACKAGE_TARNAME}_mkdev}\""
    eval "${strconf_prefix}_cv_mkdevices=\"\$STRCONF_DEVICES\""
    AC_MSG_RESULT([${STRCONF_DEVICES}])
    AC_MSG_CHECKING([for strconf STREAMS package])
    eval "STRCONF_PACKAGE=\"\${${strconf_prefix}_cv_package:-\${streams_cv_package:-LfS}}\""
    eval "${strconf_prefix}_cv_package=\"\$STRCONF_PACKAGE\""
    AC_MSG_RESULT([${STRCONF_PACKAGE}])
    AC_MSG_CHECKING([for strconf minor bits])
    eval "STRCONF_MINORSZ=\"\${${strconf_prefix}_cv_minorbits:-\${linux_cv_minorbits:-8}}\""
    eval "${strconf_prefix}_cv_minorbits=\"\$STRCONF_MINORSZ\""
    AC_MSG_RESULT([${STRCONF_MINORSZ}])
dnl
dnl Allow the user to specify a package directory that is completely outside
dnl of the source or build tree: that way, one can configure with a simple
dnl option and do not need to copy files from anywhere.
dnl
    AC_ARG_WITH([strconf-pkgdir],
	[AS_HELP_STRING([--with-strconf-pkgdir=DIRECTORY],
	    [binary package directory @<:@default=pkg@:>@])])
    AC_MSG_CHECKING([for strconf binary package directories])
    strconf_cv_packagedir=
    strconf_dir="$with_strconf_pkgdir"
    # clean it up
    strconf_dir=`echo $strconf_dir | sed -e 's,///*,/,g;s,/\./,/,g;s,/[[^/]]*/\.\./,/,;s,/\.[$],,;s,/[$],,;s,^\./,,;s,^\.[$],,'`
    if test -n "$strconf_dir" ; then
	case $strconf_dir in
	    (.*|/*) # if it begin a . or a / then it is not vpath relative
	    # if it is not vpath relative, then it must exist
	    if test ! -d "$strconf_dir" ; then
		AC_MSG_ERROR([
***
*** You have specified a specific package directory of
***	"$with_strconf_pkgdir"
*** using --with-strconf-pkgdir, however, that directory does not exist.
*** This cannot be correct.  Please specify the correct directory with
*** the configure option --with-strconf-pkgdir, or create the
***	"$strconf_dir"
*** directory before calling configure again.
***])
	    fi
	    strconf_cv_packagedir="$strconf_dir"
	    ;;
	    (*)
	    # if it is vpath relative, then at the source directory must exist
	    if test ! -d "$srcdir/$strconf_dir" ; then
		AC_MSG_ERROR([
***
*** You have specified a relative package directory of
***	"$with_strconf_pkgdir"
*** using --with-strconf-pkgdir, however, the corresponding source
*** directory,
***	"$srcdir/$strconf_dir"
*** does not exist.  This cannot be correct.  Please specify the correct
*** directory with the configure option --with-strconf-pkgdir, or create
*** the corresponding source directory before calling configure again.
***])
	    fi
	    # might need to create the build directory
	    test -d "./$strconf_dir" || (umask 077 && mkdir -p $strconf_dir)
	    strconf_cv_packagedir="$strconf_dir"
	    ;;
	esac
    else
	strconf_dir='pkg'
	if test -d "$srcdir/$strconf_dir" ; then
	    test -d "./$strconf_dir" || (umask 077 && mkdir -p $strconf_dir)
	    strconf_cv_packagedir="$strconf_dir"
	fi
    fi
    AC_MSG_RESULT([$strconf_cv_packagedir])
    STRCONF_BPKGDIR="$strconf_cv_packagedir"
    AM_CONDITIONAL([WITH_PACKAGES], [test :${strconf_cv_packagedir:-no} != :no])dnl
    AC_ARG_WITH([strconf-pkgrules],
	[AS_HELP_STRING([--with-strconf-pkgrules=FILENAME],
	    [package make rules file @<:@default=pkgrules@:>@])])
    AC_CACHE_CHECK([for strconf rules file], [strconf_cv_pkgrules], [dnl
	if test "${with_strconf_pkgrules:-no}" != :no ; then
	    strconf_cv_pkgrules="$with_strconf_pkgrules"
	fi
    ])
    STRCONF_PKGRULE="${strconf_cv_pkgrules:-pkgrules}"
])# _STRCONF_SETUP
# =============================================================================

# =============================================================================
# _STRCONF_OUTPUT_CONFIG_COMMANDS
# -------------------------------------------------------------------------
# The point of deferring the search for configuration files is so that we can
# generate configuration files as output from autoconf before using the
# strconf script to generate the output files.
# -------------------------------------------------------------------------
AC_DEFUN([_STRCONF_OUTPUT_CONFIG_COMMANDS], [dnl
    AC_MSG_NOTICE([searching for $STRCONF_INPUT input files in  $ac_srcdir and $ac_builddir])
    ac_pkgdir=
    if test :"${STRCONF_BPKGDIR:+set}" = :set ; then
	case $STRCONF_BPKGDIR in
	    (.*|/*) # non vpath directory specification, use specified
	    ac_pkgdir="$STRCONF_BPKGDIR"
	    ac_pkg_srcdir=
	    ac_pkg_builddir=
	    ;;
	    (*) # vpath directory specification, relative to src and build
	    ac_pkgdir=
	    ac_pkg_srcdir="$ac_srcdir/$ac_pkgdir"
	    ac_pkg_builddir="$ac_builddir/$ac_pkgdir"
	    ;;
	esac
    fi
    # need absolute directory names so that we can get rid of duplicates
    ac_abs_srcdir=`(cd $ac_srcdir ; /bin/pwd)`
    ac_abs_builddir=`(cd $ac_builddir ; /bin/pwd)`
    if test -z "$ac_pkgdir" ; then
	ac_abs_pkgdir=
    else
	ac_abs_pkgdir=`(cd $ac_pkgdir ; /bin/pwd)`
    fi
    strconf_list="`find ${ac_abs_srcdir:+$ac_abs_srcdir/} ${ac_abs_builddir:+$ac_abs_builddir/} ${ac_abs_pkgdir:+$ac_abs_pkgdir/} -type f -name \"$STRCONF_STEM\" | sort -u`"
    strconf_configs=
    ac_abs_srcdir_mask="^`echo $ac_abs_srcdir | sed -e 's|.|.|g'`"
    ac_abs_builddir_mask="^`echo $ac_abs_builddir | sed -e 's|.|.|g'`"
    ac_abs_pkgdir_mask="^`echo $ac_abs_pkgdir | sed -e 's|.|.|g'`"
    for strconf_tmp in $strconf_list ; do
	# skip lower level build directories in list (to avoid duplicates)
	# skip subtending debian build directories as well
	case $strconf_tmp in
	    ("$ac_abs_builddir"/debian/* | "$ac_abs_builddir"/*/debian/*) continue ;;
	    ("$ac_abs_builddir"/_build/* | "$ac_abs_builddir"/*/_build/*) continue ;;
	    ("$ac_abs_builddir"/_install/* | "$ac_abs_builddir"/*/_install/*) continue ;;
	    ("$ac_abs_builddir/${PACKAGE}"/* | "$ac_abs_builddir/"*/"${PACKAGE}"/*) continue ;;
	    ("$ac_abs_builddir/${PACKAGE}-${VERSION}"/* | "$ac_abs_builddir/"*/"${PACKAGE}-${VERSION}"/*) continue ;;
	    ("$ac_abs_builddir/${PACKAGE}-bin-${VERSION}"/* | "$ac_abs_builddir/"*/"${PACKAGE}-bin-${VERSION}"/*) continue ;;
	    ("$ac_abs_builddir/${PACKAGE_LCNAME}"/* | "$ac_abs_builddir/"*/"${PACKAGE_LCNAME}"/*) continue ;;
	    ("$ac_abs_builddir/${PACKAGE_LCNAME}-${VERSION}"/* | "$ac_abs_builddir/"*/"${PACKAGE_LCNAME}-${VERSION}"/*) continue ;;
	    ("$ac_abs_builddir/${PACKAGE_LCNAME}-bin-${VERSION}"/* | "$ac_abs_builddir/"*/"${PACKAGE_LCNAME}-bin-${VERSION}"/*) continue ;;
	esac
	# convert back to relative
	if test -n "$ac_abs_builddir" ; then
	    case $strconf_tmp in
		("$ac_abs_builddir"/*)
		strconf_tmp=`echo $strconf_tmp | sed -e 's|'$ac_abs_builddir_mask'|'$ac_builddir'|'`
		;;
	    esac
	fi
	if test -n "$ac_abs_srcdir" ; then
	    case $strconf_tmp in
		("$ac_abs_srcdir"/*)
		strconf_tmp=`echo $strconf_tmp | sed -e 's|'$ac_abs_srcdir_mask'|'$ac_srcdir'|'`
		;;
	    esac
	fi
	if test -n "$ac_abs_pkgdir" ; then
	    case $strconf_tmp in
		("$ac_abs_pkgdir"/*)
		strconf_tmp=`echo $strconf_tmp | sed -e 's|'$ac_abs_pkgdir_mask'|'$ac_pkgdir'|'`
		;;
	    esac
	fi
	if test -r "$strconf_tmp" ; then
	    strconf_configs="$strconf_tmp${strconf_configs:+ }${strconf_configs}"
	fi
    done
    STRCONF_INPUTS="$strconf_configs"
    AC_SUBST([STRCONF_INPUTS])
    if test -n "${strconf_configs}" -a -n "${STRCONF_INPUT}"; then
	AC_MSG_NOTICE([creating $STRCONF_INPUT])
	cat /dev/null > $STRCONF_INPUT
	strconf_tmp=
	for file in $strconf_configs ; do
	    AC_MSG_NOTICE([appending $file to  $STRCONF_INPUT])
	    basename=`echo $file | sed -e 's|^.*/||'`
	    dirname=`echo $file | sed -e 's|/[[^/]]*$||'`
	    absdir=`( cd $dirname/ ; /bin/pwd )`
	    abspath="$absdir/$basename"
	    strconf_tmp=${strconf_tmp:+$strconf_tmp }$file
	done
	$AWK '
BEGIN { print "# Created by " me " -- DO NOT EDIT" }
(FNR == 1) { print "file " FILENAME; SKIPPING = 0 }
/^# / { print; next }
/^$/ || /^#/ { SKIPPING = 1; next }
(SKIPPING == 1) { SKIPPING = 0; print "line " FNR }
{ print }
END   { print "# Created by " me " -- DO NOT EDIT" }' \
	me="$as_me" $strconf_tmp > "$tmp/Config.master"
	if diff "$STRCONF_INPUT" "$tmp/Config.master" >/dev/null 2>&1; then
	    AC_MSG_NOTICE([$STRCONF_INPUT is unchanged])
	    rm -f "$tmp/Config.master"
	else
	    rm -f "$STRCONF_INPUT"
	    mv "$tmp/Config.master" "$STRCONF_INPUT"
	fi
	if test :"${STRCONF_CONFIG:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_CONFIG])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --hconfig=$STRCONF_CONFIG $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_MODCONF:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_MODCONF])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --modconf=$STRCONF_MODCONF $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_MKNODES:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_MKNODES])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --makenodes=$STRCONF_MKNODES $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_DRVCONF:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_DRVCONF])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --driverconf=$STRCONF_DRVCONF $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_CONFMOD:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_CONFMOD])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --confmodules=$STRCONF_CONFMOD $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_MAKEDEV:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_MAKEDEV])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --strmknods=$STRCONF_MAKEDEV $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_STSETUP:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_STSETUP])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --strsetup=$STRCONF_STSETUP $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_STRLOAD:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_STRLOAD])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --strload=$STRCONF_STRLOAD $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_DEVICES:+set}" = :set; then
	    AC_MSG_NOTICE([creating $STRCONF_DEVICES])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --mkdevices=$STRCONF_DEVICES $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	fi
	if test :"${STRCONF_BPKGDIR:+set}" = :set ; then
	    AC_MSG_NOTICE([creating $STRCONF_BPKGDIR])
	    eval "$STRCONF --package=${STRCONF_PACKAGE} -B${STRCONF_MINORSZ} -b${STRCONF_MAJBASE} -i${STRCONF_MIDBASE} --packagedir=$STRCONF_BPKGDIR --pkgrules=${STRCONF_PKGRULE}.in $STRCONF_INPUT" 2>&1 | \
	    while read line ; do
		echo "$as_me:$LINENO: $line" >&5
		echo "$as_me: $line" >&2
	    done
	    subcmd=
	    for sub in $tmp/subs-[[0-9]].sed ; do
		if test -f $sub ; then
		    subcmd="$subcmd"'| sed -f "'"$sub"'" '
		fi
	    done
	    if test -n "$subcmd" ; then
		AC_MSG_NOTICE([creating $STRCONF_PKGRULE])
		eval "cat \${STRCONF_PKGRULE}.in $subcmd >\${STRCONF_PKGRULE}"
	    fi
	fi
    fi
])# _STRCONF_OUTPUT_CONFIG_COMMANDS
# =============================================================================

# =============================================================================
# _STRCONF_OUTPUT_CONFIG
# -------------------------------------------------------------------------
AC_DEFUN([_STRCONF_OUTPUT_CONFIG], [dnl
    AC_CONFIG_COMMANDS([strconf],
	[_STRCONF_OUTPUT_CONFIG_COMMANDS], [dnl
ac_aux_dir="$ac_aux_dir"
PACKAGE="$PACKAGE"
VERSION="$VERSION"
PACKAGE_TARNAME="$PACKAGE_TARNAME"
PACKAGE_VERSION="$PACKAGE_VERSION"
PACKAGE_RELEASE="$PACKAGE_RELEASE"
PACKAGE_PATCHLEVEL="$PACKAGE_PATCHLEVEL"
STRCONF="$STRCONF"
STRCONF_STEM="$STRCONF_STEM"
STRCONF_SCRIPT="$STRCONF_SCRIPT"
STRCONF_INPUT="$STRCONF_INPUT"
STRCONF_INPUTS="$STRCONF_INPUTS"
STRCONF_MAJBASE="$STRCONF_MAJBASE"
STRCONF_MIDBASE="$STRCONF_MIDBASE"
STRCONF_CONFIG="$STRCONF_CONFIG"
STRCONF_MODCONF="$STRCONF_MODCONF"
STRCONF_MKNODES="$STRCONF_MKNODES"
STRCONF_DRVCONF="$STRCONF_DRVCONF"
STRCONF_CONFMOD="$STRCONF_CONFMOD"
STRCONF_MAKEDEV="$STRCONF_MAKEDEV"
STRCONF_STSETUP="$STRCONF_STSETUP"
STRCONF_STRLOAD="$STRCONF_STRLOAD"
STRCONF_DEVICES="$STRCONF_DEVICES"
STRCONF_BPKGDIR="$STRCONF_BPKGDIR"
STRCONF_PKGRULE="$STRCONF_PKGRULE"
STRCONF_PACKAGE="$STRCONF_PACKAGE"
STRCONF_MINORSZ="$STRCONF_MINORSZ"
    ])
])# _STRCONF_OUTPUT_CONFIG
# =============================================================================

# =============================================================================
# _STRCONF_OUTPUT
# -----------------------------------------------------------------------------
AC_DEFUN([_STRCONF_OUTPUT], [dnl
	AC_SUBST([STRCONF])dnl
	AC_SUBST([STRCONF_STEM])dnl
	AC_SUBST([STRCONF_SCRIPT])dnl
	AC_SUBST([STRCONF_INPUT])dnl
	AC_SUBST([STRCONF_INPUTS])dnl
	AC_SUBST([STRCONF_CONFIGS])dnl
	AC_SUBST([STRCONF_MAJBASE])dnl
	AC_SUBST([STRCONF_MIDBASE])dnl
	AC_SUBST([STRCONF_CONFIG])dnl
	AC_SUBST([STRCONF_MODCONF])dnl
	AC_SUBST([STRCONF_MKNODES])dnl
	AC_SUBST([STRCONF_DRVCONF])dnl
	AC_SUBST([STRCONF_CONFMOD])dnl
	AC_SUBST([STRCONF_MAKEDEV])dnl
	AC_SUBST([STRCONF_STSETUP])dnl
	AC_SUBST([STRCONF_STRLOAD])dnl
	AC_SUBST([STRCONF_DEVICES])dnl
	AC_SUBST([STRCONF_BPKGDIR])dnl
	AC_SUBST([STRCONF_PKGRULE])dnl
	AC_SUBST([STRCONF_PACKAGE])dnl
	AC_SUBST([STRCONF_MINORSZ])dnl
	AC_SUBST([STRMAKENODES])dnl
	_STRCONF_OUTPUT_CONFIG
])# _STRCONF_OUTPUT
# =============================================================================

# =============================================================================
#
# $Log: strconf.m4,v $
# Revision 1.1.2.4  2011-02-07 04:48:32  brian
# - updated configure and build scripts
#
# Revision 1.1.2.3  2009-07-23 16:37:50  brian
# - updates for release
#
# Revision 1.1.2.2  2009-07-21 11:06:13  brian
# - changes from release build
#
# Revision 1.1.2.1  2009-06-22 03:53:38  brian
# - added files to new distro
#
# Revision 0.9.2.48  2008-10-31 06:54:51  brian
# - move config files, better strconf handling
#
# Revision 0.9.2.47  2008-09-20 11:17:14  brian
# - build system updates
#
# Revision 0.9.2.46  2008-04-28 09:41:04  brian
# - updated headers for release
#
# Revision 0.9.2.45  2007/08/12 19:05:32  brian
# - rearrange and update headers
#
# =============================================================================
# 
# Copyright (c) 2008-2011  Monavacon Limited <http://www.monavacon.com/>
# Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>
# 
# =============================================================================
# ENDING OF SEPARATE COPYRIGHT MATERIAL
# =============================================================================
# vim: ft=config sw=4 noet nocin nosi com=b\:#,b\:dnl,b\:***,b\:@%\:@ fo+=tcqlorn
