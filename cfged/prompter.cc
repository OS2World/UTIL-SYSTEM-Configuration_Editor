// this might look like 'C', but it's really  -*-c++-*-
/* prompter.cc
 *
 * Declaration of class PrompterDlg for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: prompter.cc,v 1.3 1992/08/29 16:12:07 gruen Exp $
 * $Log: prompter.cc,v $
// Revision 1.3  1992/08/29  16:12:07  gruen
// Fixed several bugs. This will become the official beta-release.
//
// Revision 1.2  1992/08/09  21:55:35  gruen
// beta release 1.0 of cfged. Changed the architecture: now using a dialog
// box as main window. As an result the accelerators now work. As goodie
// there is a new special-browser for HELP and last but not least the
// warning at the end of the program occures only if there not saved
// changes to the configuration.
//
// Revision 1.1  1992/07/17  00:23:38  gruen
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
#include "maindlg.h"
#include "prompter.h"
#include "pmctool.h"

     PrompterDlg::PrompterDlg( HWND hwndOwnerNew, 
			      USHORT  idResNew) 
:( hwndOwnerNew, idResNew) {
  pComment  = new StaticText( this, PR_COMMENT);
  pef       = new EntryField( this, PR_EDIT_FIELD);
  pbtOK     = new CntrlWindow( this, PR_OK_BUTT);
  pbtCancel = new CntrlWindow( this, PR_CANCEL_BUTT);
  pbtHelp   = new CntrlWindow( this, PR_HELP_BUTT);
  pStrg     = NULL;
  pszComment= NULL;
}


MRESULT PrompterDlg::msgInitDlg( HWND hwnd, USHORT msg, 
				MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  pComment->setText( pszComment);
  pef     ->setTextLimit( 512);
  pef     ->setText( (char *)*pStrg);
  pbtHelp ->enable( FALSE);
  fChanged = FALSE;		// initial instance value is no change
  return 0;
}

MRESULT PrompterDlg::msgCommand( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  USHORT usID;

  usID = SHORT1FROMMP(mp1);	// the resource id of the sender
  if( SHORT1FROMMP( mp2) == CMDSRC_PUSHBUTTON) {   
    switch (SHORT1FROMMP(mp1)) {   
    case PR_OK_BUTT:		// OK Button Pressed
      //DosBeep( 100, 100);
      pef->queryText( szBuf, 512);
      if( strcmp( (char*)*pStrg, szBuf)) // record change of contents
	fChanged = TRUE;
      *pStrg = szBuf;
      //PmUserMessage( HWND_DESKTOP, "%s", (const char *)pStrg);
      fDoDefault = FALSE;
      destroy();
      break;
    case PR_CANCEL_BUTT:
      fDoDefault = FALSE;
      destroy();
      break;
    }
  }
  return 0;
}
