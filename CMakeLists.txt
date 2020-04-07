cmake_minimum_required(VERSION 3.10)

# set the project name
project(ANPR_TEST)
set (CMAKE_CXX_FLAGS "-m32 -Xlinker")
set (CMAKE_C_FLAGS "-m32 -Xlinker")
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# add the executable
add_executable(ANPR_TEST main.cpp)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR/libs})

target_link_libraries(ANPR_TEST cdk)