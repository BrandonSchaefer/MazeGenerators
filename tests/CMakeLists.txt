find_package(GMock REQUIRED)

set (GTEST_BACKEND_SOURCE
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

add_executable (gtest-test-maze ${GTEST_BACKEND_SOURCE})

target_link_libraries (
    gtest-test-maze
    pthread
    maze
    ${GTEST_BOTH_LIBRARIES}
    ${GMOCK_LIBRARIES}
)

add_custom_target (check COMMAND gtest-test-maze)
