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

#ifndef GROWINGTREEMAZE
#define GROWINGTREEMAZE

#include "Maze.h"
#include "Marked.h"

class GrowingTreeMaze : public Maze
{
public:
  GrowingTreeMaze(int x, int y);
  void Generate();

  std::pair<Point, Cell::Direction> GetValidNeighbour(std::vector<Point>& open_neighbours);

private:
  Marked marked_;

};

#endif // GROWINGTREEMAZE
