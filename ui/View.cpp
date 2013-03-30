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

#include "View.h"
#include "GridWindow.h"

#include <QAction>
#include <QKeyEvent>

namespace ui
{

View::View(QWidget* parent)
  : QFrame(parent)
  , grid_window_(parent)
  , maze_view_(new MazeView(this))
  , menu_bar_(new MazeMenuBar(this))
  , graphics_view_(std::make_shared<MazeGraphicsView>(this))
  , grid_layout_(new QGridLayout)
{
  SetupGridLayout();
  GenerateMaze();
}

void View::SetupGridLayout()
{
  grid_layout_->addWidget(menu_bar_.get(), 0, 0);
  grid_layout_->addWidget(graphics_view_.get(), 1, 0);
  setLayout(grid_layout_);
}

void View::SetScene(QGraphicsScene* scene)
{
  graphics_view_->setScene(scene);
  GenerateMaze();
}

QPointF View::GetCenterPointFocus() const
{
  return maze_view_->GetCenterPointFocus();
}

View::Ptr View::view() const
{
  return graphics_view_;
}

void View::GenerateMaze()
{
  maze_view_->GenerateMaze(menu_bar_->GetMazeType());
  graphics_view_->SetupMatrix();
}

void View::UpdateCellSize(int cell_size)
{
  maze_view_->SetCellSize(cell_size);
  GenerateMaze();
}

void View::keyPressEvent(QKeyEvent* event)
{
  switch (event->key())
  {
    case(Qt::Key_Z):
      GenerateMaze();
      break;
    case(Qt::Key_V):
      maze_view_->MarkSolvedMaze();
      break;
    default:
      break;
  }

  if (maze_view_->HandleKeyEvent(event))
    graphics_view_->centerOn(maze_view_->GetCenterPointFocus());
}

} // namespace ui
