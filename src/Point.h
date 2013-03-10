//-*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/* * Copyright (C) 2013 Brandon Schaefer
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Authored by: Brandon Schaefer <brandon.schaefer@canonical.com>
*/

#ifndef POINT
#define POINT

#include "Cell.h"

class Point
{
public:
  Point (int x = 0, int y = 0);
  Point (Point const& p);

  int x() const;
  int y() const;
  
  Point Direction(Cell::Direction dir);

  Point Right();
  Point Down();
  Point Left();
  Point Up();

  bool operator==(Point const& p);

private:
  int x_;
  int y_;
};

#endif // POINT
