# add_executable(map map.cpp)
add_executable(main main.cpp)


# target_include_directories(map PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})
# target_link_libraries(map PRIVATE Python3::Python )

# 添加库
# include_directories(../include)
# add_library(map Map.hpp)
target_link_directories(main PRIVATE /home/z/path_planning/dijkstra/include)
target_include_directories(main PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})
# target_include_directories(main PRIVATE /home/z/path_planning/dijkstra/include)
target_link_libraries(main PRIVATE Python3::Python)
