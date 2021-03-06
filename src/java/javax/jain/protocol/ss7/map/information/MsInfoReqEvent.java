/*
 @(#) $RCSfile: MsInfoReqEvent.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:34:39 $ <p>
 
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
 
 Last Modified $Date: 2009-06-21 11:34:39 $ by $Author: brian $
 */

package javax.jain.protocol.ss7.map.information;

import javax.jain.protocol.ss7.map.information.etsipar.*;
import javax.jain.protocol.ss7.map.*;
import javax.jain.protocol.ss7.*;
import javax.jain.*;

/** This primitive (event) is used by the MAP API User to request information (status
  * and/or location) for a Mobile Station. <p>
  *
  * The following rules applies for the setting of primitive parameters:- <ul>
  * <li>Mandatory parameters with no default value must be provided to the constructor.
  * <li>Mandatory parameters with default value need not be set.
  * <li>Optional / conditional parameter is by default not present. Such a parameter
  * becomes present by setting it. </ul> <p>
  *
  * Primitive parameters:- <ul>
  * <li>msId (Mobile Station Id), mandatory parameter with no default
  * <li>infoRequestSpecifier, mandatory parameter with no default </ul>
  *
  * @author Monavacon Limited
  * @version 1.2.2
  */
public final class MsInfoReqEvent extends InformationEvent {
    /** The constructor.  
      * @param source  The source of this event. Should be set to the Listener object for
      * the transaction.
      * @param msId  The MSISDN (an E.164 number) of the Mobile Station for which
      * information is requested.
      * @param infoRequestSpecifier  Parameter that specifies what information is
      * requested.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public MsInfoReqEvent(java.lang.Object source, E164Number msId, InfoRequestSpecifier infoRequestSpecifier)
        throws SS7InvalidParamException {
        super(source,MS_INFO_REQ_ID);
        setMsId(msId);
        setInfoRequestSpecifier(infoRequestSpecifier);
    }
    /** Empty constructor; needed for serializable objects and beans.  */
    public MsInfoReqEvent()
        throws SS7InvalidParamException {
        super(null,MS_INFO_REQ_ID);
    }
    /** Change the ID (MSISDN) of the Mobile Station for which information is requested.
      * @param msId  Identifier of the Mobile Station.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setMsId(E164Number msId)
        throws SS7InvalidParamException {
        m_msId = msId;
    }
    /** Get the ID (MSISDN) of the Mobile Station for which information is requested.
      * @return Identifier of the Mobile Station.
      */
    public E164Number getMsId() {
        return m_msId;
    }
    /** Change the specifier for requested information.
      * @param infoRequestSpecifier  Specifier for requested information.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setInfoRequestSpecifier(InfoRequestSpecifier infoRequestSpecifier)
        throws SS7InvalidParamException {
        m_infoRequestSpecifier = infoRequestSpecifier;
    }
    /** Get the specifier for requested information.
      * @return Specifier for requested information.
      */
    public InfoRequestSpecifier getInfoRequestSpecifier() {
        return m_infoRequestSpecifier;
    }
    protected E164Number m_msId;
    protected InfoRequestSpecifier m_infoRequestSpecifier;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
