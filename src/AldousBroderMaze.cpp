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

#include "AldousBroderMaze.h"
#include "Marked.h"

#include <stdlib.h>

using namespace std;

AldousBroderMaze::AldousBroderMaze(int x, int y)
  : Maze(x,y)
{}

void AldousBroderMaze::Generate()
{
  Marked marked(Columns(), Rows());
  int cell_count = (Columns()-2) * (Rows()-2);

  Point current(1,1);
  Cell::Direction rand_dir;

  while (cell_count > 0)
  {
    rand_dir = GetValidRandomDirection(current);
    current = current.Direction(rand_dir);

    if (!marked.IsMarked(current))
    {
      OpenPassage(current, OppositeDirection(rand_dir));
      marked.Mark(current);
      cell_count--;

      //PrintMaze();
    }
  }
}

string AldousBroderMaze::GetName() const
{
  return "AldousBroderMaze";
}
