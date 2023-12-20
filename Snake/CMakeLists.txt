cmake_minimum_required(VERSION 3.25)
project(Snake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/robert12/Qt6.6.0/6.6.0/gcc_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Snake main.cpp Snake.cpp Snake.h Game.cpp Game.h)
target_link_libraries(Snake
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

