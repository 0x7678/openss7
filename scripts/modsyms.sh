#!/bin/bash
# =============================================================================
#
# @(#) $RCSfile: modsyms.sh,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2009-06-21 12:41:53 $
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
# Last Modified $Date: 2009-06-21 12:41:53 $ by $Author: brian $
#
# =============================================================================

ECHO='echo'
SHELL=${CONFIG_SHELL:-/bin/sh}
SED='sed'

# Check that we have a working $ECHO.
if test "X$1" = X--no-reexec; then
    # Discard the --no-reexec flag, and continue
    shift
elif test "X`($ECHO '\t') 2>/dev/null`" = 'X\t'; then
    :
else
    exec $SHELL "$0" --no-reexec ${1+"$@"}
fi

if test "X$1" = X--fallback-echo ; then
    shift
    cat <<EOF
$*
EOF
    exit 0
fi

program=`$ECHO "$0" | ${SED} -e 's%^.*/%%'`
modename="$program"
reexec="$SHELL $0"

version="3.0.0"
ident='$RCSfile: modsyms.sh,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2009-06-21 12:41:53 $'

# Sed substitution that helps us do robust quoting.  It backslashifies
# metacharacters that are still active within double-quoted strings.
Xsed="${SED}"' -e 1s/^X//'
sed_quote_subst='s/\([\\`\\"$\\\\]\)/\\\1/g'
# test EBCDIC or ASCII
case `$ECHO A|od -x` in
 *[Cc]1*) # EBCDIC based system
  SP2NL="tr '\100' '\n'"
  NL2SP="tr '\r\n' '\100\100'"
  ;;
 *) # Assume ASCII based system
  SP2NL="tr '\040' '\012'"
  NL2SP="tr '\015\012' '\040\040'"
  ;;
esac

# NLS nuisances.
# Only set LANG and LC_ALL to C if already set.
# These must not be set unconditionally because not all systems understand
# e.g. LANG=C (notably SCO).
# We save the old values to restore during execute mode.
if test "${LC_ALL+set}" = set; then
  save_LC_ALL="$LC_ALL"; LC_ALL=C; export LC_ALL
fi
if test "${LANG+set}" = set; then
  save_LANG="$LANG"; LANG=C; export LANG
fi

# Make sure IFS has a sensible default
: ${IFS=" 	"}

modsyms_letters='abcdefghijklmnopqrstuvwxyz'
modsyms_LETTERS='ABCDEFGHIJKLMNOPQRSTUVWXYZ'
modsyms_Letters=$modsyms_letters$modsyms_LETTERS
modsyms_numbers='0123456789'
modsyms_alphano=$modsyms_Letters$modsyms_numbers
modsyms_uppercase="$SED y%*$modsyms_letters%P$modsyms_LETTERS%;s%[^_$modsyms_alphano]%_%g"

modsyms_tokenize="$SED s%[^a-zA-Z0-9]%_%g"

# defaults

defaults="sysmap vmlinux moddir"

default_sysmap=/boot/System.map-`uname -r`
default_vmlinux=/lib/modules/`uname -r`/build/vmlinux
default_moddir=/lib/modules/`uname -r`

command=
debug=0
verbose=1

version ()
{
    if test ${show:-yes} = no ; then
	return
    fi
    cat <<EOF
Version $version
$ident
Copyright (c) 2008-2011  Monavacon Limited.  All Rights Reserved.
Distributed under AGPL Version 3, included here by reference.
See \`$program --copying' for copying permissions.
EOF
}

usage ()
{
    if test ${show:-yes} = no ; then
	return
    fi
    cat <<EOF
$program:
    $ident
Usage:
    $program [options] [MODULE ...]
    $program {-h|--help}
    $program {-V|--version}
    $program {-C|--copying}
EOF
}

help ()
{
    if test ${show:-yes} = no ; then
	return
    fi
    usage
    cat <<EOF
Arguments:
    MODULE ...
        modules for which to generate symbols
        ['$modules_set']
Options:
    -d, --moddir MODDIR
        module directory
        ['$moddir']
    -F, --filename SYSMAP
        specify system map file
        ['$sysmap']
    -I, --image VMLINUX
        specify kernel image file
        ['$vmlinux']
    -n, --dryrun
        don't perform the actions, just check them
    -q, --quiet
        suppress normal output
    -D, --debug [LEVEL]
        increase or set debugging verbosity
    -v, --verbose [LEVEL]
        increase or set output verbosity
    -h, --help
        prints this usage information and exits
    -V, --version
        prints the version and exits
    -C, --copying
        prints copying permissions and exits
EOF
}

copying ()
{
    if test ${show:-yes} = no ; then
	return
    fi
    cat <<EOF
--------------------------------------------------------------------------------
$ident
--------------------------------------------------------------------------------
Copyright (c) 2008-2011  Monavacon Limited <http://www.monavacon.com/>
Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>

All Rights Reserved.
--------------------------------------------------------------------------------
This program is free software; you can  redistribute  it and/or modify  it under
the terms of the  GNU  Affero  General  Public  License as published by the Free
Software Foundation; version 3 of the License.

This program is distributed in the hope that it will  be useful, but WITHOUT ANY
WARRANTY; without even  the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the  GNU  Affero General Public License along
with this program.   If not, see <http://www.gnu.org/licenses/>, or write to the
Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
--------------------------------------------------------------------------------
U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on behalf
of the U.S. Government ("Government"), the following provisions apply to you. If
the Software is supplied by the  Department of Defense ("DoD"), it is classified
as "Commercial  Computer  Software"  under  paragraph  252.227-7014  of the  DoD
Supplement  to the  Federal Acquisition Regulations  ("DFARS") (or any successor
regulations) and the  Government  is acquiring  only the  license rights granted
herein (the license rights customarily provided to non-Government users). If the
Software is supplied to any unit or agency of the Government  other than DoD, it
is  classified as  "Restricted Computer Software" and the Government's rights in
the Software  are defined  in  paragraph 52.227-19  of the  Federal  Acquisition
Regulations ("FAR")  (or any successor regulations) or, in the cases of NASA, in
paragraph  18.52.227-86 of  the  NASA  Supplement  to the FAR (or any  successor
regulations).
--------------------------------------------------------------------------------
Commercial  licensing  and  support of this  software is  available from OpenSS7
Corporation at a fee.  See http://www.openss7.com/
--------------------------------------------------------------------------------
EOF
}

syntax_error ()
{
    if test ${verbose:-0} -gt 0 ; then
	$ECHO "$program: syntax error -- $1" >&2
	( usage ) >&2
    fi
    exit 2
}

option_unrec ()
{
    opt=`$ECHO -n "X$1" | $Xsed -e 's|=.*||'`
    syntax_error "\`$opt' unrecognized"
}

option_noarg ()
{
    opt=`$ECHO -n "X$1" | $Xsed -e 's|=.*||'`
    syntax_error "\`$opt' does not accept an argument"
}

option_needarg ()
{
    syntax_error "\`$1' requires an argument"
}

option_after ()
{
    syntax_error "\`$1' cannot occur after \`$2'"
}

option_with ()
{
    syntax_error "\`$1' cannot occur with \`$2'"
}

# Parse our command line options once, thoroughly.
while test "$#" -gt 0 -o ":$more" != ":"
do
    if test ":$more" != ":" ; then arg="-$more" ; more= ; else arg="$1" ; shift ; fi
    # check for attached option argument
    case $arg in
	(--filename=* | --filenam=* | --filena=* | --filen=* | --file=* | --fil=* | --fi=* | --f=* | \
	--image=* | --imag=* | --ima=* | --im=* | --i=* | \
	--moddir=*  | --moddi=*  | --modd=*  | --mod=*  | --mo=*  | --m=*)
	    optarg=`$ECHO "X$arg" | $Xsed -e 's/[-_a-zA-Z0-9]*=//'` ;;
	(--*=*)
	    option_noarg $arg ;;
	(-[nqDvhVC])
	    optarg= ;;
	(-[nqDvhVC]*)
	    optarg=
	    more=`$ECHO "X$arg" | $Xsed -e 's|-[nqDvhVC]||'`
	    eval "arg=\`$ECHO \"X$arg\" | $Xsed -e 's|$more||'\`"
	    ;;
	(-[FId])
	    optarg= ;;
	(-[FId]*)
	    optarg=`$ECHO "X$arg" | $Xsed -e 's|-[FId]||'` ;;
	(*)
	    optarg= ;;
    esac
    # check for optional or required option argument
    if test -n "$prev" ; then
	case $arg in
	    (-*) # optional arguments not forthcoming
		case $prev in
		    (debug | verbose) eval "(($prev++))" ;;
		    # the rest have required arguments
		    (sysmap | vmlinux | moddir)
			option_needarg $prevopt ;;
		esac
		prev= ; prevopt=
		;;
	    (*) # if the previous option needs an argument, assign it.
		eval "$prev=\"\$arg\""
		prev= ; prevopt=
		continue
		;;
	esac
    fi
    # Have we seen a non-optional argument yet?
    case $arg in
	(--help | --h | --Help | --H | -h | -H | -\? | --\?)
	    show_help=yes
	    if test ":$command" = ":" ; then command=none ; fi
	    ;;
	(--version | --versio | --versi | --vers | -V)
	    show_version=yes
	    if test ":$command" = ":" ; then command=none ; fi
	    ;;
	(--copying | --copyin | --copyi | --copy | --cop | --co | --c | -C)
	    show_copying=yes
	    if test ":$command" = ":" ; then command=none ; fi
	    ;;
	(--verbose | --verbos | --verbo | --verb)
	    prevopt="$arg"
	    prev=verbose
	    ;;
	(-v)
	    ((verbose++))
	    ;;
	(--verbose=* | --verbos=* | --verbo=* | --verb=*)
	    verbose="$optarg"
	    ;;
	(--debug | --debu | --deb)
	    prevopt="$arg"
	    prev=debug
	    ;;
	(-D)
	    $ECHO "$program: enabling shell trace mode" 1>&2
	    set -x
	    ;;
	(--debug=* | --debu=* | --deb=*)
	    debug="$optarg"
	    ;;
	(--dry-run | --dryrun | --n | -n)
	    run=no
	    ;;
	(--quiet | --silent | -q)
	    show=no
	    verbose=0
	    debug=0
	    ;;
	(--filename | --filenam | --filena | --filen | --file | --fis | --fi | --f | -F)
	    prevopt="$arg"
	    prev=sysmap
	    ;;
	(--filename=* | --filenam=* | --filena=* | --filen=* | --file=* | --fil=* | --fi=* | --f=* | -F*)
	    sysmap="$optarg"
	    ;;
	(--image | --imag | --ima | --im | --i | -I)
	    prevopt="$arg"
	    prev=vmlinux
	    ;;
	(--image=* | --imag=* | --ima=* | --im=* | --i=* | -I*)
	    vmlinux="$optarg"
	    ;;
	(--moddir | --moddi | --modd | --mod | --mo | --m | -d)
	    prevopt="$arg"
	    prev=moddir
	    ;;
	(--moddir=* | --moddi=* | --modd=* | --mod=* | --mo=* | --m=* | -d*)
	    moddir="$optarg"
	    ;;
	(--)
	    # end of options
	    break
	    ;;
	(-*)
	    option_unrec $arg
	    ;;
	(*)
	    nonopt="${nonopt}${nonopt:+ }'$arg'"
	    ;;
    esac
done

# hit end of list wanting arguments
case $prev in
    # these have optional arguments
    (debug | verbose) eval "(($prev++))" ;;
    # the rest have required arguments
    (sysmap | vmlinux | moddir)
	option_needarg $prevopt ;;
esac

# assign defaults to all unassigned variables
for d in $defaults ; do
	eval "test :\${$d+set} = :set || $d=\"\$default_$d\""
done

if test x"$nonopt${nonopt:+ }${1+$@}" != "x" ; then
    eval "modules=($nonopt${nonopt:+ }${1+$@})"
    modules_set="$modules"
else
    modules_set="all modules in $moddir"
fi

# assign all defaults
if test ":$command" = ":" ; then
    command=process
fi

default_modules="$(find $moddir -name '*.ko' -o -name '*.ko.gz' 2>/dev/null)"
test :${modules+set} = :set || modules="$default_modules"

if test $debug -gt 1 ; then
    exec 3>&2
else
    exec 3>/dev/null
fi

command_error() {
    $ECHO "$program: ERROR: ${1+@}" >&3
}

command_info() {
    $ECHO "$program: INFO: ${1+@}" >&3
}

process_map() {
	modname="$1"
	test -n "$modname" || { command_error "no module name" ; return 1 ; }
	shift
	while read crc flag expsym junk ; do
		test -z "$junk" || { command_error "got junk $junk" ; continue ; }
		$ECHO "$expsym" | egrep -q '^(_)?__crc_' &>/dev/null || { command_error "not crc symbol $expsym" ; continue ; }
		test :$flag = :A || { command_error "wrong flag $flag" ; continue ; }
		symbol=`$ECHO "$expsym" | sed -r -e 's|^(_)?__crc_||'`
		test -n "$symbol" || { command_error "no symbol for $expsym" ; continue ; }
		printf "0x%08x\t%s\t%s\n" "0x$crc" $symbol $modname
	done
}

process_kobject() {
	filename="$1"
	shift
	test -n "$filename" -a -f "$filename" || return 1
	# not all files have appropriate symbols
	zgrep -E -qcm1 '\<(_)?__crc_' $filename || return 0
	basename=`basename $filename`
	koname=`basename $basename .gz`
	modname=`basename $koname .ko`
	test -n "$modname" || return 1
	if test :$basename != :$koname ; then
		# shoot, we have a .gz ending
		file=".tmp.$$.$modname.ko"
		remv="$file"
		gzip -dc $filename > $file
	else
		file="$filename"
		remv=
	fi
	command_info "processing file $filename"
	nm -s $file | egrep '\<(_)?__crc_' | process_map $modname
	test -n "$remv" && rm -f -- $remv
}

process_sysmap() {
	sysmap="$1"
	shift
	test -n "$sysmap" -a -f "$sysmap" || return 1
	command_info "processing system map $filename"
	egrep '\<(_)?_crc_' $sysmap | process_map vmlinux

}

process_vmlinux() {
	vmlinux="$1"
	shift
	test -n "$vmlinux" -a -f "$vmlinux" || return 1
	basename=`basename $vmlinux`
	imgname=`basename $basename .gz`
	test -n "$imgname" || return 1
	if test :$basename != :$imgname ; then
	    # shoot, we have a .gz ending
	    file=".tmp.$$.$imgname"
	    remv="$file"
	    gzip -dc $vmlinux > $file
	else
	    file="$vmlinux"
	    remv=
	fi
	command_info "processing vmlinux $vmlinux"
	nm -s $file | egrep '\<(_)?__crc_' | process_map vmlinux
	test -n "$remv" && rm -f -- $remv
}

process_command() {
    for mod in $modules ; do
	    process_kobject $mod
    done
    process_sysmap $sysmap
    process_vmlinux $vmlinux
}


none_command ()
{
    if test -n "$show_version$show_help$show_copying" ; then
	if test ${verbose:-0} -gt 1 ; then
	    $ECHO "Displaying information"
	fi
	if test ":$show_version" != ":" ; then
	    version
	fi
	if test ":$show_help" != ":" ; then
	    help
	fi
	if test ":$show_copying" != ":" ; then
	    copying
	fi
    fi
}

case "$command" in
    (none|process)
	eval "${command}_command"
	;;
    *)
	( usage ) >&2
	exit 1
	;;
esac

exit 0

# =============================================================================
#
# $Log: modsyms.sh,v $
# Revision 1.1.2.2  2009-06-21 12:41:53  brian
# - updated headers
#
# Revision 1.1.2.1  2009-06-21 11:16:41  brian
# - added files to new distro
#
# Revision 0.9.2.10  2008-04-28 09:23:11  brian
# - updated script headers for release
#
# Revision 0.9.2.9  2007/08/12 18:08:02  brian
# - more header corrections
#
# Revision 0.9.2.8  2007/08/12 17:47:21  brian
# - updated script headers
#
# =============================================================================
# vim: ft=sh sw=4
