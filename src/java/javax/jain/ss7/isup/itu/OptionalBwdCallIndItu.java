/*
 @(#) $RCSfile: OptionalBwdCallIndItu.java,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2011-09-02 08:46:49 $ <p>
 
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
 
 Last Modified $Date: 2011-09-02 08:46:49 $ by $Author: brian $
 */

package javax.jain.ss7.isup.itu;

import javax.jain.ss7.isup.*;
import javax.jain.ss7.*;
import javax.jain.*;

/** A class representing the ITU ISUP Optional Backward Call Indicators.
  * This class provides the methods to access the ITU only sub-fields in the optional
  * bacward call indicators parameter.
  *
  * @author Monavacon Limited
  * @version 1.2.2
  */
public class OptionalBwdCallIndItu extends OptionalBwdCallInd {
    public static final boolean CDI_NO_INDICATION = false;
    public static final boolean CDI_CALL_DIVERSION_MAY_OCCUR = true;
    public static final boolean SSI_NO_ADDITIONAL_INFORMATION = false;
    public static final boolean SSI_ADDITIONAL_INFORMATION_SENT_IN_SEGMENTATION = true;
    public static final boolean MUI_NO_INDICATION = false;
    public static final boolean MUI_MLPP_USER = true;
    /** Constructs a new OptionalBwdCallIndItu class, parameters with default values.  */
    public OptionalBwdCallIndItu() {
    }
    /** Constructs a OptionalBwdIndItu class from the input parameters specified.
      * @param in_inbandInfoInd  The in-band information indicator, see
      * OptionalBwdCallInd().
      * @param in_callDivInd  The call division may occur indicator. <ul>
      * <li>CDI_NO_INDICATION and <li>CDI_CALL_DIVERSION_MAY_OCCUR. </ul>
      * @param in_segInd  The simple segmentation indicator. <ul>
      * <li>SSI_NO_ADDITIONAL_INFORMATION aned
      * <li>SSI_ADDITIONAL_INFORMATION_SENT_IN_SEGMENTATION. </ul>
      * @param in_mlppUserInd  The MLPP user indicator. <ul> <li>MUI_NO_INDICATION aned
      * <li>MUI_MLPP_USER. </ul>
      */
    public OptionalBwdCallIndItu(boolean in_inbandInfoInd,
                             boolean in_callDivInd,
                             boolean in_segInd,
                             boolean in_mlppUserInd) {
        super(in_inbandInfoInd);
        this.setCallDiversionInd(in_callDivInd);
        this.setSegmentationInd(in_segInd);
        this.setMLPPUserInd(in_mlppUserInd);
    }
    /** Gets the Call Diversion May Occur Indicator field of the parameter.
      * @return boolean value containing the CallDiversionIndicator value, see
      * OptionalBwdCallIndItu().
      */
    public boolean getCallDiversionInd() {
        return m_callDiversionMayOccurIndicator;
    }
    /** Sets the Call Diversion May Occur Indicator field of the parameter.
      * @param aCallDiversionMayOccurIndicator  Boolean the Call Diversion May Occur
      * Indicator value, see OptionalBwdCallIndItu().
      */
    public void setCallDiversionInd(boolean aCallDiversionMayOccurIndicator) {
        m_callDiversionMayOccurIndicator = aCallDiversionMayOccurIndicator;
    }
    /** Gets the Simple Segmentation Indicator field of the parameter.
      * @return Boolean, the Simple Segmentation Indicator, see OptionalBwdCallIndItu().
      */
    public boolean getSegmentationInd() {
        return m_simpleSegmentation;
    }
    /** Sets the Simple Segmentation Indicator field of the parameter.
      * @param aSimpleSegmentation  Boolean the Simple Segmentation Indicator, see
      * OptionalBwdCallIndItu().
      */
    public void setSegmentationInd(boolean aSimpleSegmentation) {
        m_simpleSegmentation = aSimpleSegmentation;
    }
    /** Gets the MLPP User Indicator field of the parameter.
      * @return Boolean value containing the MLPPUserIndicator, see
      * OptionalBwdCallIndItu().
      */
    public boolean getMLPPUserInd() {
        return m_mlppUserIndicator;
    }
    /** Sets the MLPP User Indicator field of the parameter.
      * @param aMLPPUserIndicator  Boolean value containing the MLPP User Indicator, see
      * OptionalBwdCallIndItu().
      */
    public void setMLPPUserInd(boolean aMLPPUserIndicator) {
        m_mlppUserIndicator = aMLPPUserIndicator;
    }
    /** The toString method retrieves a string containing the values of the members of the
      * OptionalBwdCallIndItu class.
      * @return A string representation of the member variables.
      */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append(super.toString());
        b.append("\njavax.jain.ss7.isup.itu.OptionalBwdCallIndItu");
        b.append("\n\tm_callDiversionMayOccurIndicator: " + m_callDiversionMayOccurIndicator);
        b.append("\n\tm_simpleSegmentation: " + m_simpleSegmentation);
        b.append("\n\tm_mlppUserIndicator: " + m_mlppUserIndicator);
        return b.toString();
    }
    protected boolean m_callDiversionMayOccurIndicator;
    protected boolean m_simpleSegmentation;
    protected boolean m_mlppUserIndicator;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
