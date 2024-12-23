cmake_minimum_required(VERSION 3.10)
project(Lab1OS)

set(CMAKE_CXX_STANDARD 14)

add_executable(process_manager process_manager.cpp utils.cpp)
add_executable(parent parent.cpp utils.cpp)
add_executable(child1 child1.cpp utils.cpp)
add_executable(child2 child2.cpp utils.cpp)

target_link_libraries(process_manager pthread)
target_link_libraries(parent pthread)
target_link_libraries(child1 pthread)
target_link_libraries(child2 pthread)