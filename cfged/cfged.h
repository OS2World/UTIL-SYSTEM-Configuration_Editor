/* cfged.h
 *
 * Resource header file for CFGED
 *
 * Language        : RC-Language
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : OS/2 2.0 resource compiler, GNU GCC V2.1 and higher
 *
 *
 * $Id: cfged.h,v 1.2 1992/08/09 21:55:21 gruen Exp $
 * $Log: cfged.h,v $
 * Revision 1.2  1992/08/09  21:55:21  gruen
 * beta release 1.0 of cfged. Changed the architecture: now using a dialog
 * box as main window. As an result the accelerators now work. As goodie
 * there is a new special-browser for HELP and last but not least the
 * warning at the end of the program occures only if there not saved
 * changes to the configuration.
 *
 * Revision 1.1  1992/07/17  00:46:55  gruen
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

/* Name Indentifier for the program icon. */

#define ID_RESOURCE      100
#define IDP_MAIN         101   /* the icon for the application */
#define IDA_MAIN         102

/* Name Identifier for the Menu Bar Items. */
#define IDM_MAIN         103 
#define   IDM_FILE         110
#define     IDM_OPEN         112
#define     IDM_SAVE         113
#define     IDM_SAVEAS       114
#define     IDM_EXIT         115
#define     IDM_ABOUT        116
#define   IDM_SPECIAL        120
#define     IDM_PATH         121
#define     IDM_DPATH        122
#define     IDM_LIBPATH      123
#define     IDM_HELP         124
#define     IDM_ENV          125


