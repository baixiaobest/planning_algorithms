# CMakeList.txt : CMake project for Planning Algorithms, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Planning Algorithms")

enable_testing()
find_package(GTest CONFIG REQUIRED)
include_directories("include")

add_library(DStarLite "src/DStarLite.cpp" "src/AugmentedPriorityQueue.cpp")

# Add source to this project's executable.
add_executable (CMakeTarget "Planning Algorithms.cpp")
target_link_libraries(CMakeTarget DStarLite)

# TODO: Add tests and install targets if needed.

add_executable(PriorityQueueTest "tests/AugmentedPriorityQueueTest.cpp")
target_link_libraries(PriorityQueueTest DStarLite GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
add_test(PriorityQueueTest PriorityQueueTest)
