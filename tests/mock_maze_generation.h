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

#include <gtest.h>
#include <MazeFactory.h>
#include <Solver.h>

int const WIDTH = 10;
int const HEIGHT = 11;

class MockMazeGeneration : public testing::Test
{
public:
  MockMazeGeneration()
  {}

  bool SolveAllPoints()
  {
    for (int i = 1; i <= maze->Columns()-2; i++)
    {
      for (int j = 1; j <= maze->Rows()-2; j++)
      {
        maze->SetStart(Point(i,j));

        if (solver.DFSolve(maze).empty())
          return false;
      }
    }

    return true;
  }

  Maze::Ptr maze;
  MazeFactory maze_factory;
  Solver solver;
};
