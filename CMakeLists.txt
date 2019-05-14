cmake_minimum_required(VERSION 3.0.2)
project(csid)
find_package(SDL REQUIRED)

include_directories(SYSTEM ${SDL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(csidl examples/csid.c src/libcsidlight.c)
add_executable(csid examples/csid.c src/libcsidfull.c)
target_link_libraries(csidl ${SDL_LIBRARY})
target_link_libraries(csid ${SDL_LIBRARY})
