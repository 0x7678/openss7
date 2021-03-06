/*
 @(#) $RCSfile: MapErrorEvent.java,v $ $Name:  $($Revision: 1.1.2.1 $) $Date: 2009-06-21 11:34:38 $ <p>
 
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
 
 Last Modified $Date: 2009-06-21 11:34:38 $ by $Author: brian $
 */

package javax.jain.protocol.ss7.map;

import java.io.Serializable;

/**
  * This class is the base class for all error events returned to the listener from the provider.
  *
  * @author Monavacon Limited
  * @version 1.2.2
  */
public class MapErrorEvent extends java.util.EventObject implements java.io.Serializable, java.lang.Cloneable {
    /**
      * The constructor.
      *
      * @param source The source of this event.
      * @param error A vendor-defined object containing the error.
      */
    public MapErrorEvent(java.lang.Object source, java.lang.Object error) {
        super(source);
        setError(error);
    }
    /**
      * Empty constructure needed for serializable objects and beans.
      */
    public MapErrorEvent() {
        super(null);
    }
    /**
      * Change the object contianing the error.
      * @param error The Object containing the error.
      */
    public void setError(java.lang.Object error) {
        m_error = error;
        m_error_is_set = true;
    }
    /**
      * Get the object containing the error.
      * @return The Object containing the error.
      */
    public java.lang.Object getError() {
        java.lang.Object error = null;
        if (m_error_is_set)
            error = m_error;
        return error;
    }
    public java.lang.Object getSource() {
        java.lang.Object source = null;
        if (m_source_is_set)
            source = m_source;
        return source;
    }
    private java.lang.Object m_source = null;
    private boolean m_source_is_set = false;
    private java.lang.Object m_error = null;
    private boolean m_error_is_set = false;
}

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
