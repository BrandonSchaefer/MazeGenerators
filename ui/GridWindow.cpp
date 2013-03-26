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

#include <vector>

#include "GridWindow.h"

namespace ui
{

GridWindow::GridWindow(QWidget* parent)
  : QWidget(parent)
  , scene_(new QGraphicsScene(this))
  , view_(new View(this))
{
  view_->SetScene(scene_.get());

  view_->show();
  setWindowTitle(tr("MazeGenerator"));
}

} // namespace ui
