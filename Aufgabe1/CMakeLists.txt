cmake_minimum_required(VERSION 3.6)
project(stromrallye)

set(CMAKE_CXX_STANDARD 14)

add_executable(stromrallye files/main.cpp files/graph.cpp files/backtracking.cpp files/generate.cpp)
target_link_libraries(stromrallye -std=c++14)

install(TARGETS stromrallye DESTINATION bin)

