// this might look like 'C', but it's really  -*-c++-*-
/* window.cc
 *
 * Methoden der Window-Klassen von PMviews 
 *
 * Die Window-Klassen ermoeglichen die Generierung
 * von PM-Fesnterobjekten fuer eine
 * eine PM Applikation
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: window.cc,v 1.3 1992/08/09 22:18:40 gruen Exp $
 * $Log: window.cc,v $
// Revision 1.3  1992/08/09  22:18:40  gruen
// corrected some bugs, changed the contsructors for the dialog windows, appended
// some methods.
//
// Revision 1.2  1992/07/28  00:36:04  gruen
// fixed a bug in StdWindow::Set...: appended flag SWP_SHOW to the
// WinSetWindowPos-Call.
//
// Revision 1.1  1992/07/19  01:56:12  gruen
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

/* globale Variablen */
StdWindow *globalStdWindowPointer;

/* StdWindow::StdWindow()
 *
 * Konstruktor der Klasse StdWindow.
 * Hier werden die notwendigen Daten gesichert.
 * Der (notwendige) Eintrag der (PM-)Klasse beim System 
 * sowie die Erzeugung des Fensters erfolgen beim 
 * Create-Aufruf.
 */

StdWindow::StdWindow( Session *ps,
                      USHORT idRes)

{
  pSession        = ps;
  strcpy( szTitle, STDWINDOWCLASS);
  flFlags         = FCF_STANDARD;
  flStyle         = WS_VISIBLE | FS_STANDARD;
  idRessources    = idRes;
}


/* StdWindow::create()
 *
 * Create-Methode der Klasse StdWindow.
 * Hier wird die (PM-)Klasse beim System eingetragen
 * und das Fenster mittels WinCreateStdWindow erzeugt.
 */

VOID StdWindow::create()
{
  WinRegisterClass (pSession->queryAnchorBlock(),   // Anchor Block handle
              (PSZ) STDWINDOWCLASS,            // Name of window class
            (PFNWP) StdWindowClientWndProc,    // Window procedure for class   
                    CS_SIZEREDRAW,       // Set redraw on window resize 
                    sizeof(StdWindow*)); // Extra bytes to reserve       
  globalStdWindowPointer = this;
  hwndFrame = 
  WinCreateStdWindow (HWND_DESKTOP,      // Create a parent window 
		      flStyle,           // Window Style
                      &flFlags,          // Creation flags    
                (PSZ) STDWINDOWCLASS,    // window class name
                (PSZ) szTitle,           // Title bar text
		      0L,
            (HMODULE) NULL,  // Resource is in application module
		      idRessources,
                      &hwndClient);
}  

/* StdWindow::destroy()
 *
 * Destroy-Methode der Klasse StdWindow.
 * Diese Methode zertst”rt das StdWindow.
 */

VOID StdWindow::destroy()
{
  WinDestroyWindow(hwndFrame);
}

/* StdWindow::setStyle()
 *
 * setStyle-Methode der Klasse StdWindow.
 * Diese Methode kann vor dem Aufruf der Create-Methode
 * benutzt werden, um den Style des Frame-Windows beim
 * Systemaufruf zu modifizieren. Der Defaultwert ist 
 * WS_VISIBLE | FS_STANDARD.
 * Der neue Style wird als Argument bergeben.
 */
VOID StdWindow::setStyle( ULONG flNewStyle)
{
  flStyle = flNewStyle;
}


/* StdWindow::setFlags()
 *
 * setFlags-Methode der Klasse StdWindow.
 * Diese Methode kann vor dem Aufruf der Create-Methode
 * benutzt werden, um die Creation-Flags des Frame-Windows beim
 * Systemaufruf zu modifizieren. Der Defaultwert ist 
 * FCF_STANDARD.
 * Die neuen Flags werden als Argument bergeben.
 */
VOID StdWindow::setFlags( ULONG flNewFlags)
{
  flFlags = flNewFlags;
}


/* StdWindow::setTitle()
 *
 * setTitle-Methode der Klasse StdWindow.
 * Diese Methode kann zum „ndern der Titelzeile des Fensters
 * benutzt werden. Ihre Benutzung ist auch zur
 * zur Laufzeit des Fensters m”glich (noch nicht implementiert).
 * Der Defaultwert ist der PM-Klassenname. Der neue Name
 * wird als Argument bergeben. Der Name wird im internen
 * Buffer festgehalten.
 */
VOID StdWindow::setTitle( CHAR *szNewTitle)
{
  strcpy( szTitle, szNewTitle);
}

/* StdWindowClientWndProc
 * 
 * Diese Funktion ordnet den Objekt-Instanzen deren
 * message parser zu und fuehrt diesen aus.
 */
MRESULT StdWindowClientWndProc (HWND hwnd, USHORT msg,
				MPARAM  mp1, MPARAM  mp2)
{ 
  StdWindow *pWindow = (StdWindow *)WinQueryWindowULong( hwnd, 0);
  if( msg == WM_CREATE){
    pWindow = globalStdWindowPointer;
    WinSetWindowULong( hwnd, 0, (ULONG)globalStdWindowPointer);
  }
  return pWindow->msgParser(hwnd,msg,mp1,mp2); 
}

/* StdWindow::msgParser
 *
 * Diese Funktion ist der Window-Handler fuer die StdWindow Class
 * Sie verarbeitet alle eingehenden Messages und ruft die
 * entsprechenden virtuellen Methoden der Klasse auf.
 */
 
MRESULT StdWindow::msgParser(HWND hwnd, USHORT msg,
			     MPARAM  mp1, MPARAM  mp2)
{ 
  BOOL      fDoDefault = TRUE;
  MRESULT   result;

  switch (msg){ 
  case WM_CREATE:  
    result = msgCreate(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_CLOSE:
    result = msgClose(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_DESTROY: 
    result = msgDestroy(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_COMMAND:
    result = msgCommand(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_PAINT:   
    result = msgPaint(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  case WM_CONTROL: 
    result = msgControl(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;
    
  case WM_SIZE: 
    result = msgSize(hwnd,msg,mp1,mp2,&fDoDefault); 
    break;

  default: 
    fDoDefault = TRUE;
  }
  result = fDoDefault ? WinDefWindowProc (hwnd, msg, mp1, mp2) : result;
  return result;
}

BOOL    StdWindow::queryClientSize( SIZEL *pSize)
{
  RECTL rcl;
  BOOL  fReturn;
  
  fReturn = WinQueryWindowRect( hwndClient, &rcl);
  pSize->cx = rcl.xRight;
  pSize->cy = rcl.yTop;    
  return fReturn;
}

BOOL    StdWindow::queryClientPos( POINTL *pPos)
{
  SWP   swp;
  BOOL  fReturn;
  
  fReturn = WinQueryWindowPos( hwndClient, &swp);
  pPos->x = swp.x;
  pPos->y = swp.y;    
  return fReturn;
}

BOOL    StdWindow::queryFrameSize( SIZEL *pSize)
{
  RECTL rcl;
  BOOL  fReturn;
  
  fReturn = WinQueryWindowRect( hwndFrame, &rcl);
  pSize->cx = rcl.xRight;
  pSize->cy = rcl.yTop;    
  return fReturn;
}

BOOL    StdWindow::queryFramePos( POINTL *pPos)
{
  SWP   swp;
  BOOL  fReturn;
  
  fReturn = WinQueryWindowPos( hwndFrame, &swp);
  pPos->x = swp.x;
  pPos->y = swp.y;    
  return fReturn;
}

BOOL    StdWindow::setClientSize( SIZEL *pSize)
{
  RECTL rcl = {0L,0L,0L,0L};

  rcl.xRight = pSize->cx;
  rcl.yTop   = pSize->cy;
  WinCalcFrameRect( hwndFrame, &rcl, FALSE);
  return WinSetWindowPos( hwndFrame, HWND_TOP, 
			 0, 0, 
			 (SHORT)(rcl.xRight - rcl.xLeft), 
			 (SHORT)(rcl.yTop   - rcl.yBottom), 
			 SWP_SHOW|SWP_SIZE);
}

BOOL    StdWindow::setClientPos( POINTL *ptl, SIZEL *pSize)
{
  RECTL rcl = {0L,0L,0L,0L};

  rcl.xRight = pSize->cx;
  rcl.yTop   = pSize->cy;
  WinCalcFrameRect( hwndFrame, &rcl, FALSE);
  return WinSetWindowPos( hwndFrame, HWND_TOP, 
			 ptl->x, ptl->y, 
			 (SHORT)(rcl.xRight - rcl.xLeft), 
			 (SHORT)(rcl.yTop   - rcl.yBottom), 
			 SWP_SHOW|SWP_SIZE|SWP_MOVE);
}

BOOL    StdWindow::setClientPos( POINTL *pPos)
{
  return WinSetWindowPos( hwndClient, HWND_TOP, 
			 pPos->x, pPos->y, 0, 0, 
			 SWP_SHOW|SWP_MOVE);
}

BOOL    StdWindow::setFrameSize( SIZEL *pSize)
{
  return WinSetWindowPos( hwndFrame, HWND_TOP, 
			 0, 0, 
			 (SHORT)pSize->cx, 
			 (SHORT)pSize->cy, 
			 SWP_SHOW|SWP_SIZE);
}

BOOL    StdWindow::setFramePos( POINTL *pPos)
{
  return WinSetWindowPos( hwndFrame, HWND_TOP, 
			 pPos->x, pPos->y, 0, 0, 
			 SWP_SHOW|SWP_MOVE);
}

BOOL StdWindow::calcFrameRect( RECTL *prcl, BOOL fFrame)
{
  return WinCalcFrameRect( hwndFrame, prcl, fFrame);
}

BOOL    StdWindow::show( BOOL fShow)
{
  return WinShowWindow( hwndFrame, fShow); 
}

BOOL    StdWindow::enable( BOOL fEnable)
{
  return WinEnableWindow( hwndFrame, fEnable);
}

/* PM-called methods */

MRESULT StdWindow::msgCreate(HWND hwnd, USHORT msg,
			     MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT StdWindow::msgClose(HWND hwnd, USHORT msg,
			    MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT StdWindow::msgDestroy(HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT StdWindow::msgPaint(HWND hwnd, USHORT msg,
			    MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT StdWindow::msgCommand(HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT StdWindow::msgControl(HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}

MRESULT StdWindow::msgSize(HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault)
{
  *fDoDefault = TRUE;
  return 0;
}



/* E O F */
