cmake_minimum_required(VERSION 3.0.0)
project(cling_node VERSION "0.0.1")

SET(CMAKE_SHARED_LIBRARY_SUFFIX ".node")

add_compile_options(-std=c++17)

find_package(Cling REQUIRED )

include_directories(/home/daminetreg/.node-gyp/8.9.4/include/node)
include_directories(/opt/softwares/cling_2018-02-17_ubuntu16/include)
add_library(cling_node main.cpp)
target_link_libraries(cling_node clingInterpreter clingMetaProcessor clingUserInterface clingUtils)
set_target_properties(cling_node PROPERTIES ENABLE_EXPORTS 1)
