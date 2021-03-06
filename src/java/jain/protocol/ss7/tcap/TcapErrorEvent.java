/*
 @(#) $RCSfile: TcapErrorEvent.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:34:29 $ <p>
 
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
 
 Last Modified $Date: 2009-06-21 11:34:29 $ by $Author: brian $
 */

package jain.protocol.ss7.tcap;

import jain.protocol.ss7.*;
import jain.*;

/**
  * This Event may be emitted by a JainTcapProvider if the Provider
  * encounters an Error that cannot be passed to all registered
  * JainTcapListeners through normal TCAP error handling mechanisms.
  * @version 1.2.2
  * @author Monavacon Limited
  */
public class TcapErrorEvent extends java.util.EventObject implements java.io.Serializable, java.lang.Cloneable {
    /** Constructs a new TcapErrorEvent containing the user defined
      * error object.
      * @param source
      * The new Object source supplied to the constructor.
      * @param error
      * The new error supplied to the constructor.  */
    public TcapErrorEvent(java.lang.Object source, java.lang.Object error) {
        super(source);
        this.setError(error);
    }
    /** Sets the Error attribute of the TcapErrorEvent object.
      * @param error
      * The new Error value.  */
    public void setError(java.lang.Object error) {
        m_error = error;
    }
    /** Gets the Error attribute of the TcapErrorEvent object.
      * @return
      * The Error value.  */
    public java.lang.Object getError() {
        return m_error;
    }
    /** java.lang.String representation of class TcapErrorEvent.
      * @return
      * java.lang.String provides description of class TcapErrorEvent.  */
    public java.lang.String toString() {
        StringBuffer b = new StringBuffer(512);
        b.append(super.toString());
        b.append("\n\nerror = ");
        if (m_error != null)
            b.append(m_error.toString());
        return b.toString();
    }
    /** Error object.
      * @serial m_error
      * - a default serializable field. */
    private java.lang.Object m_error;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
