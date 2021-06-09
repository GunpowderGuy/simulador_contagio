cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

# set the project name
project(contagio)

#find_package(centurion REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/lib/centurion)

#https://bbs.archlinux.org/viewtopic.php?id=252171
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# add the executable
add_executable(contagio
${SDL2_LIBRARY}
src/main.cpp
)

target_link_libraries(contagio ${SDL2_LIBRARIES})
target_include_directories(contagio PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(contagio PUBLIC ${SDL2_CFLAGS_OTHER})