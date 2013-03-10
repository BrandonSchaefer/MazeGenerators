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

#include "SideWinderMaze.h"

#include <stdlib.h>

using namespace std;

SideWinderMaze::SideWinderMaze(int x, int y)
  : Maze(x, y)
{}
  
void SideWinderMaze::Generate()
{
  vector<Point> run_set;
  bool open_east = false;

  Point up_point;
  Point current;
  run_set.push_back(start_);

  for (int j = 1; j < Rows()-2; j++)
    OpenPassage(Point(1,j), Cell::Direction::RIGHT);

  for (int i = 2; i <= Columns()-2; i++)
  {
    current = Point(i,1);

    for (int j = 1; j <= Rows()-2; j++)
    {
      open_east = rand() % 2;

      if (open_east && InBounds(current.Right()))
      {
        OpenPassage(current, Cell::Direction::RIGHT);
        current = current.Right();
        run_set.push_back(current);
      }
      else
      {
        up_point = (run_set.empty() ? current : run_set[rand() % run_set.size()]);
        OpenPassage(up_point, Cell::Direction::UP);
        current = current.Right();
        run_set.clear();
      }
    }
  }
}
