cmake_minimum_required(VERSION 3.6)
project(stromrallye)

set(CMAKE_CXX_STANDARD 11)

add_executable(stromrallye files/main.cpp)
target_link_libraries(stromrallye)

install(TARGETS stromrallye DESTINATION bin)

