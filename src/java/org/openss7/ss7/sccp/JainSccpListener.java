/*
 @(#) $RCSfile: JainSccpListener.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:36:47 $ <p>
 
 Copyright &copy; 2008-2009  Monavacon Limited <a href="http://www.monavacon.com/">&lt;http://www.monavacon.com/&gt;</a>. <br>
 Copyright &copy; 2001-2008  OpenSS7 Corporation <a href="http://www.openss7.com/">&lt;http://www.openss7.com/&gt;</a>. <br>
 Copyright &copy; 1997-2001  Brian F. G. Bidulock <a href="mailto:bidulock@openss7.org">&lt;bidulock@openss7.org&gt;</a>. <p>
 
 All Rights Reserved. <p>
 
 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license. <p>
 
 This program is distributed in the hope that it will be useful, but <b>WITHOUT
 ANY WARRANTY</b>; without even the implied warranty of <b>MERCHANTABILITY</b>
 or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.  See the GNU Affero General Public
 License for more details. <p>
 
 You should have received a copy of the GNU Affero General Public License along
 with this program.  If not, see
 <a href="http://www.gnu.org/licenses/">&lt;http://www.gnu.org/licenses/&gt</a>,
 or write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA. <p>
 
 <em>U.S. GOVERNMENT RESTRICTED RIGHTS</em>.  If you are licensing this
 Software on behalf of the U.S. Government ("Government"), the following
 provisions apply to you.  If the Software is supplied by the Department of
 Defense ("DoD"), it is classified as "Commercial Computer Software" under
 paragraph 252.227-7014 of the DoD Supplement to the Federal Acquisition
 Regulations ("DFARS") (or any successor regulations) and the Government is
 acquiring only the license rights granted herein (the license rights
 customarily provided to non-Government users).  If the Software is supplied to
 any unit or agency of the Government other than DoD, it is classified as
 "Restricted Computer Software" and the Government's rights in the Software are
 defined in paragraph 52.227-19 of the Federal Acquisition Regulations ("FAR")
 (or any successor regulations) or, in the cases of NASA, in paragraph
 18.52.227-86 of the NASA Supplement to the FAR (or any successor regulations). <p>
 
 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See
 <a href="http://www.openss7.com/">http://www.openss7.com/</a> <p>
 
 Last Modified $Date: 2009-06-21 11:36:47 $ by $Author: brian $
 */

package org.openss7.ss7.sccp;

/** This interface defines the methods required by all and any SCCP user
  * application to receive and process JAIN SCCP Events that are emitted
  * by an object implementing the
  * {@link org.openss7.ss7.sccp.JainSccpProvider} interface.
  * It must be noted that any object that implements the JainSccpListener
  * interface is referred to as a JainSccpListenerImpl; the JainSccpProvider, a
  * JainSccpProviderImpl.  The events emitted by JainSccpProviderImpl may be
  * {@link org.openss7.ss7.sccp.SccpEvent} events.  These events
  * correspond to SCCP indication and confirmation primitives emitted as
  * events by the JainSccpProviderImpl.  SCCP indication and confirmation
  * events represent SCCP service primitives that are sent from SCCP to
  * the SCCP User. <p>
  *
  * A SCCP User application will only receive indication events once it
  * has registered as an EventListener of a JainSccpProviderImpl.  The user
  * application will register with the JainSccpProviderImpl with a user
  * address by invoking the JainSccpProviderImpl's {@link
  * org.openss7.ss7.sccp.JainSccpProvider#addSccpListener} method.  Any
  * events addressed to a user address belonging to a user application
  * will be passed to that user application. <p>
  *
  * The user application will use the JainSccpProviderImpl to send SCCP
  * messages by sending {@link org.openss7.ss7.sccp.SccpEvent} events to
  * that JainSccpProviderImpl's {@link
  * org.openss7.ss7.sccp.JainSccpProvider#sendSccpEvent} method.
  *
  * @author     Monavacon Limited
  * @version    1.2.2
  * @see        JainSccpProvider
  */
public interface JainSccpListener extends java.util.EventListener {
    /** 
      * Process an SCCP Event emitted by the JainSccpProvider.
      * Indication events can only be passed from SCCP (the
      * JainSccpProviderImpl) to the SCCP User (JainSccpListenerImpl) and is
      * enforced by the JAIN SCCP Event hierarchy and error checking
      * within the specification, to ensure SCCP like processing.
      * @param event  The new event supplied by the method.
      */
    public void processSccpEvent(SccpEvent event);
    /** 
      * Adds a {@link org.openss7.ss7.sccp.SccpUserAddress} to the list
      * of user addresses used by a JainSccpListenerImpl.
      * A JainSccpListenerImpl may choose to register as an Event Listener of
      * a JainSccpProvider for all of its user addresses.  Any Sccp messages
      * addressed to any of this JainSccpListenerImpl's user addresses will
      * be passed to this JainSccpListenerImpl as events by the
      * JainSccpProviderImpl.
      */
    public void addUserAddress(SccpUserAddress userAddress)
        throws jain.protocol.ss7.UserAddressLimitException;
    /** 
      * Removes the {@link org.openss7.ss7.sccp.SccpUserAddress} from the
      * list of user addresses held by a JainSccpListenerImpl. */
    public void removeUserAddress(SccpUserAddress userAddress)
        throws jain.protocol.ss7.InvalidAddressException;
    /** 
      * Returns the list of {@link org.openss7.ss7.sccp.SccpUserAddress}
      * used by this JainSccpListenerImpl.
      * @return The SccpUserAddress[] of user addresses used by this
      * JainSccpListenerImpl.
      */
    public SccpUserAddress[] getUserAddressList()
        throws jain.protocol.ss7.UserAddressEmptyException;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
