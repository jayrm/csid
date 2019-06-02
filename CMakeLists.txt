cmake_minimum_required(VERSION 3.0.2)
project(cppsid)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(SDL2 REQUIRED)

add_library(cppsid STATIC ${CMAKE_SOURCE_DIR}/src/libcsidlight.c ${CMAKE_SOURCE_DIR}/src/cppsid.cpp)
target_link_libraries(cppsid SDL2::Main)
include_directories(${CMAKE_SOURCE_DIR}/include)

# c++ example using cppsid wrapper library
add_executable(player ${CMAKE_SOURCE_DIR}/examples/player.cpp)
target_link_libraries(player cppsid)

# original c examples
add_executable(csidl ${CMAKE_SOURCE_DIR}/examples/csid.c ${CMAKE_SOURCE_DIR}/src/libcsidlight.c)
add_executable(csid ${CMAKE_SOURCE_DIR}/examples/csid.c ${CMAKE_SOURCE_DIR}/src/libcsidfull.c)
set_target_properties(csid PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_link_libraries(csidl SDL2::Main m)
target_link_libraries(csid SDL2::Main m)
