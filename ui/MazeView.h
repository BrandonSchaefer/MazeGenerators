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

#ifndef MAZEVIEW
#define MAZEVIEW

#include "CellItem.h"

#include <Point.h>
#include <MazeFactory.h>

#include <vector>

namespace ui
{

class MazeView
{
public:
  MazeView(QWidget* parent = 0);

  void GenerateMaze(MazeType maze);
  void SetCellSize(int cell_size);
  void MarkSolvedMaze();

  bool HandleKeyEvent(QKeyEvent* event);
  QPointF GetCenterPointFocus() const;

private:
  QGraphicsScene* GetViewsScene() const;

  QWidget* view_;
  Point current_;
  Point finish_;
  int cell_size_;

  std::vector<std::vector<CellItem::Ptr> > cell_views_;
  std::vector<Point> solved_path_;

  MazeFactory maze_factory_;
};

} // namespace ui

#endif // MAZEVIEW
