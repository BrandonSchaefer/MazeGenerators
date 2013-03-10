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
* Authored by: Brandon Schaefer <brandon.schaefer@canonical.com>
*/

#include "Maze.h"

#include <iostream>

using namespace std;

Maze::Maze (int x, int y)
  : start_(1, 1)
  , finish_(x, y)
{
  maze_  = vector<vector<Cell> >(x + 2, vector<Cell>(y + 2, Cell()));
  directions_ = {Cell::Direction::RIGHT, Cell::Direction::DOWN, Cell::Direction::LEFT, Cell::Direction::UP};
}

bool Maze::InBounds(Point pos) const
{
  int x = pos.x();
  int y = pos.y();

  if (x > 0 && y > 0 && x < (int)maze_.size() - 1 && y < (int)maze_[0].size() - 1)
    return true;

  return false;
}

Cell& Maze::Get(Point pos)
{
  return maze_[pos.x()][pos.y()];
}

int Maze::Columns() const
{
  return maze_.size();
}

int Maze::Rows() const
{
  return maze_[0].size();
}

void Maze::OpenPassage(Point p, Cell::Direction dir)
{
  Get(p).AddDirection(dir);
  Get(p.Direction(dir)).AddDirection(OppositeDirection(dir));
}

void Maze::SetStart(Point start)
{
  start_ = start;
}

void Maze::SetFinish(Point finish)
{
  finish_ = finish;
}

bool Maze::IsStart(Point& p) const
{
  return p == start_;
}

bool Maze::IsFinish(Point& p) const
{
  return p == finish_;
}

Point Maze::GetStart()
{
  return start_;
}

Point Maze::GetFinish()
{
  return finish_;
}

bool Maze::RightOpen(Point point)
{
  return (InBounds(point) && Get(point).RightOpen());
}

bool Maze::DownOpen(Point point)
{
  return (InBounds(point) && Get(point).DownOpen());
}

bool Maze::LeftOpen(Point point)
{
  return (InBounds(point) && Get(point).LeftOpen());
}

bool Maze::UpOpen(Point point)
{
  return (InBounds(point) && Get(point).UpOpen());
}

std::vector<Cell::Direction> Maze::GetDirections()
{
  return directions_;
}

Cell::Direction Maze::GetValidRandomDirection(Point& current)
{
  vector<Cell::Direction> valid_dirs;
  Point random_dir;
  Point tmp_pt;
  int randN;

  for (auto dir : directions_)
  {
    tmp_pt = current.Direction(dir);

    if (InBounds(tmp_pt))
      valid_dirs.push_back(dir);
  }

  randN = rand() % (valid_dirs.size());

  return valid_dirs[randN];
}

Cell::Direction Maze::OppositeDirection(Cell::Direction dir)
{
  switch (dir)
  {
    case (Cell::Direction::RIGHT):
      return Cell::Direction::LEFT;
    case (Cell::Direction::LEFT):
      return Cell::Direction::RIGHT;
    case (Cell::Direction::DOWN):
      return Cell::Direction::UP;
    case (Cell::Direction::UP):
      return Cell::Direction::DOWN;
  }

  return Cell::Direction::RIGHT;
}

void Maze::PrintMaze()
{
  cout << "\e[H";

  for (int i = 0; i < Rows(); i++)
    cout << " _";
  cout << endl;

  for (int i = 0; i < Columns(); i++)
  {
    cout << "|";
    for (int j = 0; j < Rows(); j++)
    {
      Point p(i,j);

      if (IsStart(p))
        cout << "\033[4;34mS\033[0m";
      else if (IsFinish(p))
        cout << "\033[4;31mF\033[0m";
      else if (Get(p).DownOpen() && Get(p.Down()).UpOpen())
        if (Get(p).path)
          cout << "\033[0;31m*\033[0m";
        else
          cout << " ";
      else
      {
        if (Get(p).path)
          cout << "\033[4;31m*\033[0m";
        else
            cout << "_";
      }

      if (Get(p).RightOpen() && Get(p.Right()).LeftOpen())
        cout << " ";
      else
        cout << "|";
    }
    cout << endl;
  }
}
