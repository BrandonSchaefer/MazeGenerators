enable_testing ()

include_directories (${MAZE_GENERATORS_SOURCE_DIR}/maze ${GTEST_INCLUDE_DIR})
link_directories (${MAZE_GENERATORS_BINARY_DIR}/maze)

add_executable (maze_test main.cpp)

target_link_libraries (maze_test maze)
