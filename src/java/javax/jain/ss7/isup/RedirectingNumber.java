/*
 @(#) $RCSfile: RedirectingNumber.java,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2011-09-02 08:46:47 $ <p>
 
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

/** A class representing the ITU and ANSI Redirecting Number.
  * This class is common to ITU and ANSI. This class provides methods to access the
  * sub-fields of this parameter.
  *
  * @author Monavacon Limited
  * @version 1.2.2
  */
public class RedirectingNumber extends NumberParameter {
    public static final byte APRI_PRESENTATION_ALLOWED = 0;
    public static final byte APRI_PRESENTATION_RESTRICTED = 1;
    public static final byte APRI_ADDRESS_NOT_AVAILABLE = 2;
    /** Constructs a new RedirectingNumber taking no parameters.
      * This constructor sets all the sub-field values to their spare value (which is
      * zero).  */
    public RedirectingNumber() {
    }
    /** Constructs a Redirecting Party Id.
      * @param natureOfAddressIndicator  The nature of address indicator, range 0-127,
      * see NumberParameter().
      * @param numberingPlanIndicator  The numbering plan indicator, range 0-7, see
      * NumberParameter().
      * @param addressPresentationRestrictedIndicator  The address presentation
      * restricted indicator; <ul> <li>APRI_ADDRESS_PRESENTATION_ALLOWED,
      * <li>APRI_ADDRESS_PRESENTATION_RESTRICTED and <li>APRI_ADDRESS_NOT_AVAILABLE.
      * </ul>
      * @param addressSignal  The address signal.
      * @exception ParameterRangeInvalidException  Thrown when value is out of range.  */
    public RedirectingNumber(byte natureOfAddressIndicator,
            byte numberingPlanIndicator, byte addressPresentationRestrictedIndicator,
            byte[] addressSignal)
        throws ParameterRangeInvalidException {
        super(natureOfAddressIndicator, numberingPlanIndicator, addressSignal);
        this.setAddrPresRestInd(addressPresentationRestrictedIndicator);
    }
    /** Gets the Address Presentation Restricted Ind field of the parameter.
      * @return The address presentation indicator, range 0 - 3, see
      * RedirectingNumber().  */
    public byte getAddrPresRestInd() {
        return m_addressPresentationRestrictedIndicator;
    }
    /** Sets the Address Presentation Restricted Ind field of the parameter.
      * @param addressPresentationRestrictedIndicator  Address presentation restriction indicator value, see
      * RedirectingNumber().  */
    public void setAddrPresRestInd(byte addressPresentationRestrictedIndicator)
        throws ParameterRangeInvalidException {
        switch (addressPresentationRestrictedIndicator) {
            case APRI_PRESENTATION_ALLOWED:
            case APRI_PRESENTATION_RESTRICTED:
            case APRI_ADDRESS_NOT_AVAILABLE:
                m_addressPresentationRestrictedIndicator = addressPresentationRestrictedIndicator;
                return;
        }
        throw new ParameterRangeInvalidException("AddressPresentationRestrictedIndicator value " + addressPresentationRestrictedIndicator + " out of range.");
    }
    /** The toString method retrieves a string containing the values of the members of
      * the RedirectingNumber class.
      * @return A string representation of the member variables.  */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append(super.toString());
        b.append("\njavax.jain.ss7.isup.RedirectingNumber");
        b.append("\n\tm_addressPresentationRestrictedIndicator: " + m_addressPresentationRestrictedIndicator);
        return b.toString();
    }
    protected byte m_addressPresentationRestrictedIndicator;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
