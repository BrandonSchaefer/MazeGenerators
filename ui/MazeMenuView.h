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

#include <QComboBox>
#include <QHBoxLayout>
#include <QWidget>

#include "MazeFactory.h"

#ifndef MAZEMENUBAR
#define MAZEMENUBAR

namespace ui
{

enum Difficulty
{
  EASY,
  MEDIUM,
  HARD
};

class MazeComboBox : public QComboBox
{
public:
  MazeComboBox(QWidget* parent = 0);

  void hidePopup();
};

class MazeMenuView : public QHBoxLayout
{
  Q_OBJECT
public:
  MazeMenuView(QWidget* parent = 0);

  MazeType GetMazeType() const;

private slots:
  void MazeMenuActivated(int index);
  void DifficultyMenuActivated(int index);

private:
  void UpdateMazeMenuTitle();
  void UpdateDifficultyMenuTitle();

  std::unique_ptr<MazeComboBox> maze_menu_;
  std::unique_ptr<MazeComboBox> diff_menu_;

  MazeFactory maze_factory_;
  MazeType current_maze_type_;
  Difficulty current_diff_;
};

} // namespace ui

#endif // MAZEMENUBAR
