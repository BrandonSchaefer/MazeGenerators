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

#include <gtest/gtest.h>
#include <Maze.h>

#include <BinaryTreeMaze.h>

int const WIDTH = 50;
int const HEIGHT = 45;
int const WALL_BOUNDARY = 2;

Point const START = {2,2};
Point const FINISH = {5,5};
Point const ON_TOP_WALL_BOUNDARY = {0,1};

class FakeMaze : public Maze
{
public:
  FakeMaze(int x, int y)
    : Maze(x,y)
  {
    start_ = START; 
    finish_ = FINISH; 
  }

  void Generate()
  {}

  std::string GetName() const
  {
    return "FakeMaze";
  }
};

class MockMaze : public testing::Test
{
public:
  MockMaze()
    : maze(WIDTH, HEIGHT)
    , center(WIDTH/2, HEIGHT/2)
  {}

  FakeMaze maze;
  Point center;
};


TEST_F(MockMaze, TestColumsAndRows)
{
  EXPECT_EQ(maze.Columns(), WIDTH + WALL_BOUNDARY);
  EXPECT_EQ(maze.Rows(), HEIGHT + WALL_BOUNDARY);
}

TEST_F(MockMaze, TestGettingCell)
{
  EXPECT_TRUE(maze.Get(center).Empty());
}

TEST_F(MockMaze, TestOpeningPassageRight)
{
  maze.OpenPassage(center, Cell::Direction::RIGHT);

  EXPECT_TRUE(maze.RightOpen(center));
}

TEST_F(MockMaze, TestOpeningPassageLeft)
{
  maze.OpenPassage(center, Cell::Direction::LEFT);

  EXPECT_TRUE(maze.LeftOpen(center));
}

TEST_F(MockMaze, TestOpeningPassageDown)
{
  maze.OpenPassage(center, Cell::Direction::DOWN);

  EXPECT_TRUE(maze.DownOpen(center));
}

TEST_F(MockMaze, TestOpeningPassageUp)
{
  maze.OpenPassage(center, Cell::Direction::UP);

  EXPECT_TRUE(maze.UpOpen(center));
}

TEST_F(MockMaze, TestCantOpenOutofBoundsPassage)
{
  Point out_bounds(1,1);
  maze.OpenPassage(out_bounds, Cell::Direction::UP);

  EXPECT_FALSE(maze.UpOpen(center));
}

TEST_F(MockMaze, TestSettingWallRight)
{
  maze.OpenPassage(center, Cell::Direction::RIGHT);
  EXPECT_TRUE(maze.RightOpen(center));

  maze.SetWall(center, Cell::Direction::RIGHT);
  EXPECT_FALSE(maze.RightOpen(center));
}

TEST_F(MockMaze, TestSettingWallLeft)
{
  maze.OpenPassage(center, Cell::Direction::LEFT);
  EXPECT_TRUE(maze.LeftOpen(center));

  maze.SetWall(center, Cell::Direction::LEFT);
  EXPECT_FALSE(maze.LeftOpen(center));
}

TEST_F(MockMaze, TestSettingWallDown)
{
  maze.OpenPassage(center, Cell::Direction::DOWN);
  EXPECT_TRUE(maze.DownOpen(center));

  maze.SetWall(center, Cell::Direction::DOWN);
  EXPECT_FALSE(maze.DownOpen(center));
}

TEST_F(MockMaze, TestSettingWallUp)
{
  maze.OpenPassage(center, Cell::Direction::UP);
  EXPECT_TRUE(maze.UpOpen(center));

  maze.SetWall(center, Cell::Direction::UP);
  EXPECT_FALSE(maze.UpOpen(center));
}

TEST_F(MockMaze, TestGetStart)
{
  EXPECT_TRUE(maze.GetStart() == START);
}

TEST_F(MockMaze, TestGetFinish)
{
  EXPECT_TRUE(maze.GetFinish() == FINISH);
}

TEST_F(MockMaze, TestInBounds)
{
  EXPECT_TRUE(maze.InBounds(center));
}

TEST_F(MockMaze, TestOutOfBounds)
{
  EXPECT_FALSE(maze.InBounds({-1,-1}));
}

TEST_F(MockMaze, TestGetDirections)
{
  std::vector<Cell::Direction> directions = maze.GetDirections();

  for (auto dir : directions)
    EXPECT_FALSE(center == center.Direction(dir));

  EXPECT_FALSE(directions.empty());
}

TEST_F(MockMaze, TestGetValidRandomDirection)
{
  // Puts us in a place where there is only 1 know valid direction
  Point p(ON_TOP_WALL_BOUNDARY);

  EXPECT_EQ(maze.GetValidRandomDirection(p), Cell::Direction::DOWN);
}

TEST_F(MockMaze, TestOppositeDirectionRight)
{
  EXPECT_EQ(maze.OppositeDirection(Cell::Direction::RIGHT), Cell::Direction::LEFT);
}

TEST_F(MockMaze, TestOppositeDirectionLeft)
{
  EXPECT_EQ(maze.OppositeDirection(Cell::Direction::LEFT), Cell::Direction::RIGHT);
}

TEST_F(MockMaze, TestOppositeDirectionDown)
{
  EXPECT_EQ(maze.OppositeDirection(Cell::Direction::DOWN), Cell::Direction::UP);
}

TEST_F(MockMaze, TestOppositeDirectionUp)
{
  EXPECT_EQ(maze.OppositeDirection(Cell::Direction::UP), Cell::Direction::DOWN);
}
