// this might look like 'C', but it's really  -*-c++-*-
/* prompter.h
 *
 * Declaration of class PrompterDlg for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: prompter.h,v 1.2 1992/08/09 21:55:38 gruen Exp $
 * $Log: prompter.h,v $
 * Revision 1.2  1992/08/09  21:55:38  gruen
 * beta release 1.0 of cfged. Changed the architecture: now using a dialog
 * box as main window. As an result the accelerators now work. As goodie
 * there is a new special-browser for HELP and last but not least the
 * warning at the end of the program occures only if there not saved
 * changes to the configuration.
 *
 * Revision 1.1  1992/07/17  00:47:08  gruen
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
#ifndef PROMPTER_H_INCLUDED
#define PROMPTER_H_INCLUDED

class PrompterDlg : public Dialog {
  StaticText  *pComment;
  EntryField  *pef;
  CntrlWindow *pbtOK;
  CntrlWindow *pbtCancel;
  CntrlWindow *pbtHelp;
  String      *pStrg;
  CHAR        *pszComment;
  CHAR        szBuf[256];

public:
  BOOL        fChanged;		// change flag, TRUE signals a change

  PrompterDlg( HWND hwndOwnerNew, USHORT  idResNew);
  VOID setString( String* pStrgNew){
    pStrg = pStrgNew;
  }
  VOID setComment( CHAR *szText) {
    pszComment=szText;
  }
  virtual MRESULT msgInitDlg( HWND hwnd, USHORT msg, 
			     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault);
  virtual MRESULT msgCommand( HWND hwnd, USHORT msg, 
			     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault);
};

#endif /* PROMPTER_H_INCLUDED */


