// this might look like 'C', but it's really  -*-c++-*-
/* pmctool.cc
 *
 * Utility functions for easy PM access
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: pmctool.cc,v 1.2 1992/07/18 01:21:25 gruen Exp $
 * $Log: pmctool.cc,v $
// Revision 1.2  1992/07/18  01:21:25  gruen
// corrected minor bugs and enhanced makefile with clean and install section.
//
// Revision 1.1  1992/07/17  00:23:36  gruen
// Initial revision
//
 *
 * Copyright (c) 1990, 1991, 1992 Lutz Grueneberg
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
#include <stdio.h>
#include <stdarg.h>
#include "pmctool.h"
 
static CHAR szPmToolText[256];
 
/*------------------------------------------------------------*
 * VOID PmUserMessage( HWND hwnd, char *szMessage)
 *------------------------------------------------------------*
 *  Diese Funktion gibt die Åberreichte Message als
 *  Box aus.                           
 *  Agiert mit den Parametern wie printf Åber Variable
 *  Argumentenliste
 *------------------------------------------------------------*/
VOID PmUserMessage( HWND hwnd,CHAR *szFormat, ...)
{   
    va_list     ArgPtr;
    
    va_start( ArgPtr, szFormat);
    vsprintf( szPmToolText, szFormat, ArgPtr);    
    WinMessageBox (HWND_DESKTOP, hwnd, (PSZ)szPmToolText,
        (PSZ)"Information:", 0, MB_OK | MB_ICONEXCLAMATION) ;
    va_end( ArgPtr);
}

/*------------------------------------------------------------*
 * SHORT PmUserRequest( HWND hwnd, CHAR *szMessage)
 *------------------------------------------------------------*
 *  Diese Funktion gibt die Åberreichte Message als
 *  Box aus. Dabei wird der Benutzer nach einer Eingabe
 *  befragt. Anwortet er mit ja, kommt ein TRUE zurÅck,
 *  andernfalls ein FALSE.
 *------------------------------------------------------------*/
SHORT PmUserRequest( HWND hwnd,CHAR *szFormat, ...)
{
    va_list     ArgPtr;
    
    va_start( ArgPtr, szFormat);
    vsprintf( szPmToolText, szFormat, ArgPtr);    
    va_end( ArgPtr);
    if( WinMessageBox (HWND_DESKTOP, hwnd,
		       (PSZ)szPmToolText, (PSZ)"Request:", 0, 
		       MB_YESNO | MB_ICONQUESTION) == MBID_YES) return TRUE;
    return FALSE;
}
/* E O F */
