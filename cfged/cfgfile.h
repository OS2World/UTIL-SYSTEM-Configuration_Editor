// this might look like 'C', but it's really  -*-c++-*-
/* cfgfile.h
 *
 * Declaration of class CfgFile
 *
 * this class allows access to the Configuration File CONFIG.SYS
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 * History:
 * Edit Histroy:
 *
 * $Id: cfgfile.h,v 1.2 1992/08/29 16:12:02 gruen Exp $
 * $Log: cfgfile.h,v $
 * Revision 1.2  1992/08/29  16:12:02  gruen
 * Fixed several bugs. This will become the official beta-release.
 *
 * Revision 1.1  1992/07/17  00:46:57  gruen
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
#ifndef cfgfile_h
#define cfgfile_h

#include "StrDLL.h"

class CfgFile {
public:
  StrDLList strList;

  void clear( void);
  int  read( char *szFileName);
  int  save( char *szFileName, char *szOldFileName);
  void printToListBox( ListBox  *plb);
  String* retrieve( SHORT iItem);
  Pix retrievePix( SHORT iItem);
  void list( void);
};
#endif /* cfgfile_h */
