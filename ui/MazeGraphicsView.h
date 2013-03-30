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

#ifndef MAZEGRAPHICSVIEW
#define MAZEGRAPHICSVIEW

#include <QGraphicsView>

namespace ui
{

class MazeGraphicsView : public QGraphicsView
{
public:
  MazeGraphicsView(QWidget* parent = 0);

  void SetupMatrix();

protected:
  void wheelEvent(QWheelEvent* event);

private:
  void ZoomIn();
  void ZoomOut();

  QWidget* view_;
  int zoom_value_;

};

} // namespace ui

#endif // MAZEGRAPHICSVIEW
