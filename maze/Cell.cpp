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

#include "Cell.h"

using namespace std;

Cell::Cell()
  : open_directions_(0)
  , parent_(nullptr)
{}

void Cell::AddDirection(Direction dir)
{
  open_directions_ |= dir;
}

void Cell::RemoveDirection(Direction dir)
{
  open_directions_ &= ~(dir);
}

bool Cell::Empty() const
{
  return open_directions_ == 0;
}

bool Cell::RightOpen() const
{
  return (open_directions_ & Cell::Direction::RIGHT);
}

bool Cell::DownOpen() const
{
  return (open_directions_ & Cell::Direction::DOWN);
}

bool Cell::LeftOpen() const
{
  return (open_directions_ & Cell::Direction::LEFT);
}

bool Cell::UpOpen() const
{
  return (open_directions_ & Cell::Direction::UP);
}

void Cell::SetParent(Cell* cell)
{
  parent_ = cell;
}

Cell* Cell::GetParent() const
{
  return parent_;
}
