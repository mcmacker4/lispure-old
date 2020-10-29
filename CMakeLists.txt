cmake_minimum_required(VERSION 3.17)
project(lispure C)

set(CMAKE_C_STANDARD 99)

add_executable(lispure src/main.c src/util/string.c src/util/string.h src/parser/lexer.c src/parser/lexer.h)