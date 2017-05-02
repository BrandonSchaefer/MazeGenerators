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

#include <Point.h>
#include <gtest/gtest.h>

int const X = 5;
int const Y = 4;

class MockPoint : public testing::Test
{
public:
  MockPoint()
    : point(X, Y)
  {}

  Point point;
};

TEST_F(MockPoint, TestInit)
{
  Point p;

  EXPECT_EQ(p.x(), 0);
  EXPECT_EQ(p.y(), 0);
}

TEST_F(MockPoint, TestInitValue)
{
  EXPECT_EQ(point.x(), X);
  EXPECT_EQ(point.y(), Y);
}

TEST_F(MockPoint, TestCopy)
{
  Point p = point;

  EXPECT_EQ(p.x(), X);
  EXPECT_EQ(p.y(), Y);
}

TEST_F(MockPoint, TestDirectionRight)
{
  Point right = point.Direction(Cell::Direction::RIGHT);

  EXPECT_EQ(right.x(), X);
  EXPECT_EQ(right.y(), Y + 1);
}

TEST_F(MockPoint, TestRight)
{
  Point right = point.Right();

  EXPECT_EQ(right.x(), X);
  EXPECT_EQ(right.y(), Y + 1);
}

TEST_F(MockPoint, TestDirectionLeft)
{
  Point left = point.Direction(Cell::Direction::LEFT);

  EXPECT_EQ(left.x(), X);
  EXPECT_EQ(left.y(), Y - 1);
}

TEST_F(MockPoint, TestLeft)
{
  Point left = point.Left();

  EXPECT_EQ(left.x(), X);
  EXPECT_EQ(left.y(), Y - 1);
}

TEST_F(MockPoint, TestDirectionDown)
{
  Point down = point.Direction(Cell::Direction::DOWN);

  EXPECT_EQ(down.x(), X + 1);
  EXPECT_EQ(down.y(), Y);
}

TEST_F(MockPoint, TestDown)
{
  Point down = point.Down();

  EXPECT_EQ(down.x(), X + 1);
  EXPECT_EQ(down.y(), Y);
}

TEST_F(MockPoint, TestDirectionUp)
{
  Point up = point.Direction(Cell::Direction::UP);

  EXPECT_EQ(up.x(), X - 1);
  EXPECT_EQ(up.y(), Y);
}

TEST_F(MockPoint, TestUp)
{
  Point up = point.Up();

  EXPECT_EQ(up.x(), X - 1);
  EXPECT_EQ(up.y(), Y);
}

TEST_F(MockPoint, TestEqualityOperator)
{
  Point p = point;

  EXPECT_TRUE(p == point);
}
