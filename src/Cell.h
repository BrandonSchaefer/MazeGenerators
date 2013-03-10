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

#ifndef CELL
#define CELL

class Cell
{
public:
  Cell();

  enum Direction
  {
    RIGHT = 1 << 0,
    DOWN  = 1 << 1,
    LEFT  = 1 << 2,
    UP    = 1 << 3
  };

  void AddDirection(Direction dir);
  void RemoveDirection(Direction dir);

  bool Empty() const;
  bool RightOpen() const;
  bool DownOpen() const;
  bool LeftOpen() const;
  bool UpOpen() const;

  void SetParent(Cell* cell);
  Cell* GetParent();

  bool path;

private:
  unsigned int open_directions_;
  Cell* parent_;
};

#endif // CELL
