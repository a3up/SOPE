cmake_minimum_required(VERSION 3.16)
project(pipes C)

set(CMAKE_C_STANDARD 99)

add_executable(copipe ex/copipe-sum.c)
add_executable(pipe ex/pipe-sum.c)
add_executable(pipes main.c ex/pipe-paginator.h ex/pipe-simple-sum.h)