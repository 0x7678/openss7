/*
 @(#) $RCSfile: InfoIndAnsi.java,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2011-09-02 08:46:48 $ <p>
 
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
 
 Last Modified $Date: 2011-09-02 08:46:48 $ by $Author: brian $
 */

package javax.jain.ss7.isup.ansi;

import javax.jain.ss7.isup.*;
import javax.jain.ss7.*;
import javax.jain.*;

/** A class representing the ANSI ISUP Information Indicator parameter.
    This class inherits from the core class and adds methods to access the ANSI specific
    sub-fields of Information Indicator parameter class.

    @author Monavacon Limited
    @version 1.2.2
  */
public class InfoIndAnsi extends InfoInd {
    public static final boolean MLBGIRI_MULTI_LOCATION_BUSINESS_GROUP_INFORMATION_NOT_INCLUDED = false;
    public static final boolean MLBGIRI_MULTI_LOCATION_BUSINESS_GROUP_INFORMATION_INCLUDED = true;
    /** Constructs a new ANSI InfoInd class, parameters with default values.  */
    public InfoIndAnsi() {
    }
    /** Constructs an ANSI InfoInd class from the input parameters specified.
        @param in_callingAddrRespInd  The calling party address response indicator, range
        0 to 3, see InfoInd().
        @param in_holdInd  The hold provided indicator, see InfoInd().
        @param in_callingCatResInd  The calling party's category response indicator, see
        InfoInd().
        @param in_chargeInfoResInd  The charge information response indicator, see
        InfoInd().
        @param in_solInfoInd  The solicited information indicator, see InfoInd().
        @param in_multiLocBGInfoRespInd  The multi-location business group information
        response indicator. <ul>
        <li>MLBGIRI_MULTI_LOCATION_BUSINESS_GROUP_INFORMATION_NOT_INCLUDED and
        <li>MLBGIRI_MULTI_LOCATION_BUSINESS_GROUP_INFORMATION_INCLUDED. </ul>
      */
    public InfoIndAnsi(byte in_callingAddrRespInd, boolean in_holdInd,
            boolean in_callingCatResInd, boolean in_chargeInfoResInd,
            boolean in_solInfoInd, boolean in_multiLocBGInfoRespInd)
            throws ParameterRangeInvalidException {
            super(in_callingAddrRespInd, in_holdInd, in_callingCatResInd, in_chargeInfoResInd, in_solInfoInd);
            this.setMultiLocBusinessGroupInfoRespInd(in_multiLocBGInfoRespInd);
    }
    /** Gets the Multi Location Business Group Information Response Indicator field of the
        parameter.
        @return boolean  The MultiLocationBusinessGroupInformationResponseIndicator value,
        see InfoIndAnsi().
      */
    public boolean getMultiLocBusinessGroupInfoRespInd() {
        return m_multiLocationBGInfoRespIndicator;
    }
    /** Sets the Multi Location Business Group Information Response Indicator field of the
        parameter.
        @param aMultiLocationBGInfoRespIndicator  The
        MultiLocationBusinessGroupInformationResponseIndicator value, see InfoIndAnsi().
      */
    public void setMultiLocBusinessGroupInfoRespInd(boolean aMultiLocationBGInfoRespIndicator) {
        m_multiLocationBGInfoRespIndicator = aMultiLocationBGInfoRespIndicator;
    }
    /** The toString method retrieves a string containing the values of the members of the
        InfoIndAnsi class.
        @return A string representation of the member variables.
      */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append(super.toString());
        b.append("\njavax.jain.ss7.isup.ansi.InfoIndAnsi");
        b.append("\n\tm_multiLocationBGInfoRespIndicator: " + m_multiLocationBGInfoRespIndicator);
        return b.toString();
    }
    protected boolean m_multiLocationBGInfoRespIndicator;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
