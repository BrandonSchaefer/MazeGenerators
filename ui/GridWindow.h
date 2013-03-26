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

#ifndef MAINWINDOW
#define MAINWINDOW

#include <QWidget>
#include <QGraphicsScene>

#include <memory>

#include "View.h"

namespace ui
{

class GridWindow : public QWidget
{
  Q_OBJECT
public:
  GridWindow(QWidget* parent = 0);

private:
  std::unique_ptr<QGraphicsScene> scene_;
  std::unique_ptr<View> view_;
};

} // namespace ui

#endif // MAINWINDOW
