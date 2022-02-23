cmake_minimum_required(VERSION 3.21)
project(TP_thread C)

set(CMAKE_C_STANDARD 99)
include_directories(includes)
add_executable(TP_thread sources/main.c includes/main.h includes/camion.h sources/camion.c includes/logistic.h sources/logistic.c)
