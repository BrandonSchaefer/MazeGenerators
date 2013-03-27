set (MAZE_SORUCE
     AldousBroderMaze.cpp
     BinaryTreeMaze.cpp
     Cell.cpp
     GrowingTreeMaze.cpp
     HuntAndKillMaze.cpp
     Marked.cpp
     Maze.cpp
     MazeFactory.cpp
     PrimsMaze.cpp
     Point.cpp
     RecursiveBacktrackerMaze.cpp
     SideWinderMaze.cpp
     Solver.cpp
     WilsonsMaze.cpp
    )

set (MAZE_HEADER
     AldousBroderMaze.h
     BinaryTreeMaze.h
     Cell.h
     GrowingTreeMaze.h
     HuntAndKillMaze.h
     Marked.h
     Maze.h
     MazeFactory.h
     PrimsMaze.h
     Point.h
     RecursiveBacktrackerMaze.h
     SideWinderMaze.h
     Solver.h
     WilsonsMaze.h
    )

add_library (maze ${MAZE_SORUCE} ${MAZE_HEADER})
