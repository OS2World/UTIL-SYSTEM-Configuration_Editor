// this might look like 'C', but it's really  -*-c++-*-
/* about.cc
 *
 * Implementation of class MainBrowserDlg for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: about.cc,v 1.2 1992/08/09 21:55:15 gruen Exp $
 * $Log: about.cc,v $
// Revision 1.2  1992/08/09  21:55:15  gruen
// beta release 1.0 of cfged. Changed the architecture: now using a dialog
// box as main window. As an result the accelerators now work. As goodie
// there is a new special-browser for HELP and last but not least the
// warning at the end of the program occures only if there not saved
// changes to the configuration.
//
// Revision 1.1  1992/07/17  00:23:25  gruen
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
#include "about.h"
#include "maindlg.h"

     AboutDlg::AboutDlg( HWND hwndOwnerNew, 
			USHORT  idResNew,
			HWND hwndParentNew=HWND_DESKTOP)
:( hwndOwnerNew, idResNew, hwndParentNew) {
	      
  plb = new ListBox( this, AB_LB);
}
    
MRESULT AboutDlg::msgInitDlg( HWND hwnd, USHORT msg, 
				   MPARAM mp1, MPARAM mp2, BOOL *fDoDefault) {
  plb->enableUpdate( FALSE);	// disable update for performance reasons
  plb->deleteAll();
  plb->insertItem
    ( LIT_END, 
     "This program is free software; you can redistribute it and/or modify");
  plb->insertItem
    ( LIT_END, 
     "it under the terms of the GNU General Public License as");
  plb->insertItem
    ( LIT_END, 
     "published by the Free Software Foundation; either version 2 of the");
  plb->insertItem
    ( LIT_END, 
     "License, or (at your option) any later version.  This program is");
  plb->insertItem
    ( LIT_END, 
  "distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;");
  plb->insertItem
    ( LIT_END, 
     "without even the implied warranty of MERCHANTABILITY or FITNESS FOR");
  plb->insertItem
    ( LIT_END, 
     "A PARTICULAR PURPOSE.  See the GNU General Public License for");
  plb->insertItem
    ( LIT_END, 
     "more details. You should have received a copy of the");
  plb->insertItem
    ( LIT_END, 
     "GNU General Public License along with this program;");
  plb->insertItem
    ( LIT_END, "if not, write to the Free Software Foundation,");
  plb->insertItem
    ( LIT_END, "675 Mass Ave, Cambridge, MA 02139, USA.");
  plb->show( TRUE);		// enable update and force redraw
  *fDoDefault = TRUE;
  return 0;
}






