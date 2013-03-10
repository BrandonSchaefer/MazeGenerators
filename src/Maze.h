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

#ifndef MAZE
#define MAZE

#include "Cell.h"
#include "Point.h"

#include <vector>

class Maze
{
public:
  Maze (int x, int y);

  Cell& Get(Point pos);

  int Columns() const;
  int Rows() const;

  void OpenPassage(Point p, Cell::Direction dir);

  void SetStart(Point start);
  void SetFinish(Point finish);
  bool IsStart(Point& p) const;
  bool IsFinish(Point& p) const;
  Point GetStart();
  Point GetFinish();

  bool RightOpen(Point point);
  bool DownOpen(Point point);
  bool LeftOpen(Point point);
  bool UpOpen(Point point);

  bool InBounds(Point pos) const;

  void PrintMaze();

  std::vector<Cell::Direction> GetDirections();

  Cell::Direction GetValidRandomDirection(Point& current);
  Cell::Direction OppositeDirection(Cell::Direction dir);

  virtual void Generate() = 0;

protected:
  std::vector<std::vector<Cell> > maze_;
  std::vector<Cell::Direction> directions_;

  Point start_;
  Point finish_;
};

Cell::Direction OppositeDirection(Cell::Direction dir);

#endif // MAZE
