// this might look like 'C', but it's really  -*-c++-*-
/* sbrowser.cc
 *
 * Implementation of class SingleBrowser for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: sbrowser.cc,v 1.3 1992/08/29 16:12:08 gruen Exp $
 * $Log: sbrowser.cc,v $
// Revision 1.3  1992/08/29  16:12:08  gruen
// Fixed several bugs. This will become the official beta-release.
//
// Revision 1.2  1992/08/09  21:55:40  gruen
// beta release 1.0 of cfged. Changed the architecture: now using a dialog
// box as main window. As an result the accelerators now work. As goodie
// there is a new special-browser for HELP and last but not least the
// warning at the end of the program occures only if there not saved
// changes to the configuration.
//
// Revision 1.1  1992/07/17  00:23:40  gruen
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
#define INCL_PM
#include <os2.h>
#include <pmviews/pmviews.h>
#include <Regx.h>
#include <Strng.h>
#include "StrDLL.h"
#include "maindlg.h"
#include "prompter.h"
#include "pmctool.h"
#include "sbrowser.h"

     SingleBrowser::SingleBrowser( HWND hwndOwnerNew, USHORT  idResNew,
				  CHAR* pszTitleNew, CHAR *pszCommentNew,
				  StrDLList *pListNew)
:( hwndOwnerNew, idResNew) {
  pComment  = new StaticText( this, SB_TEXT);
  plb       = new ListBox( this, SB_LB);
  pbtInsert = new CntrlWindow( this, SB_INSERT_BUTT);
  pbtAppend = new CntrlWindow( this, SB_APPEND_BUTT);
  pbtDelete = new CntrlWindow( this, SB_DELETE_BUTT);
  pbtHelp   = new CntrlWindow( this, SB_HELP_BUTT);
  pbtCancel = new CntrlWindow( this, SB_CANCEL_BUTT);
  pbtOK     = new CntrlWindow( this, SB_OK_BUTT);

  pszTitle  = pszTitleNew;
  pszComment= pszCommentNew;
  pList     = pListNew;
  strList   = *pList;		// create a copy of the original list
}


MRESULT SingleBrowser::msgInitDlg( HWND hwnd, USHORT msg, 
				MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  setTitle( pszTitle);
  pComment->setText( pszComment);
  pbtHelp ->enable( FALSE);	// no help available 
  setState( 0);
  printToListBox();
  return 0;
}

MRESULT SingleBrowser::msgControl( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  USHORT usID;

  usID = SHORT1FROMMP(mp1);

  switch (SHORT2FROMMP(mp1)) {   
  case LN_ENTER:  /* Auswahl eines Item oder Double-Click */
    editEntry();
    *fDoDefault = FALSE;
    return 0;
  case LN_SELECT: /* selection of a item of the list */
    setState( 1);
    *fDoDefault = 0;
    return 0;
  }
  return 0;
}

MRESULT SingleBrowser::msgCommand( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  USHORT usID;

  usID = SHORT1FROMMP(mp1);	// the resource id of the sender
  if( SHORT1FROMMP( mp2) == CMDSRC_PUSHBUTTON) {   
    switch (SHORT1FROMMP(mp1)) {   
    case SB_INSERT_BUTT:
      {	PrompterDlg Prompter( queryHwnd(), PR_DLG);
	SHORT i = plb->querySelection( LIT_NONE); // retrieve active Element
	String strNew = "";
	Prompter.setString( &strNew);
	Prompter.setComment( "Enter new property:");
	Prompter.create();
	if( strNew.length()){
	  String *pStrg = new String( strNew);
	  strList.ins_before( (Pix)retrievePix( i), *pStrg);
	}
	SHORT j = plb->queryTopIndex();
	printToListBox();
	plb->setTopIndex( j);
	plb->selectItem( i, TRUE);
      }
      break;
    case SB_APPEND_BUTT:
      // First this was implemented as an append at the end of the list.
      // But this wasn't intuitive and so I've changed it. Now append means
      // an insertion of an item after the actual one.
      {	PrompterDlg Prompter( queryHwnd(), PR_DLG);
	SHORT i = plb->querySelection( LIT_NONE); // retrieve active Element
	String strNew = "";
	Prompter.setString( &strNew);
	Prompter.setComment( "Enter new property:");
	Prompter.create();
	if( strNew.length()){
	  String *pStrg = new String( strNew);
	  strList.ins_after( (Pix)(retrievePix( i)), *pStrg);
	  SHORT j = plb->queryTopIndex();
	  printToListBox();
	  plb->setTopIndex( j);
	  plb->selectItem( i+1, TRUE);
	} else {
	  SHORT j = plb->queryTopIndex();
	  printToListBox();
	  plb->setTopIndex( j);
	  plb->selectItem( i, TRUE);
	}
      }
      break;
    case SB_DELETE_BUTT:
      {	
	SHORT i = plb->querySelection( LIT_NONE); // retrieve active Element
	Pix p = i ? (Pix)retrievePix(i-1) : NULL;
	strList.del_after( p);
	printToListBox();
	setState(0);
      }
      break;
    case SB_OK_BUTT:		// OK Button Pressed
      //DosBeep( 100, 100);
      *pList = strList;		// copy local list to original list
      destroy();
      break;
    case SB_CANCEL_BUTT:	// Cancel Button Pressed
      destroy();
      break;
    }
  }
  *fDoDefault = FALSE;
  return 0;
}

// 
// service methods for SingleBrowser
//

// void SingleBrowser::printToListBox( void)
//
// This method prints the contents of the local StrDLList 
// to the list box

VOID SingleBrowser::printToListBox( VOID)
{
  plb->enableUpdate( FALSE);	// disable update for performance reasons
  plb->deleteAll();
  for(Pix i = strList.first();
      i != 0;
      strList.next(i)) 
    plb->insertItem( LIT_END, (char*)(strList(i)));
  plb->show( TRUE);		// enable update and force redraw
}

// String* SingleBrowser::retrieve( SHORT iItem)
//
// This method returns a pointer to the String at index iItem.
// The pointer is valid only for exisiting values of iItem.

String* SingleBrowser::retrieve( SHORT iItem)
{ 
  SHORT s;
  Pix   i;

  for(s=0, i=strList.first(); s != iItem; s++)
    strList.next(i);
  return &(strList(i));
}

Pix SingleBrowser::retrievePix( SHORT iItem)
{
  SHORT s;
  Pix   i;

  for(s=0, i=strList.first(); s != iItem; s++)
    strList.next(i);
  return (i);
}

// VOID SingleBrowser::setState( SHORT sState)
//
// This method changes the state of the Buttons in the
// dialog according to the transmitted state.
// Only the state of the Insert, Append and Delete Buttons is
// changed.

VOID SingleBrowser::setState( SHORT sState)
{
  switch( sState) {
  case 0: 	
    plb->enable( TRUE);
    pbtInsert->enable( FALSE);
    pbtAppend->enable( FALSE);
    pbtDelete->enable( FALSE);
    break;

  case 1:
    plb->enable( TRUE);
    pbtInsert->enable( TRUE);
    pbtAppend->enable( TRUE);
    pbtDelete->enable( TRUE);
    break;
  }
}


VOID SingleBrowser::editEntry( VOID)
{ SHORT iSelect;
  SHORT iTopIndex;
  
  PrompterDlg Prompter( HWND_DESKTOP, PR_DLG);
  String test = "Hallo";
  CHAR   *szComment="Edit the line, press OK to accept the change.";
  iTopIndex = plb->queryTopIndex();
  // find the selected line
  Prompter.setString
    (retrieve(iSelect=plb->querySelection( LIT_NONE)));
  Prompter.setComment( szComment);
  Prompter.create();
  // changes are detected by parent in lbmain
  //if( Prompter.fChanged) fChanged = TRUE;
  printToListBox();
  plb->setTopIndex( iTopIndex);
  plb->selectItem( iSelect, TRUE);
  setState( 1);
}
