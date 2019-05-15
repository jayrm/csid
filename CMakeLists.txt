cmake_minimum_required(VERSION 3.0.2)
project(cppsid)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)

# to use ppsid c++ wrapper, copy the following to CMakeLists.txt
# --- from here ----
find_package(SDL REQUIRED)
include_directories(SYSTEM ${SDL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(cppsid STATIC src/libcsidlight.c src/cppsid.cpp)
target_link_libraries(cppsid ${SDL_LIBRARY})
# --- to here ---

# c++ example using cppsid wrapper library
add_executable(player examples/player.cpp)
target_link_libraries(player cppsid)

# original c examples
add_executable(csidl examples/csid.c src/libcsidlight.c)
add_executable(csid examples/csid.c src/libcsidfull.c)
set_target_properties(csid PROPERTIES EXCLUDE_FROM_ALL TRUE)
target_link_libraries(csidl ${SDL_LIBRARY})
TARGEt_link_libraries(csid ${SDL_LIBRARY})
