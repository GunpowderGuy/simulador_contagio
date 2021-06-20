cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

# set the project name
project(poo2)

include_directories(${PROJECT_SOURCE_DIR}/lib/centurion)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#https://bbs.archlinux.org/viewtopic.php?id=252171
find_package(PkgConfig REQUIRED)
#sometimes requiered
pkg_check_modules(SDL2 REQUIRED sdl2) 

find_package(SDL2 REQUIRED) 

find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# add the executable
add_executable(poo2
src/main.cpp
src/estado.hpp
)

target_link_libraries(poo2 ${SDL2_LIBRARIES})
target_link_libraries(poo2 ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(poo2 ${SDL2_MIXER_LIBRARIES})
target_link_libraries(poo2 ${SDL2_TTF_LIBRARIES})

target_include_directories(poo2 PUBLIC ${SDL2_INCLUDE_DIRS})
#target_compile_options(poo2 PUBLIC ${SDL2_CFLAGS_OTHER})