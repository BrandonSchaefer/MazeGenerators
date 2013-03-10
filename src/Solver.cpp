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

#include "Solver.h"

#include <queue>

#include <iostream>

using namespace std;

Solver::Solver()
{
}

vector<Point> Solver::DFSolve(Maze& maze)
{
  vector<Point> path;
  Point current = maze.GetStart();

  vector<vector<bool> > marked(maze.Columns(), vector<bool>(maze.Rows(), false));

  path.push_back(current);
  marked[current.x()][current.y()] = true;

  while (!path.empty())
  {
    current = path.back();

    if (maze.IsFinish(current))
      return path;

    if (maze.RightOpen(current) && !marked[current.Right().x()][current.Right().y()])
    {
      // Add?
      path.push_back(current.Right());
      marked[current.Right().x()][current.Right().y()] = true;
    }
    else if (maze.DownOpen(current) && !marked[current.Down().x()][current.Down().y()])
    {
      path.push_back(current.Down());
      marked[current.Down().x()][current.Down().y()] = true;
    }
    else if (maze.LeftOpen(current) && !marked[current.Left().x()][current.Left().y()])
    {
      path.push_back(current.Left());
      marked[current.Left().x()][current.Left().y()] = true;
    }
    else if (maze.UpOpen(current) && !marked[current.Up().x()][current.Up().y()])
    {
      path.push_back(current.Up());
      marked[current.Up().x()][current.Up().y()] = true;
    }
    else
    {
      path.pop_back();
    }
  }

  return path;
}

vector<Point> Solver::BFSolve(Maze& maze)
{
  queue<vector<Point> > paths;
  Point current = maze.GetStart();
  vector<Point> path;

  path.push_back(current);
  paths.push(path);

  vector<vector<bool> > marked(maze.Columns(), vector<bool>(maze.Rows(), false));

  while (!paths.empty())
  {
    path = paths.front();
    paths.pop();

    current = path.back();

    if (maze.IsFinish(current))
      return path;

    if (maze.RightOpen(current) && !marked[current.Right().x()][current.Right().y()])
    {
      path.push_back(current.Right());
      paths.push(path);
      path.pop_back();
      marked[current.Right().x()][current.Right().y()] = true;
    }
    if (maze.DownOpen(current) && !marked[current.Down().x()][current.Down().y()])
    {
      path.push_back(current.Down());
      paths.push(path);
      path.pop_back();
      marked[current.Down().x()][current.Down().y()] = true;
    }
    if (maze.LeftOpen(current) && !marked[current.Left().x()][current.Left().y()])
    {
      path.push_back(current.Left());
      paths.push(path);
      path.pop_back();
      marked[current.Left().x()][current.Left().y()] = true;
    }
    if (maze.UpOpen(current) && !marked[current.Up().x()][current.Up().y()])
    {
      path.push_back(current.Up());
      paths.push(path);
      path.pop_back();
      marked[current.Up().x()][current.Up().y()] = true;
    }
  }

  return path;
}
