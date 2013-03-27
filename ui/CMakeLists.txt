find_package (Qt5Gui REQUIRED)
find_package (Qt5Widgets REQUIRED)
find_package (Qt5PrintSupport REQUIRED)

find_package (PkgConfig)

set (UI_REQUIRES
     Qt5Gui
     Qt5PrintSupport
     Qt5Widgets
    )

pkg_check_modules (CACHED_UI_REQUIRES ${UI_REQUIRES})

set (UI_SOURCE
     CellItem.cpp
     GridWindow.cpp
     main.cpp
     MazeMenuBar.cpp
     MazeView.cpp
     View.cpp
    )

set (UI_HEADERS
     CellItem.h
     GridWindow.h
     MazeMenuBar.h
     MazeView.h
    )

include_directories (${MAZE_GENERATORS_SOURCE_DIR}/maze)
link_directories (${MAZE_GENERATORS_BINARY_DIR}/maze)

add_executable (maze_ui ${UI_SOURCE} ${UI_HEADERS})
qt5_use_modules (maze_ui Widgets Gui PrintSupport)

target_link_libraries (maze_ui maze)
