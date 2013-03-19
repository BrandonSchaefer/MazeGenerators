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

#ifndef VIEW
#define VIEW

#include <QFrame>
#include <QGraphicsView>
#include <QGridLayout>
#include <QSlider>

#include <memory>

namespace ui
{

class View : public QFrame
{
  Q_OBJECT
public:
  typedef std::shared_ptr<QGraphicsView> Ptr;

  View(QWidget* parent = 0);

  View::Ptr view() const;

private slots:
  void SetupMatrix();

private:
  void SetupZoomLayout();
  void SetupGridLayout();
  void SetupSignals();

  std::shared_ptr<QGraphicsView> graphics_view_;

  std::unique_ptr<QVBoxLayout> zoom_layout_;
  std::unique_ptr<QSlider> zoom_slider_;

  // setLayout() takes ownership of this pointer
  QGridLayout* grid_layout_;
};

} // namespace ui

#endif // VIEW
