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
#include <QMenuBar>
#include <QSlider>

#include "Maze.h"
#include "MazeFactory.h"

#include <memory>

namespace ui
{

class View : public QFrame
{
  Q_OBJECT
public:
  typedef std::shared_ptr<QGraphicsView> Ptr;

  View(QWidget* parent = 0);

  Maze::Ptr GetGeneratedMaze(int width, int height);

  View::Ptr view() const;

private slots:
  void SetupMatrix();

  void aldBrod();
  void binTree();
  void growTree();
  void huntKill();
  void prims();
  void sideWind();
  void recBack();
  void wilsons();

private:
  void SetupMenuBar();
  void SetupZoomLayout();
  void SetupGridLayout();
  void SetupSignals();

  void UpdateMazeMenuTitle();

  QWidget* parent_;

  std::shared_ptr<QGraphicsView> graphics_view_;

  std::unique_ptr<QVBoxLayout> zoom_layout_;
  std::unique_ptr<QSlider> zoom_slider_;
  std::unique_ptr<QMenuBar> menu_bar_;

  QGridLayout* grid_layout_;
  QMenu* maze_menu_;

  MazeFactory maze_factory_;
  MazeType current_maze_type_;
};

} // namespace ui

#endif // VIEW
