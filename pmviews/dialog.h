// this might look like 'C', but it's really  -*-c++-*-
/* dialog.h
 *
 * Klssendeklaration der Dialog-Window-Klassen
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
 * $Id: dialog.h,v 1.3 1992/08/29 18:16:07 gruen Exp $
 * $Log: dialog.h,v $
 * Revision 1.3  1992/08/29  18:16:07  gruen
 * Version as used by cfged 1.0 beta. Applied some additional callbacks and
 * fixed bugs.
 *
 * Revision 1.2  1992/08/09  22:18:38  gruen
 * corrected some bugs, changed the contsructors for the dialog windows, appended
 * some methods.
 *
 * Revision 1.1  1992/07/19  02:01:13  gruen
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
 * The main goals of the Dialog class are:
 * o Relieve the programmer of writing a WindowProc (Callback).
 *   Instead subclassing with virtual methods is used.
 * o Supply a calm, secure interface to the programmer.
 * 
 * The dialog class should be used in conjunction with a 
 * Dialog-Box Editor (i.e. dlgbox).
 * 
 * Wie arbeitet die Klasse?
 * Zu Beginn einer Session wird fÅr jede, i.d.R. mit dem
 * Dialogbox-Editor erstellte, Dialogbox ein Objekt vom Typ
 * Dialog erzeugt. Dabei werden dem Konstruktor die Adresse
 * des Owner-Windows Objekts (Klasse StdWindow) sowie die
 * Resource-ID des Dialogs Åbergeben. Diese Informationen
 * werden im Objekt (einer Instanz der Klasse Dialog) verankert.
 * Danach werden der Klasse die Dialog-Elemente, auf die
 * eine Reaktion erfolgen soll, die vom Standard abweicht,
 * uebergeben. Dies erfolgt mit der Methode Dialog::Add.
 *
 * Wenn nun der Dialog zur Anzeige gebracht werden soll, 
 * wird die Methode Dialog::Create benutzt. Diese Methode
 * fragt erzeugt den Dialog.
 *
 * class MyDialog : public Dialog {
 * public:
 *   Initialize( HWND hwndDlg) {
 *     StringBox.SetText( "Hallo");
 *   }
 */

#ifndef DIALOG_H_INCLUDED
#define DIALOG_H_INCLUDED

class Dialog {
private:
  static Dialog  *pDialogList;
  Dialog         *pDialogNext;
  CHAR           szTitle[80];
  USHORT         idRes;
  HWND           hwndParent;
  HWND           hwndOwner;
  HWND           hwndDlg;
  static MRESULT StaticDlgWndProc(HWND hwnd, USHORT msg,
				  MPARAM  mp1, MPARAM  mp2);     
  MRESULT        DlgWndProc(HWND hwnd, USHORT msg,
			    MPARAM  mp1, MPARAM  mp2);
  

public:
  Dialog( HWND hwndOwnerNew,	        /* Owner Window (hwndClient) */
	  USHORT  idResNew,            /* Ressource ID of Dialog    */
	  HWND hwndParentNew=HWND_DESKTOP); 
  VOID            create();           /* Erzeugung des Fensters  */
  HWND            load();
  VOID            destroy();          /* Zerstîren des Fensters  */
  virtual MRESULT msgInitDlg( HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgCommand( HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgControl( HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgActivate(HWND hwnd, USHORT msg,
			      MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgClose(HWND hwnd, USHORT msg,
			   MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  virtual MRESULT msgDestroy(HWND hwnd, USHORT msg,
			     MPARAM  mp1, MPARAM  mp2, BOOL *fDoDefault);
  /* Service methods, query */
  HWND            queryHwnd( VOID) { return hwndDlg;}
  BOOL            querySize( SIZEL *pSize);       /* TRUE signals success */
  BOOL            queryPos( POINTL *pPos);        /* TRUE signals success */
  HWND            queryHwndOwner( VOID);          /* ret. handle to owner */
  /* Service methods, set */
  BOOL            setPos( POINTL *pPos);          /* TRUE signals success */
  BOOL            show( BOOL fShow);              /* TRUE signals success */
  BOOL            enable( BOOL fEnable);          /* TRUE signals success */
  // set the title of the window
  // this method is only usable, if the dialog is displayed
  BOOL            setTitle( CHAR *szNewTitle);    /* Set the dialog title */

};
#endif /* DIALOG_H_INCLUDED */









