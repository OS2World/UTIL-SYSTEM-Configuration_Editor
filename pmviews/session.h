// this might look like 'C', but it's really  -*-c++-*-
/* session.h
 *
 * Declaration of class Session
 *
 * This class initiates a new session for a PM program
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: session.h,v 1.1 1992/07/18 02:03:02 gruen Exp $
 *
 * $Log: session.h,v $
 * Revision 1.1  1992/07/18  02:03:02  gruen
 * Initial revision
 *
 *
 * Revision 1.1  92/05/23  23:20:33  Unknown
 * Initial revision
 * 
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
#ifndef SESSION_H_INCLUDED
#define SESSION_H_INCLUDED

/* the master file needs to define INCL_WIN and must include os2.h */

class Session
{
private:
  HAB      hab;
  HMQ      hmq;
  QMSG     qmsg;

public:
  Session();
  ~Session();
  VOID     run();
  HAB      queryAnchorBlock();
  HMQ      queryMsgQueue();
};
#endif /* SESSION_H_INCLUDED */











