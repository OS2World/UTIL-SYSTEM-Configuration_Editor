// this might look like 'C', but it's really  -*-c++-*-
/* lbmain.cc
 *
 * Implementation of class MainBrowserDlg for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: lbmain.cc,v 1.3 1992/08/29 16:12:03 gruen Exp $
 * $Log: lbmain.cc,v $
// Revision 1.3  1992/08/29  16:12:03  gruen
// Fixed several bugs. This will become the official beta-release.
//
// Revision 1.2  1992/08/09  21:55:25  gruen
// beta release 1.0 of cfged. Changed the architecture: now using a dialog
// box as main window. As an result the accelerators now work. As goodie
// there is a new special-browser for HELP and last but not least the
// warning at the end of the program occures only if there not saved
// changes to the configuration.
//
// Revision 1.1  1992/07/17  00:23:31  gruen
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pmviews/pmviews.h>

#include "cfgfile.h"
#include "lbmain.h"
#include "maindlg.h"
#include "prompter.h"
#include "pmctool.h"
#include "sbrowser.h"
#include "cfged.h"
#include "about.h"

BOOL MainBrowserDlg::fChanged = FALSE; // no change by default 

     MainBrowserDlg::MainBrowserDlg( HWND hwndOwnerNew, 
				    USHORT  idResNew,
                                    HWND hwndParentNew=HWND_DESKTOP)
:( hwndOwnerNew, idResNew, hwndParentNew) {
	      
  plbMain = new ListBox( this, MAIN_LB);
  pbtEdit   = new CntrlWindow( this, EDIT_BUTT);
  pbtBrowse = new CntrlWindow( this, BROWSE_BUTT);
  pbtInsert = new CntrlWindow( this, INSERT_BUTT);
  pbtAppend = new CntrlWindow( this, APPEND_BUTT);
  pbtDelete = new CntrlWindow( this, DELETE_BUTT);
  pLdCfgDlg = NULL;
}

VOID MainBrowserDlg::setState( int stateNew) {
  switch( stateNew) {
  case 0: 	
    plbMain->enable( TRUE);
    pbtEdit->enable( FALSE);
    pbtBrowse->enable( FALSE);
    pbtInsert->enable( FALSE);
    pbtAppend->enable( FALSE);
    pbtDelete->enable( FALSE);
    break;

  case 1:
    plbMain->enable( TRUE);
    pbtEdit->enable( TRUE);
    pbtBrowse->enable( TRUE);
    pbtInsert->enable( TRUE);
    pbtAppend->enable( TRUE);
    pbtDelete->enable( TRUE);
    break;

  case 2:			// all disabled 
    plbMain->enable( FALSE);
    pbtEdit->enable( FALSE);
    pbtBrowse->enable( FALSE);
    pbtInsert->enable( FALSE);
    pbtAppend->enable( FALSE);
    pbtDelete->enable( FALSE);
    break;
  }
}

VOID MainBrowserDlg::loadCfgList( VOID){
  /* query the right CONFIG.SYS */
  if( !pLdCfgDlg) 
    pLdCfgDlg = new LoadConfigDlg( queryHwnd(), LDCFG_DLG);
  pLdCfgDlg->create();
  /* read the CONFIG.SYS */
  cfile.clear();
  cfile.read( (char*)(*(pLdCfgDlg->pSelected)));
  cfile.printToListBox( plbMain);
  setState(0);
}

VOID MainBrowserDlg::saveCfgList( VOID){
  CHAR   szBuf[300];
  String str("c:\\config.old");

  sprintf( szBuf, "%s%s%s%s",
	  "Do you really want to save the actual configuration ",
	  "to the file '",
	  (char*)(*(pLdCfgDlg->pSelected)),
	  "'?");
  if( PmUserRequest( HWND_DESKTOP, szBuf)) {
    str[0] = (*(pLdCfgDlg->pSelected))[0];
    cfile.save( (char*)(*(pLdCfgDlg->pSelected)), (char*)str);
    sprintf( szBuf, "%s%s%s%s%s%s", 
	    "The actual configuration was stored to the file '",
	    (char*)(*(pLdCfgDlg->pSelected)),
	    "'.\nThe old configuration was saved to the file '",
	    (char*)str,
            "'.\nThe changed version of the configuration takes",
	    "affect after the next shutdown!");
    PmUserMessage( HWND_DESKTOP, szBuf);
    fChanged = FALSE;		// clear change flag
  }

  cfile.printToListBox( plbMain);
  setState(0);
}

VOID MainBrowserDlg::editEntry( VOID)
{ SHORT iSelect;
  SHORT iTopIndex;
  
  // make shure that there is a selection
  if( plbMain->querySelection( LIT_NONE) == LIT_NONE) return;
  PrompterDlg Prompter( queryHwnd(), PR_DLG);
  String test = "Hallo";
  CHAR   *szComment="Edit the line, press OK to accept the change.";
  iTopIndex = plbMain->queryTopIndex();
  // find the selected line
  Prompter.setString
    (cfile.retrieve(iSelect=plbMain->querySelection( LIT_NONE)));
  Prompter.setComment( szComment);
  Prompter.create();		// control goes to dialog
  if( Prompter.fChanged) fChanged = TRUE;
  cfile.printToListBox( plbMain);
  plbMain->selectItem( iSelect, TRUE);
  plbMain->setTopIndex( iTopIndex);
  setState( 1);
}


VOID MainBrowserDlg::browseEntry( SHORT iItem)
{ String    *pString;
  String    strgNew;
  StrDLList strList;
  String    strgComment;
  String    strgRemainer;
  String*   pstrgTemp;
  BOOL      fSemicolon = FALSE;

  // build list
  pString = cfile.retrieve( iItem);
  // verify browsability
  if( !pString->contains( "=")) {
    PmUserMessage( HWND_DESKTOP, 
		  "This entry can't be browsed.\nUse EDIT instead!");
    return;
  }
  strgComment  = pString->before( "=");
  strgRemainer = pString->after( "=");
  while( strgRemainer.contains( ";")){
    pstrgTemp = new String( strgRemainer.before( ";"));
    strList.append( *pstrgTemp);
    strgRemainer = strgRemainer.after( ";");
  }
  if( strgRemainer.length()) {
    pstrgTemp = new String( strgRemainer);
    strList.append( *pstrgTemp);
  }
  else fSemicolon = TRUE;
  // display Dialog
  SingleBrowser sb( queryHwnd(), SB_DLG, "SingleBrowser",
		   (char*)strgComment, &strList);
  sb.create();
  // assemble string
  strgNew = strgComment;
  strgNew += "=";
  for(Pix i = strList.first();
      i != 0;
      strList.next(i)) {
    if( i != strList.first()) strgNew += ";";
    strgNew += strList(i);
  }
  if( fSemicolon) strgNew+=';';
  if( strgNew != *pString) fChanged = TRUE;
  *pString = strgNew;
}
    
MRESULT MainBrowserDlg::msgInitDlg( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  SIZEL     sizl;
  POINTL    ptl = {0,0};
  StdWindow *pSW;
  
  //pSW->show( TRUE);		// display the complete window

  /* loadCfgList to ListBox */
  loadCfgList();
  //setPos( &ptl);
  /* SetUp the position */
  //pSW = queryOwnerWindow();
  //querySize( &sizl);
  //pSW->setClientPos( &ptl, &sizl);
  return 0;
}

MRESULT MainBrowserDlg::msgControl( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  USHORT usID;

  usID = SHORT1FROMMP(mp1);
  *fDoDefault = TRUE;

  switch (SHORT2FROMMP(mp1)) {   
  case LN_ENTER:  /* Auswahl eines Item oder Double-Click */
    editEntry();
    *fDoDefault = FALSE;
    return 0;

  case LN_SELECT: /* selection of a item of the list */
    setState( 1);
    *fDoDefault = FALSE;
    return 0;
  }
  return 0;
}

// this method reacts on the click to buttons
MRESULT MainBrowserDlg::msgCommand( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  if( SHORT1FROMMP( mp2) == CMDSRC_PUSHBUTTON) {   
    switch (SHORT1FROMMP(mp1)) {   
    case EDIT_BUTT:		// OK Button Pressed
      editEntry();
      *fDoDefault = FALSE;
      return 0;               
   
    case BROWSE_BUTT:		// BROWSE Button Pressed
      { SHORT iSelect;
	SHORT iTopIndex;

	iTopIndex = plbMain->queryTopIndex();
	browseEntry( iSelect = plbMain->querySelection( LIT_NONE));
	cfile.printToListBox( plbMain);
	plbMain->setTopIndex( iTopIndex);
	plbMain->selectItem( iSelect, TRUE);
	setState(1);
      }
      *fDoDefault = FALSE;
      return 0;

    case INSERT_BUTT:		// INSERT Button pressed
      {	PrompterDlg Prompter( queryHwnd(), PR_DLG);
	SHORT i = plbMain->querySelection( LIT_NONE);// retrieve active Element
	String strNew = "";
	Prompter.setString( &strNew);
	Prompter.setComment( "Enter new property:");
	Prompter.create();
	if( strNew.length()){
	  String *pStrg = new String( strNew);
	  cfile.strList.ins_before( (Pix)(cfile.retrievePix( i)), *pStrg);
	  fChanged = TRUE;
	}
	SHORT j = plbMain->queryTopIndex();
	cfile.printToListBox( plbMain);
	plbMain->setTopIndex(j);
	plbMain->selectItem( i, TRUE);
      }
      *fDoDefault = FALSE;
      return 0;

    case APPEND_BUTT:
      // First this was implemented as an append at the end of the list.
      // But this wasn't intuitive and so I've changed it. Now append means
      // an insertion of an item after the actual one.
      {	PrompterDlg Prompter( queryHwnd(), PR_DLG);
	SHORT i = plbMain->querySelection( LIT_NONE);// retrieve active Element
	String strNew = "";
	Prompter.setString( &strNew);
	Prompter.setComment( "Enter new property:");
	Prompter.create();
	if( strNew.length()){
	  String *pStrg = new String( strNew);
	  cfile.strList.ins_after( (Pix)(cfile.retrievePix( i)), *pStrg);
	  fChanged = TRUE;
	  SHORT j = plbMain->queryTopIndex();
	  cfile.printToListBox( plbMain);
	  plbMain->setTopIndex(j);
	  plbMain->selectItem( i+1, TRUE);
	} else {
	  SHORT j = plbMain->queryTopIndex();
	  cfile.printToListBox( plbMain);
	  plbMain->setTopIndex(j);
	  plbMain->selectItem( i, TRUE);
	}
      }
      *fDoDefault = FALSE;
      return 0;

    case DELETE_BUTT:
      {	SHORT iTopIndex;

	iTopIndex = plbMain->queryTopIndex();
	SHORT i = plbMain->querySelection( LIT_NONE); // retrieve active
	Pix p = i ? (Pix)cfile.retrievePix(i-1) : NULL;
	cfile.strList.del_after( p);
	fChanged = TRUE;
	cfile.printToListBox( plbMain);
	plbMain->setTopIndex( iTopIndex);
	setState(0);
      }
      *fDoDefault = FALSE;
      return 0;
    }
  }
  if( SHORT1FROMMP( mp2) == CMDSRC_MENU||
      SHORT1FROMMP( mp2) == CMDSRC_ACCELERATOR) {   
    switch (SHORT1FROMMP(mp1)) {   
    case IDM_OPEN:		// Save Menu selected
      loadCfgList();
      *fDoDefault = FALSE;
      return 0;

    case IDM_EXIT:
      WinPostMsg( hwnd, WM_CLOSE, 0L, 0L); // post WM_CLOSE message to yourself
      *fDoDefault = FALSE;
      return 0;

    case IDM_SAVE:		// Save Menu selected
      saveCfgList();
      *fDoDefault = FALSE;
      return 0;

    case IDM_ABOUT:		// OK Button Pressed
      AboutDlg about( queryHwnd(), ABOUT_DLG);
      about.create();		// blocks until OK
      *fDoDefault = FALSE;
      return 0;

    case IDM_PATH:		// Browse Path button pressed
      {
	Regex rp( "\\(SET[ \n\t]+PATH[ \n\t]*=\\)");
	browseVariable( &rp);
      }
      *fDoDefault = FALSE;
      return 0;

    case IDM_DPATH:		// Browse DataPath button pressed
      {
	Regex rp( "\\(SET[ \n\t]+DPATH[ \n\t]*=\\)");
	browseVariable( &rp);
      }
      *fDoDefault = FALSE;
      return 0;

    case IDM_LIBPATH:		// Browse LibraryPath button pressed
      {
	Regex rp( "\\(LIBPATH[ \n\t]*=\\)");
	browseVariable( &rp);
      }
      *fDoDefault = FALSE;
      return 0;

    case IDM_HELP:		// Browse HelpPath button pressed
      {
	Regex rp( "\\(SET[ \n\t]+HELP[ \n\t]*=\\)");
	browseVariable( &rp);
      }
      *fDoDefault = FALSE;
      return 0;

    }
  }
  return 0;
}

MRESULT MainBrowserDlg::msgClose(HWND hwnd, USHORT msg, 
		     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault)
{
  *fDoDefault = FALSE;		// no default processing required
  if( fChanged) {		// last chance to save your work
    if( PmUserRequest( HWND_DESKTOP, 
		       "You have changed, but not saved the configuration.\nDo you really want to exit the OS/2 configuration editor?")) {
      // closing the application is realized by quitting the message queue
      WinPostMsg( hwnd, WM_QUIT, 0L, 0L); // close this application 
    }
  }
  else WinPostMsg( hwnd, WM_QUIT, 0L, 0L); // close this application
  return 0;
}

MRESULT MainBrowserDlg::msgActivate( HWND hwnd, USHORT msg, 
				     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault)
{
  //DosBeep( 100, 100);
  //PmUserMessage( "%d %d", (ULONG)hwnd, (ULONG)queryHwnd());
  //if( hwnd == queryHwnd()) DosBeep( 150, 100);
  //WinEnableWindow( hwnd, (BOOL) SHORT1FROMMP(mp1));
  if( (BOOL) SHORT1FROMMP(mp1)) {
    if( plbMain->querySelection(LIT_NONE) == LIT_NONE) setState( 0);
    else setState(1);
  }
  else setState( 2);
  *fDoDefault = TRUE;
  return 0;
}



VOID MainBrowserDlg::browseVariable( Regex *pr)
{
  String str;
  SHORT  j;
  Pix    i;

  for(i = cfile.strList.last(), j = cfile.strList.length() - 1;
      i != 0 && j >= 0;
      cfile.strList.prev(i), j--) {
    str = cfile.strList(i); // copy entry
    str = upcase( str);		  // set upcase
    if( str.contains( *pr)) {
      // browse entry
      browseEntry( j);
      cfile.printToListBox( plbMain);
      setState(0);
      break;
    }
  }
}

