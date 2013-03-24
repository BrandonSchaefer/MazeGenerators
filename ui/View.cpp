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

namespace ui
{

View::View(QWidget* parent)
  : QFrame(parent)
  , parent_(parent)
  , graphics_view_(std::make_shared<QGraphicsView>())
  , zoom_layout_(new QVBoxLayout)
  , zoom_slider_(new QSlider(Qt::Horizontal))
  , menu_bar_(new QMenuBar)
  , grid_layout_(new QGridLayout)
  , maze_menu_(new QMenu("MazeType - Prims"))
  , current_maze_type_(MazeType::PRIMS)
{
  graphics_view_->setRenderHint(QPainter::Antialiasing);

  SetupMenuBar();
  SetupZoomLayout();
  SetupGridLayout();
  SetupSignals();

  SetupMatrix();
}

void View::SetupMenuBar()
{
  // TODO Make my own QMenuBar class
  QAction* ald_brod  = new QAction(tr("&Aldous Broder"), menu_bar_.get());
  QAction* bin_tree  = new QAction(tr("&Binary Tree"), menu_bar_.get());
  QAction* grow_tree = new QAction(tr("&Growing Tree"), menu_bar_.get());
  QAction* hunt_kill = new QAction(tr("&Hunt and Kill"), menu_bar_.get());
  QAction* prims     = new QAction(tr("&Prims"), menu_bar_.get());
  QAction* side_wind = new QAction(tr("&Side Winder"), menu_bar_.get());
  QAction* rec_back  = new QAction(tr("&Recursive Backtracker"), menu_bar_.get());
  QAction* wilsons   = new QAction(tr("&Wilsons"), menu_bar_.get());

  connect(ald_brod,  SIGNAL(triggered()), this, SLOT(aldBrod()));
  connect(bin_tree,  SIGNAL(triggered()), this, SLOT(binTree()));
  connect(grow_tree, SIGNAL(triggered()), this, SLOT(growTree()));
  connect(hunt_kill, SIGNAL(triggered()), this, SLOT(huntKill()));
  connect(prims,     SIGNAL(triggered()), this, SLOT(prims()));
  connect(side_wind, SIGNAL(triggered()), this, SLOT(sideWind()));
  connect(rec_back,  SIGNAL(triggered()), this, SLOT(recBack()));
  connect(wilsons,   SIGNAL(triggered()), this, SLOT(wilsons()));

  maze_menu_->addAction(ald_brod);
  maze_menu_->addAction(bin_tree);
  maze_menu_->addAction(grow_tree);
  maze_menu_->addAction(hunt_kill);
  maze_menu_->addAction(prims);
  maze_menu_->addAction(side_wind);
  maze_menu_->addAction(rec_back);
  maze_menu_->addAction(wilsons);

  menu_bar_->addMenu(maze_menu_);
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

Maze::Ptr View::GetGeneratedMaze(int width, int height)
{
  return maze_factory_.GenerateMaze(current_maze_type_, width, height);
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

  graphics_view_->setMatrix(matrix);
}

void View::UpdateMazeMenuTitle()
{
  std::string maze_title = "Maze Type - " + maze_factory_.GetMazeTitle(current_maze_type_);
  maze_menu_->setTitle(tr(maze_title.c_str()));

  static_cast<GridWindow*>(parent_)->GenerateMaze();
}

void View::aldBrod()
{
  current_maze_type_ = ALDOUS_BRODER;
  UpdateMazeMenuTitle();
}

void View::binTree()
{
  current_maze_type_ = BINARY_TREE;
  UpdateMazeMenuTitle();
}

void View::growTree()
{
  current_maze_type_ = GROWING_TREE;
  UpdateMazeMenuTitle();
}

void View::huntKill()
{
  current_maze_type_ = HUNT_KILL;
  UpdateMazeMenuTitle();
}

void View::prims()
{
  current_maze_type_ = PRIMS;
  UpdateMazeMenuTitle();
}

void View::sideWind()
{
  current_maze_type_ = SIDE_WINDER;
  UpdateMazeMenuTitle();
}

void View::recBack()
{
  current_maze_type_ = RECURSIVE_BACKTRACKER;
  UpdateMazeMenuTitle();
}

void View::wilsons()
{
  current_maze_type_ = WILSONS;
  UpdateMazeMenuTitle();
}

} // namespace ui
