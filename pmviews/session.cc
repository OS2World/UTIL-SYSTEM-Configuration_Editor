// This may look like C code, but it is really -*- C++ -*-

/* session.cc
 *
 * Implementation of class Session
 *
 * This class initiates a new session for a PM program
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: session.cc,v 1.1 1992/07/18 02:02:43 gruen Exp $
 *
 * $Log: session.cc,v $
// Revision 1.1  1992/07/18  02:02:43  gruen
// Initial revision
//
 *
 * Copyright (c) 1992 Lutz Grueneberg
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.  This library is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Library General Public License for
 * more details. You should have received a copy of the GNU Library
 * General Public License along with this library; if not, write to the
 * Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#define INCL_WIN
#include <os2.h>
#include "session.h"


/* Session::Session()
 *
 * Konstruktor der Klasse Session
 *
 * Initializierung des PM und Registration der Applikation
 * Erzeugung einer Message-Queue
 */

Session::Session()
{
  hab = WinInitialize (0);
  hmq = WinCreateMsgQueue (hab,           // Anchor Block handle
			   0);		  // Queue size, use default
}
/* Session::~Session()
 *
 * Destruktor einer Session. 
 * Zerstoert Message-Queue und Achor-Block.
 */
Session::~Session()
{
  WinDestroyMsgQueue( hmq);
  WinTerminate( hab);
}


/* Session::queryAnchorBlock()
 *
 * Publike Methode zum Auffinden des Anker-Blocks der Session
 */

HAB Session::queryAnchorBlock ()
{
  return  hab;
}

 
/* Session::queryMsgQueue()
 *
 * Publike Methode zum Auffinden der Message-Queue der Session
 */

HMQ Session::queryMsgQueue()
{
  return  hmq;
}


/* Session::run()
 *
 * Publike Methode zum Start der Anwendung. Hier wird die
 * Message-Loop durchgefuehrt, d.h. die Message-Queue der
 * Session wird abgefragt und die Medlungen an den Dispatcher
 * Weitergegeben.
 */

VOID Session::run()
{

  while( WinGetMsg( hab,           // Anchor block handle
                    &qmsg,	   // Pointer to queue message structure
                    NULL,          // No window message filter
                    0,             // Retrieve all messages
                    0))            // Retrieve all messages
  { WinDispatchMsg( hab,	   // Anchor block handle
                    &qmsg);	   // structure holding message
  }
}
/* E O F */


