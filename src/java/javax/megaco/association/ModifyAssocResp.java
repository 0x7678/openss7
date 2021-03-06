// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
/*
 @(#) $RCSfile: ModifyAssocResp.java,v $ $Name:  $($Revision: 1.1.2.2 $) $Date: 2011-02-07 07:27:15 $ <p>
 
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
 
 Last Modified $Date: 2011-02-07 07:27:15 $ by $Author: brian $
 */

// vim: sw=4 et tw=72 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS,\://,b\:#,\:%,\:XCOMM,n\:>,fb\:-
/*

   Overview Package  Class Tree Index Help
   JAIN^TM MEGACO API (RELEASE) - Version 1.0 - 22 December 2003
    PREV CLASS   NEXT CLASS FRAMES NO FRAMES
   SUMMARY:  INNER | FIELD | CONSTR | METHOD DETAIL:  FIELD | CONSTR |
   METHOD
     _________________________________________________________________

javax.megaco.association
Class ModifyAssocResp

java.lang.Object
  |
  +--java.util.EventObject
        |
        +--javax.megaco.association.AssociationEvent
              |
              +--javax.megaco.association.ModifyAssocResp

   All Implemented Interfaces:
          java.io.Serializable
     _________________________________________________________________

   public class ModifyAssocResp
   extends AssociationEvent

   The class extends JAIN MEGACO Association Events. This class is
   created by the stack when it needs to send back response for the
   modify association request received from the application.

   See Also:
          Serialized Form
     _________________________________________________________________

   Fields inherited from class java.util.EventObject
   source

   Constructor Summary
   ModifyAssocResp (java.lang.Object source, int assocHandle)
           throws javax.megaco.InvalidArgumentException

              Constructs a Modify Association Response Event object. This
   object is modifyd by the stack.

   Method Summary
   final int getEventStatus()
             Returns an integer value that identifies that the
   association event could be handled successfuly or not. This method is
   called by the application to check the result of the modify
   association request sent to the stack. The possible values that this
   can take is defined in ReturnStatus.
   final void  setEventStatus( ReturnStatus eventStatus)
       throws javax.megaco.InvalidArgumentException

             Sets a static object that is derived class of the
   ReturnStatus, that identifies whether the association event could be
   handled successfuly or not.
   final int getErrorCode()
           throws javax.megaco.MethodInvocationException

             Specifies the error code due to which the association event
   was a failure. This method is to be called by the application only on
   identifying that the association event could not be sucessfully
   processed.

   final void  setErrorCode(ErrorCode ecode)
           throws javax.megaco.InvalidArgumentException

             Sets an integer value that identifies the error code which
   further qualifies the error due to which the modify association event
   could not be processed successfuly.

   Methods inherited from class javax.megaco. AssociationEvent
   getAssocHandle, getAssocOperIdentifier

   Methods inherited from class java.util.EventObject
   getSource, toString

   Methods inherited from class java.lang.Object
   clone, equals, finalize, getClass, hashCode, notify, notifyAll, wait



   Constructor Detail

  ModifyAssocResp

public ModifyAssocResp(java.lang.Object source, int assocHandle)
                     throws javax.megaco.InvalidArgumentException

          Constructs a Modify Association Response Event object.


        Parameters:
                source - A reference to the object, the "source", that is
                logically deemed to be the object upon which the Event in
                question initially occurred.
                assocHandle - The association handle to uniquely identify
                the MG-MGC pair. This is allocated by the stack when the
                Listener registers with the provider with a unique MG-MGC
                identity.

        Throws:
                InvalidArgumentException if the parameters send in the
                constructor are invalid.

   Method Detail

  getAssocOperIdentifier

public final int getAssocOperIdentifier()

          This method returns that the event object as modify association
          response event. This method overrides the corresponding method
          of the base class AssociationEvent.


        Returns:
                Returns an integer value that identifies this event
                object as the type of modify association response event.
                This is defined as M_MODIFY_ASSOC_RESP in AssocEventType.
     _________________________________________________________________

  getEventStatus

public final int getEventStatus()

          This method returns whether the modify association event was
          successful or not.


        Returns:
                Returns an integer value that identifies whether the
                modify association event issued earlier could be
                performed successfuly or not. The values are defined in
                ReturnStatus. If this method is not set, then this method
                returns value 0.
     _________________________________________________________________

  setEventStatus

   public final void setEventStatus(ReturnStatus returnStatus)
       throws javax.megaco.InvalidArgumentException

          This method sets the status of whether the processing of the
          modify association event was successful or not.


        Parameters:
                The return status of the processing of the modify
                association event. The static object corresponding to the
                return status which are one of the derived classes of the
                ReturnStatus shall be set.

             
        Throws:
                InvalidArgumentException : This exception is raised if
                the reference of Return Status passed to this method is
                NULL.
     _________________________________________________________________

  getErrorCode

public final int getErrorCode()
                     throws javax.megaco.MethodInvocationException

          This method returns the error code qualifying why the modify
          association event could not be processed successfuly.


        Returns:
                Returns an integer value that identifies the error code
                specifying why the execution of the modify association
                event could not be successful. The possible values are
                field constants defined for the class ErrorCode. If the
                error code is not set, then this method would return
                value 0.

        Throws:
                MethodInvocationException - This exception would be
                raised if the return status is set to M_SUCCESS, the
                error code is not set and hence should not invoke this
                method.
     _________________________________________________________________

  setErrorCode

public final void setErrorCode(ErrorCode ecode)
                     throws javax.megaco.InvalidArgumentException

          This method sets the error code specifying why the modify
          association event could not be executed successfuly.


        Parameters:
                The error code corresponding to why the modify
                association event could not be executed successfuly.

          Throws:InvalidArgumentException This exception would be raised
          in following conditions

                1. If the return status is not set to M_FAILURE, the
                error code should not be set.
                2. If the error code is not valid for the ModifyAssocReq
                class.
     _________________________________________________________________

   Overview Package  Class Tree Index Help
   JAIN^TM MEGACO API (RELEASE) - Version 1.0 - 22 December 2003
    PREV CLASS   NEXT CLASS FRAMES NO FRAMES
   SUMMARY:  INNER | FIELD | CONSTR |  METHOD DETAIL:  FIELD | CONSTR |
   METHOD
     _________________________________________________________________

                  Copyright (C) 2001 Hughes Software Systems
       HUGHES SOFTWARE SYSTEMS and JAIN JSPA SIGNATORIES PROPRIETARY
        This document contains proprietary information that shall be
     distributed, routed or made available only within Hughes Software
       Systems and JAIN JSPA Signatory Companies, except with written
                   permission of Hughes Software Systems
             _________________________________________________

   22 December 2003


    If you have any comments or queries, please mail them to
    Jmegaco_hss@hss.hns.com
*/
