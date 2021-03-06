/*
 @(#) $RCSfile: CallReference.java,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2011-09-02 08:46:47 $ <p>
 
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
 
 Last Modified $Date: 2011-09-02 08:46:47 $ by $Author: brian $
 */

package javax.jain.ss7.isup;

import javax.jain.ss7.*;
import javax.jain.*;

/** A class representing ISUP Call Reference parameter.
    This parameter is common to ITU and ANSI variant.

    @author Monavacon Limited
    @version 1.2.2
  */
public class CallReference implements java.io.Serializable {
    /** Constructs a new CallReference class, parameters with default values.  */
    public CallReference() {
    }
    /** Constructs a CallReference class from the input parameters specified.
      * @param in_callId  The call identity.
      * @param in_spc  Point code in the JAIN ISUP Signaling Point Code format.
      * @exception ParameterRangeInvalidException  Thrown when value is out of range.  */
    public CallReference(int in_callId, SignalingPointCode in_spc)
        throws ParameterRangeInvalidException {
        this.setCallIdentity(in_callId);
        this.setSignalingPointCode(in_spc);
    }
    /** Gets the call Identity field of the parameter.
      * @return The CallIdentity value.  */
    public int getCallIdentity() {
        return m_callIdentity;
    }
    /** Sets the call Indentity field of the parameter.
      * @exception ParameterRangeInvalidException  Thrown if the value is out of
      * range.  */
    public void setCallIdentity(int aCallIdentity)
        throws ParameterRangeInvalidException {
        m_callIdentity = aCallIdentity;
    }
    /** Gets the point code field of the parameter.
      * @return The PointCode value which is in the JAIN ISUP Signaling Point Code
      * format.  */
    public SignalingPointCode getSignalingPointCode() {
        return m_pointCode;
    }
    /** Sets the point code field of the parameter.
      * @param aPointCode  The point code value which is in the JAIN ISUP Signaling
      * Point Code format.
      * @exception ParameterRangeInvalidException  Thrown if the value is out of
      * range.  */
    public void setSignalingPointCode(SignalingPointCode aPointCode)
        throws ParameterRangeInvalidException {
        m_pointCode = aPointCode;
    }
    /** The toString method retrieves a string containing the values of the members of
      * the CallReference class.
      * @return A string representation of the member variables.  */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append(super.toString());
        b.append("\njavax.jain.ss7.isup.CallReference");
        b.append("\n\tm_callIdentity: " + m_callIdentity);
        b.append("\n\tm_pointCode: " + m_pointCode);
        return b.toString();
    }
    protected int m_callIdentity;
    protected SignalingPointCode m_pointCode;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
