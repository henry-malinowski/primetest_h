cmake_minimum_required(VERSION 3.6)
project(primetest_h C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -Werror -lomp -fopenmp -lm -ffast-math -O2")
#set(CMAKE_C_FLAGS "-Wall -Werror -lomp -lm -ffast-math")
add_executable(primetest main.c primetest_32u.h)
