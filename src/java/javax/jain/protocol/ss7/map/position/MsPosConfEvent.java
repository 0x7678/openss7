/*
 @(#) $RCSfile: MsPosConfEvent.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:34:40 $ <p>
 
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
 
 Last Modified $Date: 2009-06-21 11:34:40 $ by $Author: brian $
 */

package javax.jain.protocol.ss7.map.position;

import javax.jain.protocol.ss7.map.*;
import javax.jain.protocol.ss7.*;
import javax.jain.*;

/** This primitive (event) is used by the MAP API Provider to deliver position information
  * for a Mobile Station. <p>
  *
  * The following rules applies for the setting of primitive parameters:- <ul>
  * <li>Mandatory parameters with no default value must be provided to the constructor.
  * <li>Mandatory parameters with default value need not be set.
  * <li>Optional / conditional parameter is by default not present. Such a parameter
  * becomes present by setting it. </ul> <p>
  *
  * Primitive parameters:- <ul>
  * <li>position, conditional parameter, present if position information is available.
  * <li>result, conditional parameter, present if position request failed. </ul> <p>
  *
  * @author Monavacon Limited
  * @version 1.2.2
  */
public final class MsPosConfEvent extends PositionEvent {
    /** The constructor.
      * @param source  The source of this event. Should be set to the Provider object for
      * the transaction.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public MsPosConfEvent(java.lang.Object source)
        throws SS7InvalidParamException {
        super(source,MS_POS_CONF_ID);
    }
    /** Empty constructor; needed for serializable objects and beans.  */
    public MsPosConfEvent()
        throws SS7InvalidParamException {
        super(null,MS_POS_CONF_ID);
    }
    /** Set the Position.
      * @param position  Position.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setPosition(Position position)
        throws SS7InvalidParamException {
        m_position = position;
        m_positionPresent = true;
    }
    /** Get the Position. It shall be checked if this parameter is present before getting
      * it.
      * @return Position.
      */
    public Position getPosition() {
        return m_position;
    }
    /** Check if the Position is present.
      * @return True or false.
      */
    public boolean isPositionPresent() {
        return m_positionPresent;
    }
    /** Set the result parameter. This parameter is present if the operation failed.
      * @param result  Result information.
      * @exception SS7InvalidParamException  Thrown if parameter(s) are invalid / out of
      * range.
      */
    public void setResult(Result result)
        throws SS7InvalidParamException {
        m_result = result;
        m_resultPresent = true;
    }
    /** Get the result parameter. It shall be checked if this parameter is present before
      * getting it.
      * @return Result information.
      */
    public Result getResult() {
        return m_result;
    }
    /** Check if result parameter is present.
      * @return True or false.
      */
    public boolean isResultPresent() {
        return m_resultPresent;
    }
    protected Position m_position = null;
    protected boolean m_positionPresent = false;
    protected Result m_result = null;
    protected boolean m_resultPresent = false;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
