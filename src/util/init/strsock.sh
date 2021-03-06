#!/bin/sh
#
# @(#) $RCSfile: strsock.sh,v $ $Name:  $($Revision: 1.1.2.3 $) $Date: 2011-05-10 13:45:37 $
# Copyright (c) 2001-2011  OpenSS7 Corporation <http://www.openss7.com>
# Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>
# All Rights Reserved.
#
# Distributed by OpenSS7 Corporation.  See the bottom of this script for copying
# permissions.
#
# These are arguments to update-rc.d ala chkconfig and lsb.  They are recognized
# by openss7 install_initd and remove_initd scripts.  Each line specifies
# arguments to add and remove links after the the name argument:
#
# strsock:	start and stop strsock modules
# update-rc.d:	start 33 S .
# config:	/etc/default/strsock
# probe:	false
# hide:		false
# license:	GPL
# description:	This STREAMS init script is part of Linux Fast-STREAMS.  \
#		It is responsible for ensuring that the necessary STREAMS \
#		SOCK character devices are present in the /dev directory and \
#		that the STREAMS SOCK kernel modules are configured and loaded.
#
# LSB init script conventions
#
### BEGIN INIT INFO
# Provides: strsock
# Required-Start: streams $network
# Required-Stop: streams $network
# Should-Start: strerr strace
# Should-Stop: strerr strace
# Default-Start: S
# Default-Stop:
# X-UnitedLinux-Default-Enabled: yes
# Short-Description: start and stop STREAMS Binary Compatibility Modules
# License: GPL
# Description:	This STREAMS SOCK init script is part of Linux Fast-STREAMS.
#	It is reponsible for ensuring that the necessary STREAMS SOCK character
#	devices are present in the /dev directory and that the STREAMS SOCK
#	kernel modules are configured and loaded.
### END INIT INFO

PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin
name='strsock'
config="/etc/default/$name"
desc="the STREAMS SOCK modules"
mknod="${name}_mknod"

[ -e /proc/modules ] || exit 0

if test -z "$STRSOCK_MKNOD" ; then
    for STRSOCK_MKNOD in /sbin/${mknod} /usr/sbin/${mknod} /bin/${mknod} /usr/bin/${mknod} ; do
	if [ -x $STRSOCK_MKNOD ] ; then
	    break
	else
	    STRSOCK_MKNOD=
	fi
    done
fi

# Specify defaults

[ -n "$STRSOCK_PRELOAD"       ] || STRSOCK_PRELOAD=""
[ -n "$STRSOCK_DRIVERS"       ] || STRSOCK_DRIVERS="streams-socksys"
[ -n "$STRSOCK_MODULES"       ] || STRSOCK_MODULES="streams-sockmod"
[ -n "$STRSOCK_MAKEDEVICES"   ] || STRSOCK_MAKEDEVICES="yes"
[ -n "$STRSOCK_REMOVEDEVICES" ] || STRSOCK_REMOVEDEVICES="yes"

# Source config file
for file in $config ; do
    [ -f $file ] && . $file
done

[ -z "$STRSOCK_MKNOD" ] && STRSOCK_MAKEDEVICES="no"
[ -z "$STRSOCK_MKNOD" ] && STRSOCK_REMOVEDEVICES="no"

RETVAL=0

umask 077

case :$VERBOSE in
    :no|:NO|:false|:FALSE|:0|:)
	redir='>/dev/null 2>&1'
	;;
    *)
	redir=
	;;
esac

build_options() {
    # Build up the options string
    :
}

start() {
    echo -n "Loading STREAMS kernel modules: "
    RETVAL=0
    modules=
    for module in $STRSOCK_PRELOAD ; do
	modules="${modules:+$modules }$module"
    done
    for module in $modules ; do
	modrex=`echo $module | sed -e 's,[-_],[-_],g'`
	if ! eval "grep '^$modrex\>' /proc/modules $redir" ; then
	    echo -n "$module "
	    eval "modprobe -q -- $module $redir"
	    [ $? -eq 0 ] || echo -n "(failed)"
	fi
    done
    echo "."

    echo -n "Starting $desc: $name "
    build_options
    if [ $? -eq 0 ] ; then
	echo "."
    else
	echo "(failed.)"
	RETVAL=1
    fi

    if eval "grep '^[[:space:]]*${name}[/.]' /etc/sysctl.conf $redir" ; then
	echo -n "Reconfiguring kernel parameters: "
	eval "sysctl -p /etc/sysctl.conf $redir"
	if [ $? -eq 0 ] ; then
	    echo "."
	else
	    echo "(failed.)"
	fi
    fi

    if [ -f /etc/${name}.conf ] ; then
	echo -n "Configuring STREAMS parameters: "
	eval "sysctl -p /etc/${name}.conf $redir"
	if [ $? -eq 0 ] ; then
	    echo "."
	else
	    echo "(failed.)"
	    RETVAL=1
	fi
    fi

    if [ -n "$STRSOCK_MKNOD" -a :"$STRSOCK_MAKEDEVICES" = ":yes" ] ; then
	echo -n "Making STREAMS SOCK devices: "
	$STRSOCK_MKNOD
	if [ $? -eq 0 ] ; then
	    echo "."
	else
	    echo "(failed.)"
	    RETVAL=1
	fi
    fi
    return $RETVAL
}

stop() {
    echo "Stopping $desc: $name "
    RETVAL=0
    if [ -n "$STRSOCK_MKNOD" -a ":$STRSOCK_REMOVEDEVICES" = ":yes" ] ; then
	echo -n "Removing STREAMS devices: "
	$STRSOCK_MKNOD --remove
	if [ $? -eq 0 ] ; then
	    echo "."
	else
	    echo "(failed.)"
	    RETVAL=1
	fi
    fi
    echo -n "Unloading STREAMS kernel modules: "
    modules=
    for module in $STRSOCK_PRELOAD $STRSOCK_DRIVERS $STRSOCK_MODULES ; do
	modules="$module${modules:+ $modules}"
    done
    for module in $modules ; do
	modrex=`echo $module | sed -e 's,[-_],[-_],g'`
	if eval "grep '^$modrex\>' /proc/modules $redir" ; then
	    echo -n "$module "
	    eval "modprobe -r -q -- $module $redir"
	    if [ $? -ne 0 ] ; then
		echo -n "(failed) "
		RETVAL=1
	    fi
	fi
    done
    if [ $RETVAL -eq 0 ] ; then
	echo "."
    else
	echo "(failed.)"
    fi
    return $RETVAL
}

restart() {
    stop
    start
    return $?
}

show() {
    echo "$name.sh: show: not yet implemented." >&2
    return 1
}

usage() {
    echo "Usage: /etc/init.d/$name.sh (start|stop|restart|force-reload|show)" >&2
    return 1
}

case "$1" in
    (start|stop|restart|show)
	$1 || RETVAL=$?
	;;
    (force-reload)
	restart || RETVAL=$?
	;;
    (*)
	usage || RETVAL=$?
	;;
esac

[ "${0##*/}" = "$name.sh" ] && exit $RETVAL

# =============================================================================
# 
# @(#) $RCSfile: strsock.sh,v $ $Name:  $($Revision: 1.1.2.3 $) $Date: 2011-05-10 13:45:37 $
#
# -----------------------------------------------------------------------------
#
# Copyright (c) 2001-2011  OpenSS7 Corporation <http://www.openss7.com/>
# Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>
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
# Last Modified $Date: 2011-05-10 13:45:37 $ by $Author: brian $
#
# -----------------------------------------------------------------------------
#
# $Log: strsock.sh,v $
# Revision 1.1.2.3  2011-05-10 13:45:37  brian
# - weak modules workup
#
# Revision 1.1.2.2  2011-01-12 00:19:32  brian
# - modprobe no longer accepts k option
#
# Revision 1.1.2.1  2009-06-21 11:47:58  brian
# - added files to new distro
#
# Revision 0.9.2.11  2008-10-21 22:42:20  brian
# - handle verbose better in debian initscripts
#
# Revision 0.9.2.10  2008-04-28 22:33:35  brian
# - updated headers for release
#
# Revision 0.9.2.9  2007/08/14 05:17:31  brian
# - GPLv3 header update
#
# Revision 0.9.2.8  2007/03/08 22:42:45  brian
# - correct redirect
#
# Revision 0.9.2.7  2007/03/08 22:12:41  brian
# - update headers
#
# Revision 0.9.2.6  2007/03/08 22:08:10  brian
# - sense of VERBOSE reversed
#
# Revision 0.9.2.5  2007/03/08 20:25:08  brian
# - ubuntu looks for lsb info in init scripts
#
# Revision 0.9.2.4  2006/10/16 00:21:24  brian
# - do not load too many kernel modules on init
#
# Revision 0.9.2.3  2006/10/13 07:00:09  brian
# - load drivers but not modules by default, but remove modules
#
# Revision 0.9.2.2  2006/10/13 04:00:16  brian
# - corrected init scripts and config files
#
# Revision 0.9.2.1  2006/08/23 10:04:12  brian
# - started STREAMS Sockets package
#
#
# =============================================================================
# vim: ft=sh sw=4 tw=80
