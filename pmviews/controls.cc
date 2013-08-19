// this might look like 'C', but it's really  -*-c++-*-
/* controls.cc
 *
 * Realisierung der Control-Window-Klassen
 *
 * Die Klassen ermoeglichen die einfachere Handhabung
 * von PM-Dialogboxen und -Controls fuer eine
 * eine PM Applikation
 *
 *旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커
 *쿗anguage        : C++                       �
 *쿚perating System: OS/2 V2.0 and higher      �
 *쿎ompiler        : GNU GCC V2.1 and higher   �
 *읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸
 *
 * $Id: controls.cc,v 1.1 1992/07/19 02:01:16 gruen Exp $
 * $Log: controls.cc,v $
// Revision 1.1  1992/07/19  02:01:16  gruen
// Initial revision
//
// Revision 1.2  1992/06/24  23:17:00  gruen
// changed the contructor from HWND to Dialog*
//
// Revision 1.1  1992/06/24  19:51:38  gruen
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
#include "window.h"
#include "dialog.h"
#include "controls.h"

/*
 * methods of class CntrlWindow
 */
CntrlWindow::CntrlWindow( Dialog* pOwnerNew, USHORT idResNew)
{
  pOwner = pOwnerNew;
  idRes  = idResNew;
}

HWND CntrlWindow::queryHwnd( VOID)
{
  return pOwner->queryHwnd();
}

USHORT CntrlWindow::queryId( VOID)
{
  return idRes;
}

BOOL   CntrlWindow::show( BOOL fShow)              /* TRUE signals success */
{
  return WinShowWindow( WinWindowFromID( queryHwnd(), queryId()), fShow);
}

BOOL   CntrlWindow::enable( BOOL fEnable)          /* TRUE signals success */
{
  return WinEnableWindow( WinWindowFromID( queryHwnd(), queryId()), fEnable);
}

BOOL   CntrlWindow::enableUpdate( BOOL fEnable)    /* TRUE signals success */
{
  return WinEnableWindowUpdate( WinWindowFromID( queryHwnd(), 
						queryId()), fEnable);
}



/*
 * Methoden der Klasse StaticText
 */

StaticText::StaticText( Dialog* pOwnerNew, USHORT idResNew)
     :(pOwnerNew,idResNew){}

BOOL StaticText::setText( CHAR* szBuf)
{
  return WinSetDlgItemText( queryHwnd(), queryId(), (PSZ)szBuf);
}

SHORT StaticText::queryText( CHAR* szBuf, SHORT sSize)
{
  return (SHORT) WinQueryDlgItemText( queryHwnd(), queryId(), 
				     sSize, (PSZ)szBuf); 
}

BOOL StaticText::setShort( SHORT sVal)
{
  return WinSetDlgItemShort( queryHwnd(), queryId(), sVal, TRUE);
}

BOOL StaticText::queryShort( SHORT *psVal)
{
  return WinQueryDlgItemShort( queryHwnd(), queryId(), psVal, TRUE);
}

BOOL StaticText::setUShort( USHORT usVal)
{
  return WinSetDlgItemShort( queryHwnd(), queryId(), usVal, FALSE);
}

BOOL StaticText::queryUShort( USHORT *pusVal)
{
  return WinQueryDlgItemShort( queryHwnd(), queryId(), (SHORT*)pusVal, FALSE);
}

SHORT StaticText::queryTextLength( VOID)
{
  return WinQueryDlgItemTextLength( queryHwnd(), queryId());
}


/*
 * Methoden der Klasse EntryField
 */

EntryField::EntryField( Dialog* pOwnerNew, USHORT idResNew)
     :(pOwnerNew,idResNew){}

BOOL EntryField::setTextLimit( SHORT sMax)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					EM_SETTEXTLIMIT,
					MPFROMSHORT( sMax), 0L));
}

/*
 * methods of class ListBox
 */

ListBox::ListBox( Dialog* pOwnerNew, USHORT idResNew)
     :(pOwnerNew,idResNew){}

BOOL ListBox::deleteAll(VOID)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_DELETEALL,
					0L, 0L));
}
  
SHORT ListBox::deleteItem(SHORT iItem)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_DELETEITEM,
					MPFROMSHORT( iItem), 0L));
}

SHORT ListBox::insertItem(SHORT iItem, CHAR* pszText)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_INSERTITEM,
					MPFROMSHORT( iItem), 
					MPFROMP( pszText)));
}

SHORT ListBox::queryItemCount(VOID)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_QUERYITEMCOUNT,
					0L, 0L));
}

SHORT ListBox::queryItemHandle(SHORT iItem)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_QUERYITEMCOUNT,
					MPFROMSHORT(iItem), 0L));
}

SHORT ListBox::queryItemText(SHORT iItem, CHAR* pszText, SHORT cch)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_QUERYITEMTEXT,
					MPFROM2SHORT(iItem, cch), 
					MPFROMP(pszText)));
}

SHORT ListBox::queryItemTextLength(SHORT iItem)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_QUERYITEMTEXTLENGTH,
					MPFROMSHORT(iItem), 0L));
}

SHORT ListBox::querySelection(SHORT iItemPrev)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_QUERYSELECTION,
					MPFROMSHORT(iItemPrev), 0L));
}

SHORT ListBox::queryTopIndex(VOID)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_QUERYTOPINDEX,
					0L, 0L));
}

SHORT ListBox::searchString(USHORT usCmd, SHORT iItem, CHAR* pszSearch)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_SEARCHSTRING,
					MPFROM2SHORT(usCmd, iItem),
					MPFROMP(pszSearch)));
}

BOOL  ListBox::selectItem( SHORT iItem, BOOL fSelect)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_SELECTITEM,
					MPFROMSHORT(iItem),
					MPFROMSHORT(fSelect)));
}

BOOL  ListBox::setItemHandle(SHORT iItem, ULONG ulHandle)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_SETITEMHANDLE,
					MPFROMSHORT(iItem),
					MPFROMLONG(ulHandle)));
}

BOOL  ListBox::setItemHeight(SHORT sHeight)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_SETITEMHEIGHT,
					MPFROMSHORT(sHeight), 0L));
}

BOOL  ListBox::setItemText(SHORT iItem, CHAR* pszText)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_SETITEMTEXT,
					MPFROMSHORT(iItem),
					MPFROMLONG(pszText)));
}

BOOL  ListBox::setTopIndex(SHORT iItem)
{
  return SHORT1FROMMR(WinSendDlgItemMsg(queryHwnd(), queryId(), 
					LM_SETTOPINDEX,
					MPFROMSHORT(iItem), 0L));
}

/* E O F */


