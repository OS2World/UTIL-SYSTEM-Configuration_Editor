// this might look like 'C', but it's really  -*-c++-*-
/* controls.h
 *
 * Klassendeklaration der Control-Window-Klassen
 *
 * Die Klassen ermoeglichen die einfachere Handhabung
 * von PM-Dialogboxen und -Controls fuer eine
 * eine PM Applikation
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: controls.h,v 1.1 1992/07/19 02:01:18 gruen Exp $
 * $Log: controls.h,v $
 * Revision 1.1  1992/07/19  02:01:18  gruen
 * Initial revision
 *
 * Revision 1.2  1992/06/24  23:28:16  gruen
 * changed the constructor from HWND to Dialog*
 *
 * Revision 1.1  1992/06/24  19:51:38  gruen
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

/* the master file needs to define INCL_WIN and must include os2.h */
/* 
 * The idea standing behind this library is easy: avoid PM overhead.
 * Following classes are included:
 *  CntrlWindow           base class for PM Control Windows
 *    StaticText          usual text strings in a static control           
 *      EntryField        for easy access to Entry Field Controls
 *    ListBox             Interface to PM List Boxes
 */

#ifndef CONTROLS_H_INCLUDED
#define CONTROLS_H_INCLUDED


class CntrlWindow {
private:
  Dialog      *pOwner;
  USHORT      idRes;
public:
  CntrlWindow(Dialog *pOwnerNew, USHORT idResNew);

  HWND   queryHwnd( VOID);               // retrieve hwnd of Dialog
  USHORT queryId( VOID);		 // retrieve resource id
  BOOL   show( BOOL fShow);              /* TRUE signals success */
  BOOL   enable( BOOL fEnable);          /* TRUE signals success */
  BOOL   enableUpdate( BOOL fEnable);    /* TRUE signals success */
};

class StaticText: public CntrlWindow {
  public:
    StaticText(Dialog* pOwnerNew, USHORT idResNew);

    BOOL setText(CHAR* szBuf);                    /* TRUE signals success */
    SHORT queryText(CHAR* szBuf, SHORT sSize);    /* count of chars,      */
                                                  /* zero indicates error */ 
    BOOL setShort( SHORT sVal);                   /* TRUE signals success */
    BOOL queryShort( SHORT *psVal);               /* TRUE signals success */
    BOOL setUShort( USHORT usVal);                /* TRUE signals success */
    BOOL queryUShort( USHORT *pusVal);            /* TRUE signals success */
    
    SHORT queryTextLength(VOID);                  /* returns string length*/
};    


class EntryField : public StaticText {
  public:
    EntryField(Dialog* pOwnerNew, USHORT idResNew);
    
    BOOL setTextLimit(SHORT sMax);                /* TRUE signals success */
};

class ListBox : public CntrlWindow {
  public:
    ListBox(Dialog* pOwnerNew, USHORT idResNew);
    /* basic PM methods */
    BOOL  deleteAll(VOID);             /* TRUE signals success              */
    SHORT deleteItem(SHORT iItem);     /* number of remaining items         */
    SHORT insertItem(SHORT iItem,      /* LIT_MEMERROR,LIT_ERROR ->error    */
		     CHAR* pszText);
    SHORT queryItemCount(VOID);        /* returns item count                */
    SHORT queryItemHandle(SHORT iItem);/* handle, zero indicates error      */
    SHORT queryItemText(SHORT iItem,   /* count of transferred characters   */
		CHAR* pszText, SHORT cch); /* without terminating  zero     */
    SHORT queryItemTextLength(SHORT iItem);/* count of characters or zero   */
    SHORT querySelection(SHORT iItemPrev);/* index of sel. item or LIT_NONE */ 
    SHORT queryTopIndex(VOID);         /* index of top item or LIT_NONE     */
    SHORT searchString(USHORT usCmd,   /* index of item or LIT_NONE         */
		       SHORT iItem, CHAR* pszSearch);
    BOOL  selectItem(SHORT iItem,      /* TRUE signals success              */
		     BOOL fSelect);
    
    BOOL  setItemHandle(SHORT iItem,   /* TRUE signals success              */
			ULONG ulHandle);
    BOOL  setItemHeight(SHORT sHeight);/* TRUE signals success              */
    BOOL  setItemText(SHORT iItem,     /* TRUE signals success              */
		      CHAR* pszText);
    BOOL  setTopIndex(SHORT iItem);    /* TRUE signals success              */
};

#endif /* CONTROLS_H_INCLUDED */








