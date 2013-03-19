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

#include <QtCore/qmath.h>

namespace ui
{

View::View(QWidget* parent)
  : QFrame(parent)
  , graphics_view_(std::make_shared<QGraphicsView>())
  , zoom_layout_(new QVBoxLayout)
  , zoom_slider_(new QSlider(Qt::Horizontal))
  , grid_layout_(new QGridLayout)
{
  graphics_view_->setRenderHint(QPainter::Antialiasing);

  SetupZoomLayout();
  SetupGridLayout();
  SetupSignals();

  SetupMatrix();
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
  grid_layout_->addWidget(graphics_view_.get(), 0, 0);
  grid_layout_->addLayout(zoom_layout_.get(), 1, 0);
  setLayout(grid_layout_);
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
  matrix.scale(scale,scale);

  graphics_view_->setMatrix(matrix);
}

} // namespace ui
