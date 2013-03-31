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

#include "MazeGraphicsView.h"
#include "View.h"

#include <QtCore/qmath.h>

#include <QWheelEvent>

namespace ui
{

int const MIN_ZOOM = 0;
int const MAX_ZOOM = 200;
int const ZOOM = 10;

MazeGraphicsView::MazeGraphicsView(QWidget* parent)
  : QGraphicsView(parent)
  , zoom_value_(MIN_ZOOM)
{
  setRenderHint(QPainter::Antialiasing);
  setDragMode(QGraphicsView::ScrollHandDrag);

  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  SetupMatrix();
}

void MazeGraphicsView::SetupMatrix()
{
  qreal scale = qPow(qreal(2), zoom_value_ / qreal(50));

  QMatrix matrix;
  matrix.scale(scale, scale);

  centerOn(static_cast<View*>(parentWidget())->GetCenterPointFocus());
  setMatrix(matrix);
}

void MazeGraphicsView::wheelEvent(QWheelEvent* event)
{
  if (event->delta() > 0)
    ZoomIn();
  else
    ZoomOut();

  SetupMatrix();
}

void MazeGraphicsView::ZoomIn()
{
  if (zoom_value_ < MAX_ZOOM)
    zoom_value_ += ZOOM;
}

void MazeGraphicsView::ZoomOut()
{
  if (zoom_value_ > MIN_ZOOM)
    zoom_value_ -= ZOOM;
}

} // namespace ui
