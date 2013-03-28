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

int const WIDTH = 10;
int const HEIGHT = 10;

class MockMazeFactory : public testing::Test
{
public:
  MockMazeFactory()
  {}

  MazeFactory maze_factory;
};

TEST_F(MockMazeFactory, TestGenerateAldousBroder)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(ALDOUS_BRODER, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(ALDOUS_BRODER), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateBinaryTree)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(BINARY_TREE, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(BINARY_TREE), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateGrowingTree)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(GROWING_TREE, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(GROWING_TREE), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateHuntKill)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(HUNT_KILL, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(HUNT_KILL), maze->GetName());
}

TEST_F(MockMazeFactory, TestGeneratePrims)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(PRIMS, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(PRIMS), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateRecrsiveBacktracker)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(RECURSIVE_BACKTRACKER, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(RECURSIVE_BACKTRACKER), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateSideWinder)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(SIDE_WINDER, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(SIDE_WINDER), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateWilsons)
{
  Maze::Ptr maze = maze_factory.GenerateMaze(WILSONS, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(WILSONS), maze->GetName());
}
