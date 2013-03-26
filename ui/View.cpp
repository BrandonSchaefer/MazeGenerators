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

#include <QtCore/qmath.h>
#include <QAction>
#include <QKeyEvent>

namespace ui
{

View::View(QWidget* parent)
  : QFrame(parent)
  , grid_window_(parent)
  , graphics_view_(std::make_shared<QGraphicsView>())
  , zoom_layout_(new QVBoxLayout)
  , zoom_slider_(new QSlider(Qt::Horizontal))
  , menu_bar_(new MazeMenuBar(this))
  , maze_view_(new MazeView(this))
  , grid_layout_(new QGridLayout)
{
  graphics_view_->setRenderHint(QPainter::Antialiasing);

  SetupZoomLayout();
  SetupGridLayout();
  SetupSignals();

  SetupMatrix();

  GenerateMaze();
}

void View::SetupZoomLayout()
{  
  zoom_layout_->addWidget(zoom_slider_.get());

  zoom_slider_->setMinimum(250);
  zoom_slider_->setMaximum(500);
  zoom_slider_->setValue(250);
  zoom_slider_->setTickPosition(QSlider::TicksRight);
}

void View::SetupGridLayout()
{
  grid_layout_->addWidget(menu_bar_.get(), 0, 0);
  grid_layout_->addWidget(graphics_view_.get(), 1, 0);
  grid_layout_->addLayout(zoom_layout_.get(), 2, 0);
  setLayout(grid_layout_);
}

void View::SetScene(QGraphicsScene* scene)
{
  graphics_view_->setScene(scene);
  GenerateMaze();
}

void View::SetupSignals()
{
  connect(zoom_slider_.get(), SIGNAL(valueChanged(int)), this, SLOT(SetupMatrix()));
}

View::Ptr View::view() const
{
  return graphics_view_;
}

void View::SetupMatrix()
{
  qreal scale = qPow(qreal(2), (zoom_slider_->value() - 250) / qreal(50));

  QMatrix matrix;
  matrix.scale(scale, scale);

  graphics_view_->centerOn(maze_view_->GetCenterPointFocus());
  graphics_view_->setMatrix(matrix);
}

void View::GenerateMaze()
{
  maze_view_->GenerateMaze(menu_bar_->GetMazeType());
  SetupMatrix();
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

void View::wheelEvent(QWheelEvent* event)
{
  if (event->delta() > 0)
    zoom_slider_->setValue(zoom_slider_->value() + 10);
  else
    zoom_slider_->setValue(zoom_slider_->value() - 10);

  SetupMatrix();
}

} // namespace ui
