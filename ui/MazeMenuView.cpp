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

#include "MazeMenuView.h"
#include "View.h"

namespace ui
{

MazeMenuView::MazeMenuView(QWidget* parent)
  : QHBoxLayout()
  , maze_menu_(new MazeComboBox(parent))
  , diff_menu_(new MazeComboBox(parent))
  , current_maze_type_(ALDOUS_BRODER)
  , current_diff_(EASY)
{
  maze_menu_->addItem(tr("Aldous Broder"));
  maze_menu_->addItem(tr("Binary Tree"));
  maze_menu_->addItem(tr("Growing Tree"));
  maze_menu_->addItem(tr("Hunt and Kill"));
  maze_menu_->addItem(tr("Prims"));
  maze_menu_->addItem(tr("Recursive Backtracker"));
  maze_menu_->addItem(tr("Side Winder"));
  maze_menu_->addItem(tr("Wilsons"));

  diff_menu_->addItem(tr("Easy"));
  diff_menu_->addItem(tr("Medium"));
  diff_menu_->addItem(tr("Hard"));
  diff_menu_->setCurrentIndex(MEDIUM);

  connect(maze_menu_.get(), SIGNAL(activated(int)), this, SLOT(MazeMenuActivated(int)));
  connect(diff_menu_.get(), SIGNAL(activated(int)), this, SLOT(DifficultyMenuActivated(int)));

  addWidget(maze_menu_.get());
  addWidget(diff_menu_.get());
}

void MazeMenuView::UpdateMazeMenuTitle()
{
  static_cast<View*>(parentWidget())->GenerateMaze();
  parentWidget()->setFocus(Qt::ActiveWindowFocusReason);
}

void MazeMenuView::UpdateDifficultyMenuTitle()
{
  int cell_size = 10;

  switch (current_diff_)
  {
    case (HARD):
      cell_size = 10;
      break;
    case (MEDIUM):
      cell_size = 20;
      break;
    case (EASY):
      cell_size = 30;
      break;
  }

  static_cast<View*>(parentWidget())->UpdateCellSize(cell_size);
}

MazeType MazeMenuView::GetMazeType() const
{
  return current_maze_type_;
}

void MazeMenuView::MazeMenuActivated(int index)
{
  current_maze_type_ = MazeType(index);
  UpdateMazeMenuTitle();
}

void MazeMenuView::DifficultyMenuActivated(int index)
{
  current_diff_ = Difficulty(index);
  UpdateDifficultyMenuTitle();
}

MazeComboBox::MazeComboBox(QWidget* parent)
  : QComboBox(parent)
{}

void MazeComboBox::hidePopup()
{
  parentWidget()->setFocus();
  QComboBox::hidePopup();
}

} // namespace ui
