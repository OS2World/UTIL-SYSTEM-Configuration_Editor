// this might look like 'C', but it's really  -*-c++-*-
/* pmviews.h
 *
 * master include file for PMviews, includes all other headers
 *
 * Language        : C++
 * Operating System: OS/2 V2.0 and higher
 * Compiler        : GNU GCC V2.1 and higher
 *
 *
 * $Id: pmviews.h,v 1.1 1992/07/19 02:01:07 gruen Exp $
 * $Log: pmviews.h,v $
 * Revision 1.1  1992/07/19  02:01:07  gruen
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

#include <pmviews/session.h>
#include <pmviews/window.h>
#include <pmviews/dialog.h>
#include <pmviews/controls.h>

