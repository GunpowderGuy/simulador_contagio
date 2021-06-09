cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

# set the project name
project(contagio)

include_directories(${PROJECT_SOURCE_DIR}/lib/centurion)

#https://bbs.archlinux.org/viewtopic.php?id=252171
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# add the executable
add_executable(poo2
src/main.cpp
)

target_link_libraries(poo2 ${SDL2_LIBRARIES})
target_include_directories(poo2 PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(poo2 PUBLIC ${SDL2_CFLAGS_OTHER})