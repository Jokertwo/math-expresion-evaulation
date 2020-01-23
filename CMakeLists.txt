cmake_minimum_required(VERSION 3.15)
project(Clion_svatava C)

set(CMAKE_C_STANDARD 90)

add_executable(Clion_svatava main.c zasobnik.c zasobnik.h constants.h logger.h logger.c number_buffer.c number_buffer.h)