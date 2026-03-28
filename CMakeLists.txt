cmake_minimum_required(VERSION 3.20)
project(Zhouyi-Algebra C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(Zhouyi-Algebra
        main.c
        zhouyi_algebra.c
        zhouyi_algebra.h
        suangua.c
        suangua.h)

target_include_directories(Zhouyi-Algebra PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(Zhouyi-Algebra PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARY}
        OpenMP::OpenMP_C)