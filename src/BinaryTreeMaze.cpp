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

#include "BinaryTreeMaze.h"

#include <stdlib.h>

BinaryTreeMaze::BinaryTreeMaze(int x, int y)
  : Maze(x,y)
{}

void BinaryTreeMaze::Generate()
{
  bool move_up;
  Point p;

  for (int i = 1; i < Columns() - 1; i++)
  {
    for (int j = 1; j < Rows() - 1; j++)
    {
      move_up = rand() % 2;
      p = Point(i,j);

      if (move_up)
      {
        if (InBounds(p.Up()))
          OpenPassage(p, Cell::Direction::UP);
        else if (InBounds(p.Left()))
          OpenPassage(p, Cell::Direction::LEFT);
      }
      else
      {
        if (InBounds(p.Left()))
          OpenPassage(p, Cell::Direction::LEFT);
        else if (InBounds(p.Up()))
          OpenPassage(p, Cell::Direction::UP);
      }
      //PrintMaze();
    }
  }
}
