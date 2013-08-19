// this might look like 'C', but it's really  -*-c++-*-
/* dialog.cc
 *
 * Methoden der Dialog-Klasse von PMviews 
 *
 * Die Dialog-Klasse ermoeglichen die Generierung
 * von PM-Dialogen fuer eine
 * eine PM Applikation
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: dialog.cc,v 1.3 1992/08/29 18:16:06 gruen Exp $
 * $Log: dialog.cc,v $
// Revision 1.3  1992/08/29  18:16:06  gruen
// Version as used by cfged 1.0 beta. Applied some additional callbacks and
// fixed bugs.
//
// Revision 1.2  1992/08/09  22:18:36  gruen
// corrected some bugs, changed the contsructors for the dialog windows, appended
// some methods.
//
// Revision 1.1  1992/07/19  02:01:11  gruen
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

MRESULT EXPENTRY MyDlgWndProc(HWND hwnd, USHORT msg,
					 MPARAM  mp1, MPARAM  mp2);

#include "session.h"
#include "window.h"
#include "dialog.h"

Dialog *Dialog::pDialogList = NULL;

/* Dialog::Dialog()
 *
 * Konstruktor der Klasse Dialog.
 * Hier werden die notwendigen Daten gesichert.
 * Der (notwendige) Eintrag der (PM-)Klasse beim System 
 * sowie die Erzeugung des Fensters erfolgen beim 
 * Create-Aufruf.
 */

Dialog::Dialog(HWND hwndOwnerNew,               /* Konstruktor der Klasse */
	       USHORT  idResNew,
               HWND hwndParentNew=HWND_DESKTOP) /* Ressource ID of Dialog */
{
  hwndParent = hwndParentNew;
  hwndOwner  = hwndOwnerNew;
  hwndDlg    = 0L;
  idRes      = idResNew;
}


/* Dialog::create()
 *
 * create-Methode der Klasse Dialog.
 * Das Dialog-Fenster wird mittels WinDlgBox erzeugt.
 */

VOID Dialog::create()
{
  /* register this dialog in the List of displayed dialogs */
  pDialogNext = pDialogList;
  pDialogList = this;
  /* create the dialog box via PM */
  WinDlgBox (hwndParent,     
	     hwndOwner,
	     StaticDlgWndProc,
	     (HMODULE) NULL,
	     idRes,
	     this);
}  

/* Dialog::load()
 * 
 * Loading a Dialog, preparing a modeless Dialog box
 */
HWND Dialog::load()
{
  /* register this dialog in the List of displayed dialogs */
  pDialogNext = pDialogList;
  pDialogList = this;
  /* create the dialog box via PM */
  return WinLoadDlg(hwndParent,     
	            hwndOwner,
	            StaticDlgWndProc,
	            (HMODULE) NULL,
		    idRes,
		    this);
}  

/* Dialog::destroy()
 *
 * destroy-Methode der Klasse Dialog.
 * Diese Methode zertst”rt den Dialog.
 */

VOID Dialog::destroy()
{
  Dialog  *pTargetDialog;
  /* Dismiss the dialog */
  WinDismissDlg(hwndDlg, 0);
  /* remove the Dialog from the list of active Dialog boxes */
  if( pDialogList == this) {
    pDialogList = pDialogList->pDialogNext;
    return;
  }
  for(pTargetDialog = pDialogList; 
      pTargetDialog != NULL && pTargetDialog->pDialogNext != NULL;
      pTargetDialog = pTargetDialog->pDialogNext) {
    if( pTargetDialog->pDialogNext == this) {
      pTargetDialog = pTargetDialog->pDialogNext->pDialogNext;
      break;
    }
  }
}

/* Dialog::StaticDlgWndProc
 *
 * Diese Funktion ist der staische Window-Handler fuer die Dialog Class
 * Sie verarbeitet alle eingehenden Messages und ruft die
 * Methode DlgWndProc Instanz der Klasse auf.
 */
 
MRESULT Dialog::StaticDlgWndProc(HWND hwnd, USHORT msg,
				 MPARAM  mp1, MPARAM  mp2)
{
  Dialog  *pTargetDialog;

  /* if WM_INITDLG is passed, register the instance      */
  if( msg == WM_INITDLG) {
    pTargetDialog = (Dialog*)PVOIDFROMMP( mp2);
    pTargetDialog->hwndDlg = hwnd;
  }
  /* locate the instance in the list of existing dialogs */
  for(pTargetDialog = pDialogList; pTargetDialog != NULL;
      pTargetDialog = pTargetDialog->pDialogNext) {
    if( pTargetDialog->hwndDlg == hwnd)
      return pTargetDialog->DlgWndProc( hwnd, msg, mp1, mp2);
  }
  /* this should never be reached */
  return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

/* Dialog::DlgWndProc
 *
 * Diese Funktion ist der Window-Handler fuer die Dialog Class
 * Sie verarbeitet alle eingehenden Messages und ruft die
 * entsprechenden virtuellen Methoden der Klasse auf.
 */
 
MRESULT Dialog::DlgWndProc(HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2)
{
  BOOL    fDoDefault = TRUE;
  MRESULT result;

  switch( msg) {
  case WM_INITDLG: 
    result=msgInitDlg(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_COMMAND: 
    result = msgCommand(hwnd,msg,mp1,mp2,&fDoDefault); 
    /* if default processing is used, do it explicit */
    /* this is required to remove the dialog from the active dialog list */
    if( fDoDefault) {
      destroy();
      result = 0;
      fDoDefault = FALSE;
    }
    break;

  case WM_CONTROL: 
    result=msgControl(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_ACTIVATE:
    result = msgActivate(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_CLOSE:
    result = msgClose(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_DESTROY: 
    result = msgDestroy(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  default:
    fDoDefault = TRUE;
  }
  return fDoDefault ? WinDefDlgProc (hwnd, msg, mp1, mp2) : result;
}

MRESULT Dialog::msgInitDlg( HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT Dialog::msgCommand( HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT Dialog::msgControl( HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT Dialog::msgActivate(HWND hwnd, USHORT msg,
			    MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT Dialog::msgClose(HWND hwnd, USHORT msg,
			    MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT Dialog::msgDestroy(HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

BOOL    Dialog::querySize( SIZEL *pSize)
{
  RECTL rcl;
  BOOL  fReturn;
  
  fReturn = WinQueryWindowRect( hwndDlg, &rcl);
  pSize->cx = rcl.xRight;
  pSize->cy = rcl.yTop;    
  return fReturn;
}

BOOL    Dialog::queryPos( POINTL *pPos)
{
  SWP   swp;
  BOOL  fReturn;
  
  fReturn = WinQueryWindowPos( hwndDlg, &swp);
  pPos->x = swp.x;
  pPos->y = swp.y;    
  return fReturn;
}

HWND Dialog::queryHwndOwner( VOID)
{
  return hwndOwner;
}

BOOL    Dialog::setPos( POINTL *pPos)
{
  return WinSetWindowPos( hwndDlg, HWND_TOP, 
			 pPos->x, pPos->y, 0, 0, 
			 SWP_MOVE|SWP_SHOW);
}

BOOL    Dialog::show( BOOL fShow)
{
  return WinShowWindow( hwndDlg, fShow); 
}

BOOL    Dialog::enable( BOOL fEnable)
{
  return WinEnableWindow( hwndDlg, fEnable);
}


BOOL Dialog::setTitle( CHAR *szNewTitle)
{
  if( !hwndDlg) return FALSE;
    return WinSetWindowText( hwndDlg, (PSZ)szNewTitle);
}

/* E O F */
