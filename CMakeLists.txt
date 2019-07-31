cmake_minimum_required(VERSION 3.0.2)
project(cppsid)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(SDL2 CONFIG REQUIRED)

add_library(cppsid STATIC ${CMAKE_SOURCE_DIR}/src/libcsidlight.c ${CMAKE_SOURCE_DIR}/src/cppsid.cpp)
target_link_libraries(cppsid PRIVATE ${SDL2_LIBRARIES})
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
#include_directories(${CMAKE_SOURCE_DIR}/include)

# c++ example using cppsid wrapper library
add_executable(player ${CMAKE_SOURCE_DIR}/examples/player.cpp)
target_link_libraries(player cppsid)

# original c examples
add_executable(csidl ${CMAKE_SOURCE_DIR}/examples/csid.c ${CMAKE_SOURCE_DIR}/src/libcsidlight.c)
add_executable(csid ${CMAKE_SOURCE_DIR}/examples/csid.c ${CMAKE_SOURCE_DIR}/src/libcsidfull.c)
set_target_properties(csid PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_link_libraries(csidl PRIVATE ${SDL2_LIBRARIES} m)
target_link_libraries(csid PRIVATE ${SDL2_LIBRARIES} m)
