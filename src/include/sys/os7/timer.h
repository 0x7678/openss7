/*****************************************************************************

 @(#) $Id: timer.h,v 1.1.2.2 2010-11-28 14:21:52 brian Exp $

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

 Last Modified $Date: 2010-11-28 14:21:52 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: timer.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:52  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:26:49  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __OS7_TIMER_H__
#define __OS7_TIMER_H__

#define SS7_DECLARE_TIMER(__n,__o,__t,__c) \
STATIC int __o ## _ ## __t ## _timeout(struct __o *); \
STATIC void streamscall __o ## _ ## __t ## _expiry(caddr_t data) \
{ \
	ss7_do_timeout(data, # __t, __n, &((struct __o *)data)->timers.__t, \
			(int (*)(struct head *))&__o ## _ ## __t ## _timeout, \
			&__o ## _ ## __t ## _expiry); \
} \
STATIC void __o ## _stop_timer_ ## __t (struct __o * __o) \
{ \
	ss7_stop_timer((struct head *)__o, # __t, __n, &__o->timers.__t); \
} \
STATIC void __o ## _start_timer_ ## __t (struct __o * __o) \
{ \
	ss7_start_timer((struct head *)__o, # __t, __n, &__o->timers.__t, &__o ## _ ## __t ## _expiry, __o->__c.__t); \
} \

static __inline__ streamscall void
ss7_do_timeout(caddr_t data, const char *timer, const char *mod, toid_t *timeo,
	       int (*to_fnc) (struct head *), void streamscall (*exp_func) (caddr_t))
{
	struct str *s = (struct str *) data;

	if (xchg(timeo, 0)) {
		if (spin_trylock(&s->qlock)) {
			if (s->users == 0) {
				printd(("%s: %p: %s timeout at %lu\n", mod, s, timer, jiffies));
				switch (to_fnc((struct head *)s)) {
				default:
				case QR_DONE:
					spin_unlock(&s->qlock);
					if (s->priv_put)
						s->priv_put(s);
					else
						printd(("%s: %p: object has no put procedure\n", mod, s));
					return;
				case -ENOMEM:
				case -ENOBUFS:
				case -EBUSY:
				case -EAGAIN:
					break;
				}
			}
			spin_unlock(&s->qlock);
		} else
			printd(("%s: %p: %s timeout collision at %lu\n", mod, s, timer, jiffies));
		/* back off timer two ticks */
		*timeo = timeout(exp_func, data, 2);
	}
}
static __inline__ streamscall void
ss7_stop_timer(struct head *h, const char *timer, const char *mod, toid_t *timeo)
{
	toid_t to;

	if ((to = xchg(timeo, 0))) {
		untimeout(to);
		printd(("%s: %p: stopping %s at %lu\n", mod, h, timer, jiffies));
		if (h->priv_put)
			h->priv_put(h);
		else
			printd(("%s: %p: object has no put procedure\n", mod, h));
	}
	return;
}
__OS7_EXTERN_INLINE streamscall void
ss7_start_timer(struct head *h, const char *timer, const char *mod, toid_t *timeo,
		void streamscall (*exp_func) (caddr_t), ulong val)
{
	printd(("%s: %p: starting %s %lu ms at %lu\n", mod, h, timer, val * 1000 / HZ, jiffies));
	if (h->priv_get)
		h->priv_get(h);
	else
		printd(("%s: %p: object has no get procedure\n", mod, h));
	*timeo = timeout(exp_func, (caddr_t) h, val);
}

#endif				/* __OS7_TIMER_H__ */
