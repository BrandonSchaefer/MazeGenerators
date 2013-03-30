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

#include <CellItem.h>
#include <gtest.h>

using namespace ui;

int const SIZE = 10;

class MockCellItem : public testing::Test
{
public:
  MockCellItem()
    : cell(SIZE)
  {}

  CellItem cell;
};


TEST_F(MockCellItem, TestCellBoundingRect)
{
  QRectF rect = cell.boundingRect();
  EXPECT_EQ(rect.x(), 0);
  EXPECT_EQ(rect.y(), 0);
  EXPECT_EQ(rect.width(), SIZE);
  EXPECT_EQ(rect.height(), SIZE);
}

TEST_F(MockCellItem, TestCellsNotMarked)
{
  EXPECT_FALSE(cell.Marked());
}

TEST_F(MockCellItem, TestCellMarking)
{
  cell.Mark();
  EXPECT_TRUE(cell.Marked());
}

TEST_F(MockCellItem, TestCellUnMarking)
{
  cell.Mark();
  EXPECT_TRUE(cell.Marked());

  cell.UnMark();
  EXPECT_FALSE(cell.Marked());
}
