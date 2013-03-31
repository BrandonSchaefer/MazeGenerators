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

int const WIDTH = 640;
int const HEIGHT = 480;
int const CELL_SIZE = 20;

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include <Solver.h>

#include "MazeView.h"
#include "View.h"

using namespace std;

namespace ui
{

MazeView::MazeView(QWidget* parent)
  : QWidget(parent)
  , current_(Point(0,0))
  , cell_size_(CELL_SIZE)
  , solved_index_(0)
  , solved_timer_(new QTimer(parent))
{
  connect(solved_timer_, SIGNAL(timeout()), this, SLOT(updateSolvedPath()));
}

QPointF MazeView::GetCenterPointFocus() const
{
  return QPointF((current_.y() * cell_size_) + cell_size_/2, 
                 (current_.x() * cell_size_) + cell_size_/2);
}

QGraphicsScene* MazeView::GetViewsScene() const
{
  return static_cast<View*>(parentWidget())->view()->scene();
}

void MazeView::SetCellSize(int cell_size)
{
  cell_size_ = cell_size;
}

void MazeView::GenerateMaze(MazeType maze_type)
{
  QGraphicsScene* scene_ = GetViewsScene();

  if (solved_timer_->isActive())
  {
    solved_index_ = 0;
    solved_timer_->stop();
  }

  if (!scene_)
    return;

  int w_l = (WIDTH/cell_size_);
  int h_l = (HEIGHT/cell_size_);

  cell_views_ = vector<vector<CellItem::Ptr> >(h_l, vector<CellItem::Ptr>(w_l, CellItem::Ptr()));

  Maze::Ptr maze = maze_factory_.GenerateMaze(maze_type, w_l, h_l);

  Solver s;
  solved_path_ = s.DFSolve(maze);

  for (int i = 0; i < h_l; i++)
  {
    for (int j = 0; j < w_l; j++)
    {
      Point p(j+1, i+1);
      CellItem::Ptr item = make_shared<CellItem>(cell_size_);
      item->setPos(i * cell_size_, j * cell_size_);
      item->SetCell(maze->Get(p));

      cell_views_[i][j] = item;
      scene_->addItem(item.get());
    }
  }

  Point start  = maze->GetStart();
  Point finish = maze->GetFinish();

  cell_views_[start.y()-1][start.x()-1]->SetStart();
  cell_views_[start.y()-1][start.x()-1]->Mark();
  cell_views_[finish.y()-1][finish.x()-1]->SetFinish();

  current_ = Point(start.y()-1, start.x()-1);
  finish_ = Point(finish.x()-1, finish.y()-1);
}

void MazeView::MarkSolvedMaze()
{
  solved_index_ = 0;
  solved_timer_->start(25);
}

void MazeView::updateSolvedPath()
{
  if (solved_index_ >= solved_path_.size()-1)
    solved_timer_->stop();

  Point p = solved_path_[solved_index_];
  cell_views_[p.y()-1][p.x()-1]->Mark();
  cell_views_[p.y()-1][p.x()-1]->SetColor(Qt::red);
  solved_index_++;
}

bool MazeView::HandleKeyEvent(QKeyEvent* event)
{
  bool ret = false;
  CellItem::Ptr cur_cell = cell_views_[current_.y()][current_.x()];

  switch (event->key())
  {
    case(Qt::Key_W):
      if (cur_cell->GetCell().UpOpen())
      {
        current_ = current_.Up();
        ret = true;
      }
      break;
    case(Qt::Key_A):
      if (cur_cell->GetCell().LeftOpen())
      {
        current_ = current_.Left();
        ret = true;
      }
      break;
    case(Qt::Key_S):
      if (cur_cell->GetCell().DownOpen())
      {
        current_ = current_.Down();
        ret = true;
      }
      break;
    case(Qt::Key_D):
      if (cur_cell->GetCell().RightOpen())
      {
        current_ = current_.Right();
        ret = true;
      }
      break;
    default:
      break;
  }

  if (cell_views_[current_.y()][current_.x()]->Marked())
    cur_cell->UnMark();

  cur_cell->SetColor(Qt::yellow);
  cell_views_[current_.y()][current_.x()]->SetColor(Qt::green);
  cell_views_[current_.y()][current_.x()]->Mark();

  if (finish_.y() == current_.y() && finish_.x() == current_.x())
    MarkSolvedMaze();

  return ret;
}

} // namespace ui

