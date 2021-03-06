/*
 @(#) $RCSfile: ContinueReqEvent.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:34:31 $ <p>
 
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
 
 Last Modified $Date: 2009-06-21 11:34:31 $ by $Author: brian $
 */

package jain.protocol.ss7.tcap.dialogue;

import jain.protocol.ss7.tcap.*;
import jain.protocol.ss7.*;
import jain.*;

/**
  * An event representing a TCAP Continue request dialogue primitive.
  * This event will be passed from the Listener (the TC User) to the
  * Provider (TCAP) to trigger the sending of components to the
  * destination node.  This primitive is used to continue a transaction
  * with the destination node. <br>
  * The mandatory parameters of this primitive are supplied to the
  * constructor. Optional parameters may then be set using the set
  * methods. <p>
  * The optional parameters 'Application Context Name' and 'User
  * Information' are centrally located in the Dialogue Portion class,
  * therefore to manipulate them it is necessary to instantiate the
  * Dialogue Portion Object and use the acessors method for the two
  * parameters in that Dialogue Portion Object.
  * @version 1.2.2
  * @author Monavacon Limited
  * @see DialogueReqEvent
  */
public final class ContinueReqEvent extends DialogueReqEvent {
    /** Constructs a new ContinueReqEvent, with only the Event Source
      * and the JAIN TCAP Mandatory parameter being supplied to the
      * constructor.
      * @param source
      * The Event Source supplied to the constructor.
      * @param dialogueId
      * The Dialogue Identifier supplied to the constructor.  */
    public ContinueReqEvent(java.lang.Object source, int dialogueId) {
        super(source);
        setDialogueId(dialogueId);
    }
    /** Sets the Originating Address parameter of the Continue Request
      * primitive. Origination Address is an SCCP parameter that is
      * required from the application. Within this method
      * TcapUserAddress has been changed to SccpUserAddress. The method
      * has not been deprecated as a new method using type
      * SccpUserAddress would have to be created with a different method
      * name. This is less desirable than the effective removal of the
      * old method.
      * @param originatingAddress
      * The new Originating Address value.  */
    public void setOriginatingAddress(SccpUserAddress originatingAddress) {
        m_originatingAddress = originatingAddress;
        m_originatingAddressPresent = true;
    }
    /** Sets the Allowed Permission parameter of the Begin dialogue
      * primitive. The Allowed Permission parameter indicates whether or
      * not permission is to be granted to the remote TC-User to
      * terminate this dialogue. <p>
      * Permission should not be granted whenever the sending TC-User
      * anticipates sending more components that it would like the
      * TC-User at the receiving node to treat as part of the same
      * transaction. <p>
      * Permission should be granted when the converse applies. <p>
      * <em>Note to developers:</em> Permission to end (release) a
      * transaction is an ANSI concept only.
      * @param allowedPermission
      * The new Allowed Permission Flag.  */
    public void setAllowedPermission(boolean allowedPermission) {
        m_allowedPermission = allowedPermission;
        m_allowedPermissionPresent = true;
    }
    /** Indicates if the Originating Address parameter is present in
      * this Event.
      * @return
      * True if Originating Address has been set, false otherwise.  */
    public boolean isOriginatingAddressPresent() {
        return m_originatingAddressPresent;
    }
    /** Gets the Originating Address parameter of the Continue request
      * primitive. Origination Address is an SCCP parameter that is
      * required from the application. The return type of this get
      * method has been changed from TcapUserAddress. The
      * TcapUserAddress class has been deprecated in this release
      * (V1.1). This method has not been deprecated as it's replacement
      * would then have to have a different name.
      * @return
      * The SccpUserAddress representing the Originating Address of the
      * Continue Request Event.
      * @exception ParameterNotSetException
      * This exception is thrown if this parameter has not yet been set.  */
    public SccpUserAddress getOriginatingAddress()
        throws ParameterNotSetException {
        if (m_originatingAddressPresent)
            return m_originatingAddress;
        throw new ParameterNotSetException("Originating Address: not set.");
    }
    /** Indicates if the Allowed Permission parameter is present in this
      * Event.
      * @return
      * True if Allowed Permission Id has been set, false otherwise.  */
    public boolean isAllowedPermissionPresent() {
        return m_allowedPermissionPresent;
    }
    /** Gets the Allowed Permission parameter of the Begin dialogue
      * primitive. The Allowed Permission parameter indicates whether or
      * not permission is to be granted to the remote TC-User to
      * terminate this dialogue. <p>
      * Permission should not be granted whenever the sending TC-User
      * anticipates sending more components that it would like the
      * TC-User at the receiving node to treat as part of the same
      * transaction. <p>
      * Permission should be granted when the converse applies. <p>
      * <em>NOTE:</em> permission to end (release) a transaction is an
      * ANSI concept only.
      * @return
      * Whether permission to release has been granted. This may be
      * either: <ul>
      * <li>true if the destination node has the permission to end the
      * dialogue;
      * <li>false if the destination node has not the permission to end
      * the dialogue. </ul>
      * @exception ParameterNotSetException
      * This exception is thrown if this parameter has not yet been set.  */
    public boolean isAllowedPermission()
        throws ParameterNotSetException {
        if (m_allowedPermissionPresent)
            return m_allowedPermission;
        throw new ParameterNotSetException("Allowed Permission: not set.");
    }
    /** This method returns the type of this primitive.
      * @return
      * The Primitive Type of this Event.  */
    public int getPrimitiveType() {
        return jain.protocol.ss7.tcap.TcapConstants.PRIMITIVE_CONTINUE;
    }
    /** Clears all previously set parameters.  */
    public void clearAllParameters() {
        m_dialoguePortionPresent = false;
        m_dialogueIdPresent = false;
        m_originatingAddressPresent = false;
        m_qualityOfServicePresent = false;
        m_allowedPermissionPresent = false;
    }
    /** java.lang.String representation of class ContinueReqEvent.
      * @return
      * java.lang.String provides description of class ContinueReqEvent.  */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append("\n\nContinueReqEvent");
        b.append(super.toString());
        b.append("\n\tm_originatingAddress = ");
        if (m_originatingAddress != null)
            b.append(m_originatingAddress.toString());
        b.append("\n\tm_allowedPermission = " + m_allowedPermission);
        b.append("\n\tm_allowedPermissionPresent = " + m_allowedPermissionPresent);
        b.append("\n\tm_originatingAddressPresent = " + m_originatingAddressPresent);
        return b.toString();
    }
    /** The Originating User Address parameter of the Continue request
      * dialogue primitive.
      * @serial m_originatingAddress
      * - a default serializable field.  */
    private SccpUserAddress m_originatingAddress = null;
    /** The Allowed Permission parameter of the Continue dialogue
      * primitive.
      * @serial m_allowedPermission
      * - a default serializable field.  */
    private boolean m_allowedPermission = false;
    /** Whether Allowed Permission is present.
      * @serial m_allowedPermissionPresent
      * - a default serializable field.  */
    private boolean m_allowedPermissionPresent = false;
    /** Whether Originating Address is present.
      * @serial m_originatingAddressPresent
      * - a default serializable field.  */
    private boolean m_originatingAddressPresent = false;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
