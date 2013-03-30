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

#include "MazeMenuBar.h"
#include "View.h"

namespace ui
{

MazeMenuBar::MazeMenuBar(QWidget* parent)
  : QMenuBar(parent)
  , view_(parent)
  , maze_menu_(new QMenu("Prims"))
  , diff_menu_(new QMenu("Medium"))
  , current_maze_type_(MazeType::PRIMS)
  , current_diff_(MEDIUM)
{
  QAction* ald_brod  = new QAction(tr("&Aldous Broder"), this);
  QAction* bin_tree  = new QAction(tr("&Binary Tree"), this);
  QAction* grow_tree = new QAction(tr("&Growing Tree"), this);
  QAction* hunt_kill = new QAction(tr("&Hunt and Kill"), this);
  QAction* prims     = new QAction(tr("&Prims"), this);
  QAction* side_wind = new QAction(tr("&Side Winder"), this);
  QAction* rec_back  = new QAction(tr("&Recursive Backtracker"), this);
  QAction* wilsons   = new QAction(tr("&Wilsons"), this);

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

  QAction* easy   = new QAction(tr("&Easy"), this);
  QAction* medium = new QAction(tr("&Medium"), this);
  QAction* hard   = new QAction(tr("&Hard"), this);

  connect(easy,    SIGNAL(triggered()), this, SLOT(easy()));
  connect(medium,  SIGNAL(triggered()), this, SLOT(medium()));
  connect(hard,    SIGNAL(triggered()), this, SLOT(hard()));

  diff_menu_->addAction(easy);
  diff_menu_->addAction(medium);
  diff_menu_->addAction(hard);

  addMenu(diff_menu_.get());
  addMenu(maze_menu_.get());
}

void MazeMenuBar::UpdateMazeMenuTitle()
{
  std::string maze_title = maze_factory_.GetMazeTitle(current_maze_type_);
  maze_menu_->setTitle(tr(maze_title.c_str()));

  static_cast<View*>(view_)->GenerateMaze();
}

void MazeMenuBar::UpdateDifficultyMenuTitle()
{
  std::string diff;
  int cell_size = 10;

  switch (current_diff_)
  {
    case (HARD):
      diff = "Hard";
      cell_size = 10;
      break;
    case (MEDIUM):
      diff = "Medium";
      cell_size = 20;
      break;
    case (EASY):
      diff = "Easy";
      cell_size = 30;
      break;
  }

  diff_menu_->setTitle(tr(diff.c_str()));

  static_cast<View*>(view_)->UpdateCellSize(cell_size);
}

MazeType MazeMenuBar::GetMazeType() const
{
  return current_maze_type_;
}

void MazeMenuBar::aldBrod()
{
  current_maze_type_ = ALDOUS_BRODER;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::binTree()
{
  current_maze_type_ = BINARY_TREE;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::growTree()
{
  current_maze_type_ = GROWING_TREE;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::huntKill()
{
  current_maze_type_ = HUNT_KILL;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::prims()
{
  current_maze_type_ = PRIMS;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::sideWind()
{
  current_maze_type_ = SIDE_WINDER;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::recBack()
{
  current_maze_type_ = RECURSIVE_BACKTRACKER;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::wilsons()
{
  current_maze_type_ = WILSONS;
  UpdateMazeMenuTitle();
}

void MazeMenuBar::hard()
{
  current_diff_ = HARD;
  UpdateDifficultyMenuTitle();
}

void MazeMenuBar::medium()
{
  current_diff_ = MEDIUM;
  UpdateDifficultyMenuTitle();
}

void MazeMenuBar::easy()
{
  current_diff_ = EASY;
  UpdateDifficultyMenuTitle();
}


} // namespace ui
