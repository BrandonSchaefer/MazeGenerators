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

#include "PrimsMaze.h"
#include "Marked.h"

#include <stdlib.h>

using namespace std;

PrimsMaze::PrimsMaze(int x, int y)
  : Maze(x,y)
{
}

Cell::Direction PrimsMaze::GetOppositeParentsDirection(Point& current)
{
  Cell cell = Get(current);

  if (cell.GetParent() == &Get(current.Right()))
    return Cell::Direction::LEFT;
  else if (cell.GetParent() == &Get(current.Down()))
    return Cell::Direction::UP;
  else if (cell.GetParent() == &Get(current.Left()))
    return Cell::Direction::RIGHT;
  else
    return Cell::Direction::DOWN;
}

void PrimsMaze::Generate()
{
  Marked marked(Columns(), Rows());
  vector<Point> walls;

  int randN;
  Point opp_cur;
  Cell::Direction opp_dir;

  Point start(1,1);

  Point current((Columns()-2)/2, (Rows()-2)/2);
  Get(current).SetParent(&Get(start));
  marked.Mark(current);
  OpenPassage(current, Cell::Direction::RIGHT);
  walls.push_back(current.Right());

  while (!walls.empty())
  {
    current = walls.back();
    walls.pop_back();

    opp_dir = GetOppositeParentsDirection(current);
    opp_cur = current.Direction(opp_dir);

    if (!marked.IsMarked(current))
    {
      OpenPassage(current, OppositeDirection(opp_dir));
      marked.Mark(current);
      //PrintMaze();

      for (auto dir : directions_)
      {
        Point cur_dir = current.Direction(dir);

        if (!InBounds(cur_dir) || marked.IsMarked(cur_dir))
          continue;

        Get(cur_dir).SetParent(&Get(current));
        walls.push_back(cur_dir);

        randN = rand() % walls.size();
        Point tmp = walls[randN];
        walls[randN] = walls.back();
        walls[walls.size()-1] = tmp;
      }
    }
  }
}

string PrimsMaze::GetName() const
{
  return "PrimsMaze";
}
