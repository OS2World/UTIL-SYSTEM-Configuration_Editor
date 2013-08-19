// this might look like 'C', but it's really  -*-c++-*-
/* window.h
 *
 * Klssendeklaration der Window-Klassen
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
 * $Id: window.h,v 1.2 1992/08/09 22:18:43 gruen Exp $
 * $Log: window.h,v $
 * Revision 1.2  1992/08/09  22:18:43  gruen
 * corrected some bugs, changed the contsructors for the dialog windows, appended
 * some methods.
 *
 * Revision 1.1  1992/07/19  01:56:10  gruen
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
 * Architektur:
 * Ein Fenster (Window) wird durch seinen Konstruktor intern erzeugt.
 * Dies fuehrt jedoch noch nicht zur Generierung eines PM-Fensters.
 * Vielmehr wird das Objekt dadurch initialisiert. Danach ist noch die
 * Manipulation der Flags und Styles mîglich.
 *
 * Durch den Aufruf der Methode Session::Run werden dann nacheinander
 * die Fenster beim PM Angemeldet und erzeugt. Dadurch wird dem Konflikt
 * entgangen, dass nach der PM-Philosopie das am meisten an der
 * Wurzel befindliche Fenster zuerst generiert und daran die oberen
 * Fenster angebunden werden, unter PMviews jedoch meist zuerst die
 * Konstruktoren der obersten Fenster zum Aufbau benutzt werden und
 * erst dann die Basisfenster folgen.
 *   Beispiel PM:
 *     hwndFrame = WinCreateStdWindow(HWND_DESKTOP,...,&hwndClient);
 *     hwndClA1  = WinCreateWindow(hwndClient,...);
 *     hwndClA2  = WinCreateWindow(hwndClient,...);
 *
 *   Beispiel PMviews:
 *     Session *MySession = new Session( new StdWindow( new ClientWindow()));
 *     MySession->Run();
 * 
 * Unter PMviews braucht der Programmierer fÅr die bereitgestellten Klassen
 * keine Window-Prozeduren zu schreiben. Vielmehr wird fÅr die Fenster eine
 * in der Bibliothek bereitgestellte Prozedur benutzt, die virtuelle 
 * Funktionen der Standardklasse zur AusfÅhrung der Methoden benutzt.
 * Der Programmierer erstellt nun also eine Klasse, die die Eigenschaften
 * der Standardklasse erbt und erstellt ggf. Methoden fÅr die virtuellen
 * Methoden, d.h. Vererbung anstelle von Quellcode-Kopieen. Das funktioniert
 * wie folgt: Die Standardklasse meldet sich beim PM an, und reserviert
 * zusÑtzlichen Platz fÅr einen Zeiger auf eine Instanz der Klasse.
 * Die Standard-Window-Prozedur benutzt diesesn Zeiger zum Aufruf 
 * der Aktionen. Die Reservierung dieser Bytes erfolgt mit Hilfe des PM.
 * Die Funktionen WinSetWindowULong und WinQueryWindowULong werden zur
 * Kommunikation mit diesem Speicher benutzt.
 */
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

extern "C" {
  /* This function must be exported so don't mangle the name */
  MRESULT StdWindowClientWndProc (HWND, USHORT, MPARAM, MPARAM);
}

#define STDWINDOWCLASS "StdWindowClass"

class StdWindow {
private:
    StdWindow *clientWindow;
    Session   *pSession;
    ULONG     flStyle;
    ULONG     flFlags;
    CHAR      szTitle[80];
    USHORT    idRessources;
    HWND      hwndFrame;
    HWND      hwndClient;

    

public:
  StdWindow( Session *ps,           /* Konstruktor der Klasse */
	     USHORT  idRes);
  VOID setStyle( ULONG flNewStyle); /* énderung des Styles    */
  VOID setFlags( ULONG flNewFlags); /* énderung der Creation Flags */
  VOID setTitle( CHAR *szNewTitle); /* Setzen des Titels */
  VOID create();                    /* Erzeugung des Fensters  */
  VOID destroy();                   /* Zerstîren des Fensters  */
  /* PM-WM-Message-Handlers */
  MRESULT msgParser(HWND hwnd, USHORT msg,
		    MPARAM  mp1, MPARAM  mp2);
  virtual MRESULT msgCreate(HWND hwnd, USHORT msg,
			    MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgClose(HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgDestroy(HWND hwnd, USHORT msg,
			     MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgPaint(HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgCommand(HWND hwnd, USHORT msg,
			     MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgControl(HWND hwnd, USHORT msg,
			     MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgSize(HWND hwnd, USHORT msg,
			  MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  /* Service methods, query */
  HWND            queryHwnd( VOID) { return hwndClient;}
  BOOL            queryClientSize( SIZEL *pSize); /* TRUE signals success */
  BOOL            queryClientPos( POINTL *pPos);  /* TRUE signals success */
  BOOL            queryFrameSize( SIZEL *pSize);  /* TRUE signals success */
  BOOL            queryFramePos( POINTL *pPos);   /* TRUE signals success */
  /* Service methods, set */

  // setting the client. Theese methods concern the frame with respect
  // to the size of the client area. The position concern the frame.
  BOOL setClientSize( SIZEL *pSize);                /* TRUE signals success */ 
  BOOL setClientPos( POINTL *pPos);                 /* TRUE signals success */
  BOOL setClientPos( POINTL *pPos, SIZEL *pSize);   /* TRUE signals success */
  BOOL setFrameSize( SIZEL *pSize);                 /* TRUE signals success */ 
  BOOL setFramePos( POINTL *pPos);                  /* TRUE signals success */

  // Calculates the frame size and position from client, if fFrame = FALSE
  // or Client size and position from frame, if fFrame = FALSE
  // returns TRUE on success
  BOOL calcFrameRect( RECTL *rcl, BOOL fFrame);     

  BOOL show( BOOL fShow);                           /* TRUE signals success */
  BOOL enable( BOOL fEnable);                       /* TRUE signals success */
};
#endif /* WINDOW_H_INCLUDED */









