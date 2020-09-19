cmake_minimum_required(VERSION 3.16)
project(pipes C)

set(CMAKE_C_STANDARD 99)

add_executable(copipe smpl/copipe-sum.c)
add_executable(pipe smpl/pipe-sum.c)
add_executable(pipes main.c smpl/pipe-paginator.h smpl/pipe-simple-sum.h)