cmake_minimum_required(VERSION 3.10)

project(dijkstra)

find_package(Python3 COMPONENTS Development REQUIRED)

set(MATPLOTLIB_CPP_INCLUDE_DIRS /home/z/vcpkg/installed/x64-linux/include)

include_directories(/home/z/path_planning/dijkstra/include)

add_subdirectory(src)
