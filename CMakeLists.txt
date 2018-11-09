cmake_minimum_required(VERSION 3.12)
project(hexdump C)

set(CMAKE_C_STANDARD 99)

add_executable(hexdump main.c hexdump.h hexdump.c)