cmake_minimum_required(VERSION 3.15)
project(Clion_svatava C)


set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -pedantic")

add_executable(Clion_svatava main.c stack.c stack.h constants.h logger.h logger.c number_buffer.c number_buffer.h letter_buffer.c letter_buffer.h buffer.c buffer.h tokenizer.c tokenizer.h)