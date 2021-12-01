cmake_minimum_required(VERSION 3.16)
project(crypro-studio)



set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I. -g -Wall")

# AES binary
add_executable(aes-test aes-test.c aes.h)


