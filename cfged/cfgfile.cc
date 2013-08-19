// This may look like C code, but it is really -*- C++ -*-
/* cfgfile.cc
 *
 * Implementation of class CfgFile
 *
 * this class allows access to the Configuration File CONFIG.SYS
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 * $Id: cfgfile.cc,v 1.2 1992/08/29 16:12:00 gruen Exp $
 * $Log: cfgfile.cc,v $
// Revision 1.2  1992/08/29  16:12:00  gruen
// Fixed several bugs. This will become the official beta-release.
//
// Revision 1.1  1992/07/17  00:23:29  gruen
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
#include <stdio.h>
#include <unistd.h>
#include <pmviews/pmviews.h>
#include <Regx.h>
#include <Strng.h>
#include "stream.h"
#include "stdio.h"
#include "cfgfile.h"

void CfgFile::clear()
{
  //for(Pix i = strList.first(); i != 0; strList.next(i)) {
  //  delete &strList(i);
  //}
  strList.clear();
}

int  CfgFile::read( char *szFileName)
{
  FILE   *fp;
  char   szBuf[512];
  String *pstrLine;

  if((fp=fopen( szFileName, "rt"))==NULL) {
    return 0;
  }
  while( fgets( szBuf, 512, fp)) {   
    if( strlen( szBuf) && szBuf[strlen(szBuf)-1] == '\n')
      szBuf[strlen(szBuf)-1] = 0;
    pstrLine = new String( szBuf);
    strList.append( *pstrLine);
  }
  fclose( fp);
  return 1;
}
    

int  CfgFile::save( char *szFileName, char *szOldFileName)
{
  FILE   *fp;
  String *pstrLine;

  if( !access( szOldFileName, 0)) unlink( szOldFileName);
  rename( szFileName, szOldFileName);

  if((fp=fopen( szFileName, "wt"))==NULL) {
    return 0;
  }
  for(Pix i = strList.first();
      i != 0;
      strList.next(i)) {
    fputs( (char*)strList(i), fp);
    fputs( "\n", fp);
  }
  fclose( fp);
  return 1;
}

void CfgFile::printToListBox( ListBox  *plb)
{
  plb->enableUpdate( FALSE);	// disable update for performance reasons
  plb->deleteAll();
  for(Pix i = strList.first();
      i != 0;
      strList.next(i)) 
    plb->insertItem( LIT_END, (char*)(strList(i)));
  plb->show( TRUE);		// enable update and force redraw
}

String* CfgFile::retrieve( SHORT iItem)
{ 
  SHORT s;
  Pix   i;

  for(s=0, i=strList.first(); s != iItem; s++)
    strList.next(i);
  return &strList(i);
}

Pix CfgFile::retrievePix( SHORT iItem)
{
  SHORT s;
  Pix   i;

  for(s=0, i=strList.first(); s != iItem; s++)
    strList.next(i);
  return (i);
}

void CfgFile::list( void)
{
  for(Pix i = strList.first();
      i != 0;
      strList.next(i))
    cout << strList(i) << '\n';
}

