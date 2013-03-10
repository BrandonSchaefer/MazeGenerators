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
* Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
*/

#include "Point.h"

Point::Point (int x, int y)
  : x_(x)
  , y_(y)
{}

Point::Point (Point const& p)
  : x_(p.x())
  , y_(p.y())
{}

int Point::x() const
{
  return x_;
}

int Point::y() const
{
  return y_;
}

Point Point::Direction(Cell::Direction dir)
{
  switch (dir)
  {
    case (Cell::Direction::RIGHT):
      return Right();
    case (Cell::Direction::LEFT):
      return Left();
    case (Cell::Direction::UP):
      return Up();
    case (Cell::Direction::DOWN):
      return Down();
  }

  return Cell::Direction::RIGHT;
}

Point Point::Right()
{
  return Point(x_, y_+1);
}

Point Point::Down()
{
  return Point(x_+1, y_);
}

Point Point::Left()
{
  return Point(x_, y_-1);
}

Point Point::Up()
{
  return Point(x_-1, y_);
}

bool Point::operator==(Point const& p)
{
  return x_ == p.x_ && y_ == p.y_;
}
