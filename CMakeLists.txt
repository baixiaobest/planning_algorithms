# CMakeList.txt : CMake project for Planning Algorithms, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Planning Algorithms")

include_directories("include")

add_library(DStarLite "src/DStarLite.cpp")

# Add source to this project's executable.
add_executable (CMakeTarget "Planning Algorithms.cpp")
target_link_libraries(CMakeTarget DStarLite)

# TODO: Add tests and install targets if needed.
