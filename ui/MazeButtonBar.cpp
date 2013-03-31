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

#include "MazeButtonBar.h"
#include "View.h"

namespace ui
{

MazeButtonBar::MazeButtonBar(QWidget* parent)
  : QHBoxLayout()
  , generate_button_(new QPushButton("Generate", parent))
  , solve_button_(new QPushButton("Solve", parent))
{
  connect(generate_button_.get(), SIGNAL(clicked()), this, SLOT(GenerateClicked()));
  connect(solve_button_.get(), SIGNAL(clicked()), this, SLOT(SolveClicked()));

  addWidget(generate_button_.get());
  addWidget(solve_button_.get());
}

void MazeButtonBar::GenerateClicked()
{
  static_cast<View*>(parentWidget())->GenerateMaze();
}

void MazeButtonBar::SolveClicked()
{
  static_cast<View*>(parentWidget())->SolvedMaze();
}

} // namespace ui
