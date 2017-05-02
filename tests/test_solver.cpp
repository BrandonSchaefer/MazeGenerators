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

#include <MazeFactory.h>
#include <Solver.h>
#include <gtest/gtest.h>

int const WIDTH = 20;
int const HEIGTH = 30;

class MockSolver : public testing::Test
{
public:
  MockSolver()
  {
    maze = maze_factory.GenerateMaze(BINARY_TREE, WIDTH, HEIGTH);
  }

  Maze::Ptr maze;
  MazeFactory maze_factory;
  Solver solver;
};

TEST_F(MockSolver, TestDFSolver)
{
  EXPECT_FALSE(solver.DFSolve(maze).empty());
}

TEST_F(MockSolver, TestBFSolver)
{
  EXPECT_FALSE(solver.BFSolve(maze).empty());
}
