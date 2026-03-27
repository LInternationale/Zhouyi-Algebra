cmake_minimum_required(VERSION 4.1)
project(Zhouyi-Algebra C)

set(CMAKE_C_STANDARD 11)

if(EXISTS "/opt/homebrew/include")
    include_directories("/opt/homebrew/include")
    link_directories("/opt/homebrew/lib")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_library(SDL2_MIXER_LIBRARY NAMES SDL2_mixer)
find_path(SDL2_MIXER_INCLUDE_DIR NAMES SDL_mixer.h PATH_SUFFIXES SDL2)

add_executable(JiajingOS main.c
        zhouyi_algebra.c
        zhouyi_algebra.h
        suangua.c
        suangua.h)

target_link_libraries(JiajingOS ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARY})