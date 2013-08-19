// this might look like 'C', but it's really  -*-c++-*-
/* pmctool.h
 *
 * Declaration of utility functions for easy PM access
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: pmctool.h,v 1.1 1992/07/17 00:47:06 gruen Exp $
 * $Log: pmctool.h,v $
 * Revision 1.1  1992/07/17  00:47:06  gruen
 * Initial revision
 *
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
/* function prototypes for */                       
/* pmctool.c */
VOID  PmUserMessage( HWND hwnd, CHAR *szFormat, ...);
SHORT PmUserRequest( HWND hwnd,CHAR *szFormat, ...);

