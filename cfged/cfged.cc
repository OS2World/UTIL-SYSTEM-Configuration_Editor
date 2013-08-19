// this might look like 'C', but it's really  -*-c++-*-
/* cfged.cc
 *
 * Implementation of class MyWindow and main function for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: cfged.cc,v 1.3 1992/08/09 21:55:19 gruen Exp $
 * $Log: cfged.cc,v $
// Revision 1.3  1992/08/09  21:55:19  gruen
// beta release 1.0 of cfged. Changed the architecture: now using a dialog
// box as main window. As an result the accelerators now work. As goodie
// there is a new special-browser for HELP and last but not least the
// warning at the end of the program occures only if there not saved
// changes to the configuration.
//
// Revision 1.2  1992/07/21  00:36:52  gruen
// changed main function
//
// Revision 1.1  1992/07/17  00:23:27  gruen
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
#include <Regx.h>
#include <Strng.h>
#include <pmviews/session.h>
#include <pmviews/window.h>
#include <pmviews/dialog.h>
#include <pmviews/controls.h>

#include "pmctool.h"
#include "cfged.h"
#include "maindlg.h"
#include "cfgfile.h"
#include "lbmain.h"
#include "about.h"

MainBrowserDlg    *pMainBrowser;


int     main (int       argc,
              char *    argv[])
{
  Session  *ms = new Session;

  pMainBrowser = new MainBrowserDlg( HWND_DESKTOP, MAIN_BROWSER);
  pMainBrowser->load();
  // This stuff will be hidden in further Versions of PMviews
  // load the menu
  HWND hwndMenu = WinLoadMenu( pMainBrowser->queryHwnd(), 
			       NULLHANDLE, IDM_MAIN);
  WinPostMsg( pMainBrowser->queryHwnd(), 
	      WM_UPDATEFRAME, NULL, NULL);
  // load the icon
  HPOINTER hptr = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, IDP_MAIN);
  WinPostMsg( pMainBrowser->queryHwnd(), WM_SETICON, hptr, NULL);
  // load the accelerator table for the dialog
  HACCEL haccel = WinLoadAccelTable( ms->queryAnchorBlock(),
				     NULLHANDLE, IDA_MAIN);
  WinSetAccelTable( ms->queryAnchorBlock(), 
		    haccel, pMainBrowser->queryHwnd());
  // end of special stuff
  ms->run();
  WinDestroyWindow( pMainBrowser->queryHwnd());
  //pSW->destroy();
  delete ms;
}

