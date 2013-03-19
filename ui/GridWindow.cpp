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
#include <QKeyEvent>

#include "GridWindow.h"

#include "PrimsMaze.h"
#include "Solver.h"

int const WIDTH = 640;
int const HEIGHT = 480;
int const CELL_SIZE = 15;

using namespace std;

namespace ui
{

GridWindow::GridWindow(QWidget* parent)
  : QWidget(parent)
  , scene_(new QGraphicsScene(this))
  , view_(new View(this))
{
  view_->view()->setScene(scene_.get());

  GenerateMaze();

  view_->show();
  setWindowTitle(tr("MazeGenerator"));
}

void GridWindow::GenerateMaze()
{
  int w_l = (WIDTH/CELL_SIZE);
  int h_l = (HEIGHT/CELL_SIZE);

  cell_views_ = vector<vector<CellItem::Ptr> >(h_l, vector<CellItem::Ptr>(w_l, CellItem::Ptr()));
  view_->view()->centerOn(QPointF(0,0));

  PrimsMaze rmaze(w_l, h_l);
  rmaze.Generate();

  Solver s;
  solved_path_ = s.DFSolve(rmaze);

  for (int i = 0; i < h_l; i++)
  {
    for (int j = 0; j < w_l; j++)
    {
      Point p(j+1, i+1);
      CellItem::Ptr item = make_shared<CellItem>(CELL_SIZE);
      item->setPos(i * CELL_SIZE, j * CELL_SIZE);
      item->SetCell(rmaze.Get(p));

      cell_views_[i][j] = item;
      scene_->addItem(item.get());
    }
  }

  Point start = rmaze.GetStart();
  Point finish = rmaze.GetFinish();

  cell_views_[start.y()-1][start.x()-1]->SetStart();
  cell_views_[start.y()-1][start.x()-1]->Mark();
  cell_views_[finish.y()-1][finish.x()-1]->SetFinish();

  current_ = Point(start.y()-1, start.x()-1);
  finish_ = Point(finish.x()-1, finish.y()-1);
}

void GridWindow::PrintSolution()
{
  for (auto p : solved_path_)
  {
    cell_views_[p.y()-1][p.x()-1]->Mark();
    cell_views_[p.y()-1][p.x()-1]->update();
  }
}

void GridWindow::keyPressEvent(QKeyEvent* event)
{
  CellItem::Ptr cur_cell = cell_views_[current_.y()][current_.x()];

  switch (event->key())
  {
    case(Qt::Key_W):
      if (cur_cell->GetCell().UpOpen())
        current_ = current_.Up();
      break;
    case(Qt::Key_A):
      if (cur_cell->GetCell().LeftOpen())
        current_ = current_.Left();
      break;
    case(Qt::Key_S):
      if (cur_cell->GetCell().DownOpen())
        current_ = current_.Down();
      break;
    case(Qt::Key_D):
      if (cur_cell->GetCell().RightOpen())
        current_ = current_.Right();
      break;
    case(Qt::Key_Z):
      GenerateMaze();
      break;
    case(Qt::Key_V):
      PrintSolution();
      break;
    default:
      break;
  }

  view_->view()->centerOn(QPointF(current_.y()*CELL_SIZE, current_.x()*CELL_SIZE));
  cur_cell->SetColor(Qt::yellow);

  if (cell_views_[current_.y()][current_.x()]->Marked())
  {
    cur_cell->SetColor(Qt::green);
    cur_cell->UnMark();
  }

  cell_views_[current_.y()][current_.x()]->Mark();

  if (finish_.y() == current_.y() && finish_.x() == current_.x())
    GenerateMaze();
}

} // namespace ui
