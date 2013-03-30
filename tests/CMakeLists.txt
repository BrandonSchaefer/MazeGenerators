# Build gtest our selfs :(
set (GTEST_ROOT_DIR
     "/usr/src/gtest"
     CACHE
     PATH
     "Path to Google Tests source"
     FORCE)

set (GTEST_INCLUDE_DIR
     "/usr/include/gtest"
     CACHE
     PATH
     "Path to Google Tests include"
     FORCE)

find_path (GTEST_INCLUDE_DIR gtests/gtest.h)

if (GTEST_INCLUDE_DIR)
  add_subdirectory (
    ${GTEST_ROOT_DIR}
    gtest
   )
endif (GTEST_INCLUDE_DIR)

enable_testing ()

find_library (GMOCK_LIB gmock)
find_library (GMOCK_MAIN_LIB gmock_main)
find_path (GTEST_SRC_DIR gtest.cc PATHS /usr/src/gtest/src)

if (GTEST_SRC_DIR AND
    GMOCK_LIB AND
    GMOCK_MAIN_LIB)

  set (GTEST_GMOCK_LIB
       gtest
       ${GMOCK_LIB}
       ${GMOCK_MAIN_LIB}
      )

  set (GTEST_MAZE_SOURCE
       test_aldous_broder.cpp
       test_binary_tree.cpp
       test_cell.cpp
       test_growing_tree.cpp
       test_hunt_and_kill.cpp
       test_marked.cpp
       test_maze.cpp
       test_maze_factory.cpp
       test_point.cpp
       test_prims.cpp
       test_recursive_backtracker.cpp
       test_side_winder.cpp
       test_main.cpp
       test_solver.cpp
       test_wilsons.cpp
      )

  include_directories (${MAZE_GENERATORS_SOURCE_DIR}/maze ${GTEST_INCLUDE_DIR})

  add_executable (gtest-test-maze ${GTEST_MAZE_SOURCE})
  target_link_libraries (gtest-test-maze maze ${GTEST_GMOCK_LIB})
  add_test (MazeGTest gtest-test-maze)

  set (GTEST_UI_SOURCE
       test_main.cpp
       test_cell_item.cpp
      )

  include_directories (${MAZE_GENERATORS_SOURCE_DIR}/ui ${MAZE_GENERATORS_SOURCE_DIR}/maze ${GTEST_INCLUDE_DIR})

  add_executable (gtest-test-ui ${GTEST_UI_SOURCE})
  qt5_use_modules (gtest-test-ui Widgets Gui PrintSupport)

  target_link_libraries (gtest-test-ui maze ui ${GTEST_GMOCK_LIB})
  add_test (UiGTest gtest-test-ui)

  add_custom_target (check COMMAND ./gtest-test-maze && ./gtest-test-ui DEPENDS gtest-test-maze gtest-test-ui)

endif (GTEST_SRC_DIR AND
       GMOCK_LIB AND
       GMOCK_MAIN_LIB)
