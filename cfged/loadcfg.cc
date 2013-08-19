// this might look like 'C', but it's really  -*-c++-*-
/* loadcfg.cc
 *
 * Implementation of class LoadConfigDlg for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: loadcfg.cc,v 1.2 1992/08/09 21:55:29 gruen Exp $
 * $Log: loadcfg.cc,v $
// Revision 1.2  1992/08/09  21:55:29  gruen
// beta release 1.0 of cfged. Changed the architecture: now using a dialog
// box as main window. As an result the accelerators now work. As goodie
// there is a new special-browser for HELP and last but not least the
// warning at the end of the program occures only if there not saved
// changes to the configuration.
//
// Revision 1.1  1992/07/17  00:23:34  gruen
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
//#define INCL_DOS
#include <os2.h>
#include <stdio.h>
#include <unistd.h>
#include <pmviews/pmviews.h>
#include "StrDLL.h"
#include "maindlg.h"
#include "loadcfg.h"
#include "pmctool.h"

     LoadConfigDlg::LoadConfigDlg( HWND hwndOwnerNew,
				    USHORT  idResNew,
                                    HWND hwndParentNew=HWND_DESKTOP)
:( hwndOwnerNew, idResNew, hwndParentNew) {
	      
  plb   = new ListBox( this, LDCFG_LB);
  pbtOK = new CntrlWindow( this, LDCFG_OK_BUTT);
}

		

VOID LoadConfigDlg::setState( int stateNew) {
  switch( stateNew) {
  case 0: 	
    pbtOK->enable( FALSE);
    break;

  case 1:
    pbtOK->enable( TRUE);
    break;
  }
}
// void LoadConfigDlg::printToListBox( void)
//
// This method prints the contents of the local StrDLList 
// to the list box

VOID LoadConfigDlg::printToListBox( VOID)
{
  plb->enableUpdate( FALSE);	// disable update for performance reasons
  plb->deleteAll();
  for(Pix i = strList.first();
      i != 0;
      strList.next(i)) 
    plb->insertItem( LIT_END, (char*)(strList(i)));
  plb->show( TRUE);		// enable update and force redraw
}

// String* LoadConfigDlg::retrieve( SHORT iItem)
//
// This method returns a pointer to the String at index iItem.
// The pointer is valid only for exisiting values of iItem.

String* LoadConfigDlg::retrieve( SHORT iItem)
{ 
  SHORT s;
  Pix   i;

  for(s=0, i=strList.first(); s != iItem; s++)
    strList.next(i);
  return &(strList(i));
}

Pix LoadConfigDlg::retrievePix( SHORT iItem)
{
  SHORT s;
  Pix   i;

  for(s=0, i=strList.first(); s != iItem; s++)
    strList.next(i);
  return (i);
}


MRESULT LoadConfigDlg::msgInitDlg( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  findConfigFiles();
  switch( strList.length()){
  case 0:
    pSelected = NULL;
    PmUserMessage( HWND_DESKTOP,
		  "The CfgEd couldn't find any CONFIG.SYS, exiting\n");
    destroy();
    exit(-1);
    break;

  case 1:
    pSelected = retrieve(0);
    destroy();
    break;

  default:
    printToListBox();
    setState( 0);
    break;
  }
  return 0;
}


MRESULT LoadConfigDlg::msgControl( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  USHORT usID;

  usID = SHORT1FROMMP(mp1);

  switch (SHORT2FROMMP(mp1)) {   
  case LN_ENTER:  /* Auswahl eines Item oder Double-Click */
    pSelected   = retrieve( plb->querySelection( LIT_NONE));
    destroy();
    *fDoDefault = FALSE;
    return 0;

  case LN_SELECT: /* selection of a item of the list */
    setState( 1);
    *fDoDefault = 0;
    return 0;
  }
  return 0;
}

// this method reacts on the click to buttons
MRESULT LoadConfigDlg::msgCommand( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  if( SHORT1FROMMP( mp2) == CMDSRC_PUSHBUTTON) {   
    switch (SHORT1FROMMP(mp1)) {   
    case LDCFG_OK_BUTT:		// OK Button Pressed
      pSelected   = retrieve( plb->querySelection( LIT_NONE));
      *fDoDefault = TRUE;
      return 0;               
    }
  }
  return 0;
}


/*------------------------------------------------------------*
 * VOID LoadConfigDlg::findConfigFiles(VOID)
 *------------------------------------------------------------*
 * Diese Funktion durchsucht alle vorhandenen Laufwerke
 * nach einer Datei mit dem Namen 'config.sys'. Die Ergebnisse
 * werden in einer DLL gespeichert.
 *------------------------------------------------------------*/
VOID LoadConfigDlg::findConfigFiles( VOID)
{
  ULONG   ulCurDisk;
  ULONG   ulDiskMap;
  CHAR    chDrives;
  CHAR    szFileName[] = "C:\\CONFIG.SYS";
  String* str;
  
  strList.clear();
  
  DosQueryCurrentDisk( &ulCurDisk, &ulDiskMap); /*Liste der Laufwerke holen*/
  for( ulDiskMap >>= 2,chDrives = 'C'; chDrives <= 'Z'; chDrives++){
    if( ulDiskMap & 1) {        /* Laufwerksbit gesetzt ?*/
      szFileName[0] = chDrives;
      if( access( szFileName, 00) == 0) { /* gefunden ? */
	str = new String( szFileName);
	strList.append( *str);
      }
    }
    ulDiskMap >>= 1;    /* unteres Bit rausruecken */
  }
}
