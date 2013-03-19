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

#include "AldousBroderMaze.h"
#include "BinaryTreeMaze.h"
#include "GrowingTreeMaze.h"
#include "HuntAndKillMaze.h"
#include "RecursiveBacktrackerMaze.h"
#include "PrimsMaze.h"
#include "SideWinderMaze.h"
#include "WilsonsMaze.h"

#include "Solver.h"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int const X = 40;
int const Y = 80;

void time_maze(Maze& maze)
{
  auto st = std::chrono::system_clock::now();

  maze.Generate();

  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << " ms\t:" << maze.GetName() << std::endl;
}

void print_maze(Maze& maze)
{
  maze.PrintMaze();
}

void test_maze_bounds()
{
  BinaryTreeMaze m(10,10);
  Point start = m.GetStart();
  Point finish = m.GetFinish();

  assert(m.InBounds(start));
  assert(m.InBounds(finish));

  Point error(-4, 20);
  assert(!m.InBounds(error));
}

void test_cell_state()
{
  Cell c;

  c.AddDirection(Cell::Direction::RIGHT);
  c.AddDirection(Cell::Direction::DOWN);
  c.AddDirection(Cell::Direction::LEFT);
  c.AddDirection(Cell::Direction::UP);

  assert(c.RightOpen());
  assert(c.DownOpen());
  assert(c.LeftOpen());
  assert(c.UpOpen());

  c.RemoveDirection(Cell::Direction::RIGHT);
  c.RemoveDirection(Cell::Direction::DOWN);
  c.RemoveDirection(Cell::Direction::LEFT);
  c.RemoveDirection(Cell::Direction::UP);

  assert(c.Empty());
}

void test_opposite_direction()
{
  BinaryTreeMaze m(1,1);

  assert(m.OppositeDirection(Cell::Direction::RIGHT) == Cell::Direction::LEFT);
  assert(m.OppositeDirection(Cell::Direction::LEFT)  == Cell::Direction::RIGHT);
  assert(m.OppositeDirection(Cell::Direction::UP)    == Cell::Direction::DOWN);
  assert(m.OppositeDirection(Cell::Direction::DOWN)  == Cell::Direction::UP);
}

void test_point_class()
{
  Point p(1,1);
  assert(p.x() == 1);
  assert(p.y() == 1);

  assert(p.Right().y() == p.y()+1);
  assert(p.Left().y()  == p.y()-1);
  assert(p.Up().x()    == p.x()-1);
  assert(p.Down().x()  == p.x()+1);
}

void test_maze_init()
{
  BinaryTreeMaze m(X,Y);

  for (int i = 0; i < m.Columns(); i++)
  {
    for (int j = 0; j < m.Rows(); j++)
    {
      Point p (i,j);

      assert(!m.Get(p).RightOpen());
      assert(!m.Get(p).LeftOpen());
      assert(!m.Get(p).DownOpen());
      assert(!m.Get(p).UpOpen());
    }
  }
}

void test_maze_generates_solvable_path(Maze& maze)
{
  Solver s;
  vector<Point> path = s.DFSolve(maze);

  assert(maze.IsStart(path.front()));
  assert(maze.IsFinish(path.back()));

  for (auto p : path)
    assert(maze.InBounds(p));
}

int main()
{
  srand(time(NULL));

  test_maze_bounds();
  test_cell_state();
  test_opposite_direction();
  test_point_class();
  test_maze_init();

  vector<Maze*> mazes;

  RecursiveBacktrackerMaze rmaze(X, Y);
  mazes.push_back(&rmaze);

  WilsonsMaze wmaze(X, Y);
  mazes.push_back(&wmaze);

  SideWinderMaze smaze(X, Y);
  mazes.push_back(&smaze);

  HuntAndKillMaze hkmaze(X, Y);
  mazes.push_back(&hkmaze);

  AldousBroderMaze abmaze(X, Y);
  mazes.push_back(&abmaze);

  GrowingTreeMaze gtmaze(X, Y);
  mazes.push_back(&gtmaze);

  PrimsMaze pmaze(X, Y);
  mazes.push_back(&pmaze);

  BinaryTreeMaze bmaze(X, Y);
  mazes.push_back(&bmaze);

  for (auto maze : mazes)
  {
    time_maze(*maze);
    test_maze_generates_solvable_path(*maze);
  }

  //for (auto maze : mazes)
    //print_maze(*maze);
}
