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

#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include <chrono>

#include <iostream>

void time_maze(Maze& maze)
{
  auto st = std::chrono::system_clock::now();

  maze.Generate();

  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << std::endl;
}

void print_maze(Maze& maze)
{
  maze.PrintMaze();
  usleep(360000 * 5);
}

int main()
{
  int x = 40;
  int y = 80;
  srand(time(NULL));

  WilsonsMaze wmaze(x,y);
  time_maze(wmaze);
  print_maze(wmaze);

  SideWinderMaze smaze(x,y);
  time_maze(smaze);
  print_maze(smaze);

  RecursiveBacktrackerMaze rmaze(x, y);
  time_maze(rmaze);
  print_maze(rmaze);

  HuntAndKillMaze hkmaze(x,y);
  time_maze(hkmaze);
  print_maze(hkmaze);

  AldousBroderMaze abmaze(x,y);
  time_maze(abmaze);
  print_maze(abmaze);

  GrowingTreeMaze gtmaze(x,y);
  time_maze(gtmaze);
  print_maze(gtmaze);

  PrimsMaze pmaze(x,y);
  time_maze(pmaze);
  print_maze(pmaze);

  BinaryTreeMaze bmaze(x, y);
  time_maze(bmaze);
  print_maze(bmaze);

  /*


  Solver s;
  //std::cout << s.DFSolve(abmaze).size() << std::endl;
  //std::cout << s.DFSolve(wmaze).size() << std::endl;
  std::cout << s.DFSolve(pmaze).size() << std::endl;
  std::cout << s.DFSolve(bmaze).size() << std::endl;
  std::cout << s.DFSolve(rmaze).size() << std::endl;
  */
  /*
  for (auto e : s.DFSolve(rmaze))
  {
    rmaze.SetStart(e);
    rmaze.PrintMaze();
    usleep(360000/8);
  }
  */

  /*
  // - s ab
  Solver s;
  auto st = std::chrono::system_clock::now();
  s.DFSolve(abmaze);
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << std::endl;

  // -
  st = std::chrono::system_clock::now();
  s.DFSolve(pmaze);
  end = std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << std::endl;
  

  st = std::chrono::system_clock::now();
  s.DFSolve(rmaze);
  end = std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << std::endl;

  */

  /*
  for (auto e : s.DFSolve(pmaze))
  {
    //rmaze.Get(e).path = true;
    pmaze.SetStart(e);
    pmaze.PrintMaze();
    usleep(360000);
  }

  //std::cout << s.BFSolve(rmaze).size() << std::endl;
  st = std::chrono::system_clock::now();

  s.DFSolve(maze).size();
  end = std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << std::endl;

  st = std::chrono::system_clock::now();

  s.DFSolve(rmaze).size();
  end = std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << std::endl;
  */



  // ------- TESTS ------- //
  
  BinaryTreeMaze m(x,y);
  for (int i = 0; i < m.Columns(); i++)
  {
    for (int j = 0; j < m.Rows(); j++)
    {
      Point p (i,j);

      // Assert we start with no sides open
      assert(!m.Get(p).RightOpen());
      assert(!m.Get(p).LeftOpen());
      assert(!m.Get(p).DownOpen());
      assert(!m.Get(p).UpOpen());
    }
  }

  assert(m.Columns() == x + 2);
  assert(m.Rows() == y + 2);

  Point start(1,1);
  m.SetStart(start);
  assert(m.IsStart(start));
  assert(m.InBounds(start));

  Point finish(5,5);
  m.SetFinish(finish);
  assert(m.IsFinish(finish));
  assert(m.InBounds(finish));

  Point error(-4, 20);
  assert(!m.InBounds(error));

  // testing adding/removing
  Cell c;

  c.AddDirection(Cell::Direction::RIGHT);
  c.AddDirection(Cell::Direction::LEFT);
  assert(c.RightOpen());
  assert(c.LeftOpen());

  c.RemoveDirection(Cell::Direction::LEFT);
  assert(!c.LeftOpen());
  assert(c.RightOpen());

  // Assert OppositeDirections
  assert(m.OppositeDirection(Cell::Direction::RIGHT) == Cell::Direction::LEFT);
  assert(m.OppositeDirection(Cell::Direction::LEFT)  == Cell::Direction::RIGHT);
  assert(m.OppositeDirection(Cell::Direction::UP)    == Cell::Direction::DOWN);
  assert(m.OppositeDirection(Cell::Direction::DOWN)  == Cell::Direction::UP);

  // Point tests
  Point p(1,1);
  assert(p.x() == 1);
  assert(p.y() == 1);

  assert(p.Right().y() == p.y()+1);
  assert(p.Left().y()  == p.y()-1);
  assert(p.Up().x()    == p.x()-1);
  assert(p.Down().x()  == p.x()+1);
}
