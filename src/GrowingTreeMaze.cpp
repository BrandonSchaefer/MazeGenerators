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

#include "GrowingTreeMaze.h"

#include <stdlib.h>

using namespace std;

GrowingTreeMaze::GrowingTreeMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
{}

void SwapAndPop(vector<Point>& open_neighbours, int index)
{
  Point tmp_pt = open_neighbours.back();
  open_neighbours[index] = tmp_pt;
  open_neighbours.pop_back();
}

// Base Case: If no more open neighbours return default values
// Recusive, If: Find a random point that has an open neighbours
//          Else: Remove from the vector, and look for a new one
pair<Point, Cell::Direction> GrowingTreeMaze::GetValidNeighbour(vector<Point>& open_neighbours)
{
  if (open_neighbours.empty())
    return make_pair(Point(), Cell::Direction::RIGHT);

  int randN = rand() % open_neighbours.size();
  vector<Cell::Direction> valid_dir;

  Point rand_pt = open_neighbours[randN];
  Cell::Direction new_dir;
  Point tmp_pt;

  for (auto dir : directions_)
  {
    tmp_pt = rand_pt.Direction(dir);

    if (InBounds(tmp_pt) && !marked_.IsMarked(tmp_pt))
      valid_dir.push_back(dir);
  }

  if (!valid_dir.empty())
  {
    new_dir = valid_dir[rand() % valid_dir.size()];
    open_neighbours.push_back(rand_pt.Direction(new_dir));
    return make_pair(rand_pt, new_dir);
  }

  SwapAndPop(open_neighbours, randN);

  return GetValidNeighbour(open_neighbours);
}

void GrowingTreeMaze::Generate()
{
  vector<Point> open_neighbours;

  Point cur_pt;
  Cell::Direction cur_dir;

  pair<Point, Cell::Direction> cur_pair(start_, Cell::Direction::RIGHT);
  open_neighbours.push_back(start_);

  do {
    cur_pt = cur_pair.first;
    cur_dir = cur_pair.second;

    OpenPassage(cur_pt, cur_dir);
    marked_.Mark(cur_pt.Direction(cur_dir));

    //PrintMaze();
    
    cur_pair = GetValidNeighbour(open_neighbours);

  } while (!open_neighbours.empty());
}
