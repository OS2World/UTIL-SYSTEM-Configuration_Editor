// This may look like C code, but it is really -*- C++ -*-
/* 
Copyright (C) 1988 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#ifndef _StrDLList_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StrDLList_h 1

#include <Pix.h>
#include "Strdefs.h"

#ifndef _StrDLListNode_h
#define _StrDLListNode_h 1

struct StrDLListNode
{
  StrDLListNode*         bk;
  StrDLListNode*         fd;
  Str                    hd;
                         StrDLListNode();
                         StrDLListNode(Str& h, 
                                       StrDLListNode* p = 0,
                                       StrDLListNode* n = 0);
                         ~StrDLListNode();
};

inline StrDLListNode::StrDLListNode() {}

inline StrDLListNode::StrDLListNode(Str& h, StrDLListNode* p,
                                    StrDLListNode* n)
  :hd(h), bk(p), fd(n) {}

inline StrDLListNode::~StrDLListNode() {}

typedef StrDLListNode* StrDLListNodePtr;

#endif

class StrDLList
{
  friend class          StrDLListTrav;

  StrDLListNode*        h;

public:
                        StrDLList();
                        StrDLList(StrDLList& a);
                        ~StrDLList();

  StrDLList&            operator = (StrDLList& a);

  int                   empty();
  int                   length();

  void                  clear();

  Pix                   prepend(Str& item);
  Pix                   append(Str& item);
  void                  join(StrDLList&);

  Str&                  front();
  Str                   remove_front();
  void                  del_front();

  Str&                  rear();
  Str                   remove_rear();
  void                  del_rear();

  Str&                  operator () (Pix p);
  Pix                   first();
  Pix                   last();
  void                  next(Pix& p);
  void                  prev(Pix& p);
  int                   owns(Pix p);
  Pix                   ins_after(Pix p, Str& item);
  Pix                   ins_before(Pix p, Str& item);
  void                  del(Pix& p, int dir = 1);
  void                  del_after(Pix& p);

  void                  error(const char* msg);
  int                   OK();
};


inline StrDLList::~StrDLList()
{
  clear();
}

inline StrDLList::StrDLList()
{
  h = 0;
}

inline int StrDLList::empty()
{
  return h == 0;
}


inline void StrDLList::next(Pix& p)
{
  p = (p == 0 || p == h->bk)? 0 : Pix(((StrDLListNode*)p)->fd);
}

inline void StrDLList::prev(Pix& p)
{
  p = (p == 0 || p == h)? 0 : Pix(((StrDLListNode*)p)->bk);
}

inline Pix StrDLList::first()
{
  return Pix(h);
}

inline Pix StrDLList::last()
{
  return (h == 0)? 0 : Pix(h->bk);
}

inline Str& StrDLList::operator () (Pix p)
{
  if (p == 0) error("null Pix");
  return ((StrDLListNode*)p)->hd;
}

inline Str& StrDLList::front()
{
  if (h == 0) error("front: empty list");
  return h->hd;
}

inline Str& StrDLList::rear()
{
  if (h == 0) error("rear: empty list");
  return h->bk->hd;
}

#endif
