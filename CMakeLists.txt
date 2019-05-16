cmake_minimum_required(VERSION 3.0.2)
project(cppsid)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(SDL2 REQUIRED)

add_library(cppsid STATIC src/libcsidlight.c src/cppsid.cpp)
target_link_libraries(cppsid SDL2::Main)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# c++ example using cppsid wrapper library
add_executable(player examples/player.cpp)
target_link_libraries(player cppsid)

# original c examples
add_executable(csidl examples/csid.c src/libcsidlight.c)
add_executable(csid examples/csid.c src/libcsidfull.c)
set_target_properties(csid PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_link_libraries(csidl SDL2::Main)
TARGEt_link_libraries(csid SDL2::Main)
