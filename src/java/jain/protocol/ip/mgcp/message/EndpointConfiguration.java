// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
/*
 @(#) $RCSfile: EndpointConfiguration.java,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2011-02-07 07:27:08 $ <p>
 
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
 
 Last Modified $Date: 2011-02-07 07:27:08 $ by $Author: brian $
 */

package jain.protocol.ip.mgcp.message;

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
/*

   Overview  Package   Class  Tree  Index  Help
   JAIN^TM MGCP API (Final Release) - Version 1.0
    PREV CLASS   NEXT CLASS FRAMES    NO FRAMES
   SUMMARY:  INNER | FIELD | CONSTR | METHOD DETAIL:
   FIELD | CONSTR | METHOD
     _________________________________________________________________

jain.protocol.ip.mgcp.message
Class EndpointConfiguration

java.lang.Object
  |
  +--java.util.EventObject
        |
        +--jain.protocol.ip.mgcp.JainMgcpEvent
              |
              +--jain.protocol.ip.mgcp.JainMgcpCommandEvent
                    |
                    +--jain.protocol.ip.mgcp.message.EndpointConfiguration

   All Implemented Interfaces:
          java.io.Serializable
     _________________________________________________________________

   public final class EndpointConfiguration
   extends JainMgcpCommandEvent

   The MGCP EndpointConfiguration command, expressed as an event object,
   sent by a Call Agent to a Media Gateway to request configuration of an
   endpoint. This command elicits an EndpointConfigurationResponse event.

   See Also: 
          EndpointConfigurationResponse, Serialized Form
     _________________________________________________________________

   Fields inherited from class java.util.EventObject
   source



   Constructor Summary
   EndpointConfiguration(java.lang.Object source,
   EndpointIdentifier endpointIdentifier,
   BearerInformation bearerInformation)
             Constructs a new EndpointConfiguration (Command) Event
   object, setting the Endpoint Identifier and the endpoint configuration
   parameters.



   Method Summary
    BearerInformation getBearerInformation()
             Gets the Bearer Information parameter.
    void setBearerInformation(BearerInformation bearerInformation)
             Sets the Bearer Information parameter.
    java.lang.String toString()
             Overrides java.lang.Object.toString().



   Methods inherited from class
   jain.protocol.ip.mgcp.JainMgcpCommandEvent
   BuildCommandHeader, getEndpointIdentifier, setEndpointIdentifier



   Methods inherited from class jain.protocol.ip.mgcp.JainMgcpEvent
   BuildListParmLine, getObjectIdentifier, getTransactionHandle,
   setTransactionHandle



   Methods inherited from class java.util.EventObject
   getSource



   Methods inherited from class java.lang.Object
   clone, equals, finalize, getClass, hashCode, notify, notifyAll, wait,
   wait, wait



   Constructor Detail

  EndpointConfiguration

public EndpointConfiguration(java.lang.Object source,
                             EndpointIdentifier endpointIdentifier,
                             BearerInformation bearerInformation)
                      throws java.lang.IllegalArgumentException

          Constructs a new EndpointConfiguration (Command) Event object,
          setting the Endpoint Identifier and the endpoint configuration
          parameters.

        Parameters:
                endpointIdentifier - The Endpoint Identifier.
                bearerInformation - Bearer information (i.e., encoding
                method to be used).

        Throws:
                java.lang.IllegalArgumentException - Thrown if either the
                endpoint identifier or the bearer information parameter
                is null-valued.

   Method Detail

  getBearerInformation

public BearerInformation getBearerInformation()

          Gets the Bearer Information parameter.

        Returns:
                The bearer information (i.e., encoding method).
     _________________________________________________________________

  setBearerInformation

public void setBearerInformation(BearerInformation bearerInformation)
                          throws java.lang.IllegalArgumentException

          Sets the Bearer Information parameter.

        Parameters:
                bearerInformation - The bearer information (i.e.,
                encoding method).

        Throws:
                java.lang.IllegalArgumentException - Thrown if the bearer
                information parameter is null-valued.
     _________________________________________________________________

  toString

public java.lang.String toString()

          Overrides java.lang.Object.toString().

        Overrides:
                toString in class java.util.EventObject
     _________________________________________________________________

   Overview  Package   Class  Tree  Index  Help
   JAIN^TM MGCP API (Final Release) - Version 1.0
    PREV CLASS   NEXT CLASS FRAMES    NO FRAMES
   SUMMARY:  INNER | FIELD | CONSTR | METHOD DETAIL:
   FIELD | CONSTR | METHOD
     _________________________________________________________________

                  Copyright (C) 2000 Sun Microsystems, Inc.
*/
