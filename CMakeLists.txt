cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

# set the project name
project(Tutorial)

#find_package(centurion REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/lib/centurion)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# add the executable
add_executable(Tutorial
${SDL2_LIBRARY}
src/main.cpp
)

target_link_libraries(Tutorial ${SDL2_LIBRARIES})
target_include_directories(Tutorial PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(Tutorial PUBLIC ${SDL2_CFLAGS_OTHER})