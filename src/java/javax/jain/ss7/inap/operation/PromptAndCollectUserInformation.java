/*
 @(#) $RCSfile: PromptAndCollectUserInformation.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:35:00 $ <p>
 
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
 
 Last Modified $Date: 2009-06-21 11:35:00 $ by $Author: brian $
 */

package javax.jain.ss7.inap.operation;

import javax.jain.ss7.inap.constants.*;
import javax.jain.ss7.inap.datatype.*;
import javax.jain.ss7.inap.*;
import javax.jain.ss7.*;
import javax.jain.*;

/** This class represents the PromptAndCollectUserInformation Operation.
  * @version 1.2.2
  * @author Monavacon Limited
  */
public class PromptAndCollectUserInformation extends Operation implements java.io.Serializable {
    /** Constructor For PromptAndCollectUserInformation.  */
    public PromptAndCollectUserInformation(CollectedInfo collectedInfo, boolean disconnectFromIPForbidden) {
        operationCode = OperationCode.PROMPT_AND_COLLECT_USER_INFORMATION;
        setCollectedInfo(collectedInfo);
        setDisconnectFromIPForbidden(disconnectFromIPForbidden);
    }
    /** Gets Operation Code.  */
    public OperationCode getOperationCode() {
        return operationCode;
    }
    /** Gets Collected Info.  */
    public CollectedInfo getCollectedInfo() {
        return collectedInfo;
    }
    /** Sets Collected Info.  */
    public void setCollectedInfo(CollectedInfo collectedInfo) {
        this.collectedInfo = collectedInfo;
    }
    /** Gets Disconnect From IP Forbidden.  */
    public boolean getDisconnectFromIPForbidden() {
        return disconnectFromIPForbidden;
    }
    /** Sets Disconnect From IP Forbidden.  */
    public void setDisconnectFromIPForbidden(boolean disconnectFromIPForbidden) {
        this.disconnectFromIPForbidden = disconnectFromIPForbidden;
    }
    /** Gets Information To Send.  */
    public InformationToSend getInformationToSend() throws ParameterNotSetException {
        if (isInformationToSend)
            return informationToSend;
        throw new ParameterNotSetException("Information To Send: not set.");
    }
    /** Sets Information To Send.  */
    public void setInformationToSend(InformationToSend informationToSend) {
        this.informationToSend = informationToSend;
        isInformationToSend = true;
    }
    /** Indicates if the Information To Send optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isInformationToSendPresent() {
        return isInformationToSend;
    }
    /** Gets Call Segment ID.  */
    public int getCallSegmentID() throws ParameterNotSetException {
        if (isCallSegmentID)
            return callSegmentID;
        throw new ParameterNotSetException("Call Segment Id: not set.");
    }
    /** Sets Call Segment ID.  */
    public void setCallSegmentID(int callSegmentID) {
        this.callSegmentID = callSegmentID;
        this.isCallSegmentID = true;
    }
    /** Indicates if the Call Segment ID optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isCallSegmentIDPresent() {
        return isCallSegmentID;
    }
    /** Gets Extensions Parameter.  */
    public ExtensionField[] getExtensions() throws ParameterNotSetException {
        if (isExtensions)
            return extensions;
        throw new ParameterNotSetException("Extensions: not set.");
    }
    /** Gets a particular Extension Parameter.  */
    public ExtensionField getExtension(int index) {
        return extensions[index];
    }
    /** Sets Extensions Parameter.  */
    public void setExtensions(ExtensionField extensions[]) {
        this.extensions = extensions;
        this.isExtensions = true;
    }
    /** Sets a particular Extensions Parameter.  */
    public void setExtension(int index, ExtensionField extension) {
        this.extensions[index] = extension;
    }
    /** Indicates if the Extensions optional parameter is present.
      * @return True when present, false otherwise.  */
    public boolean isExtensionsPresent() {
        return isExtensions;
    }
    private CollectedInfo collectedInfo;
    private boolean disconnectFromIPForbidden = true;
    private InformationToSend informationToSend;
    private boolean isInformationToSend = false;
    private int callSegmentID;
    private boolean isCallSegmentID = false;
    private ExtensionField extensions[];
    private boolean isExtensions = false;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
