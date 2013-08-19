// this might look like 'C', but it's really  -*-c++-*-
/* loadcfg.h
 *
 * Declaration of class LoadConfigDlg for CFGED
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: loadcfg.h,v 1.2 1992/08/09 21:55:31 gruen Exp $
 * $Log: loadcfg.h,v $
 * Revision 1.2  1992/08/09  21:55:31  gruen
 * beta release 1.0 of cfged. Changed the architecture: now using a dialog
 * box as main window. As an result the accelerators now work. As goodie
 * there is a new special-browser for HELP and last but not least the
 * warning at the end of the program occures only if there not saved
 * changes to the configuration.
 *
 * Revision 1.1  1992/07/17  00:47:02  gruen
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
#ifndef LOADCFG_H_INCLUDED
#define LOADCFG_H_INCLUDED

#include "StrDLL.h"

class LoadConfigDlg : public Dialog {
public:
  StrDLList   strList;
  String*     pSelected;

  ListBox     *plb;
  CntrlWindow *pbtOK;

  LoadConfigDlg( HWND hwndOwnerNew, USHORT  idResNew,
		HWND hwndParentNew=HWND_DESKTOP);
  VOID    setState( int stateNew);
  VOID    printToListBox( VOID);
  String* retrieve( SHORT iItem);
  Pix     retrievePix( SHORT iItem);

  virtual MRESULT msgInitDlg( HWND hwnd, USHORT msg, 
			     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault);
  virtual MRESULT msgControl( HWND hwnd, USHORT msg, 
			     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault);
  virtual MRESULT msgCommand( HWND hwnd, USHORT msg, 
			     MPARAM mp1, MPARAM mp2, BOOL *fDoDefault);
private:
  VOID findConfigFiles( VOID);
};

#endif /* LOADCFG_H_INCLUDED */

