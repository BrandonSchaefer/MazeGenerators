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
#include <Marked.h>

int const WIDTH = 50;
int const HEIGHT = 45;

Point const CENTER(WIDTH/2, HEIGHT/2);

class MockMarked : public testing::Test
{
public:
  MockMarked()
    : marked(WIDTH, HEIGHT)
  {}

  Marked marked;
};

TEST_F(MockMarked, TestNotMarked)
{
  EXPECT_FALSE(marked.IsMarked(CENTER));
}

TEST_F(MockMarked, TestMarking)
{
  marked.Mark(CENTER);
  EXPECT_TRUE(marked.IsMarked(CENTER));
}
