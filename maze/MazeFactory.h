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

#ifndef MAZEFACTORY
#define MAZEFACTORY

#include "Maze.h"

enum MazeType 
{
  ALDOUS_BRODER,
  BINARY_TREE,
  GROWING_TREE,
  HUNT_KILL,
  PRIMS,
  RECURSIVE_BACKTRACKER,
  SIDE_WINDER,
  WILSONS
};

class MazeFactory
{
public:
  MazeFactory();

  Maze::Ptr GenerateMaze(MazeType maze_type, int width, int height);
  std::string GetMazeTitle(MazeType maze_type);

private:
  Maze::Ptr GetMazeByType(MazeType maze_type, int width, int height);

};

#endif // MAZEFACTORY
