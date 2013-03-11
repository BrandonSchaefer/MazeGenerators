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

#include "Marked.h"
#include "RecursiveBacktrackerMaze.h"

#include <stack>
#include <stdlib.h>

using namespace std;

RecursiveBacktrackerMaze::RecursiveBacktrackerMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
{}

void RecursiveBacktrackerMaze::Generate()
{
  vector<pair<Point, Cell::Direction> > neighbours;
  stack<Point> backtracker;

  int cell_count = (Columns()-2) * (Rows()-2) - 1;

  Point current;
  pair<Point, Cell::Direction> new_cur;

  backtracker.push(start_);
  marked_.Mark(start_);

  while (cell_count > 0)
  {
    neighbours = GetUnMarkedNeighbours(current);

    if (!neighbours.empty())
    {
      new_cur = neighbours[rand() % neighbours.size()];
      backtracker.push(new_cur.first);
      OpenPassage(current, new_cur.second);

      current = new_cur.first;
      marked_.Mark(current);
      cell_count--;

      //PrintMaze();
    }
    else if (!backtracker.empty())
    {
      current = backtracker.top();
      backtracker.pop();
    }
  }
}

vector<pair<Point, Cell::Direction> > RecursiveBacktrackerMaze::GetUnMarkedNeighbours(Point& cur)
{
  vector<pair<Point, Cell::Direction> > neighbours;

  for (auto dir : directions_)
    if (InBounds(cur.Direction(dir)) && !marked_.IsMarked(cur.Direction(dir)))
      neighbours.push_back(make_pair(cur.Direction(dir), dir));

  return neighbours;
}

string RecursiveBacktrackerMaze::GetName() const
{
  return "RecursiveBacktrackerMaze";
}
