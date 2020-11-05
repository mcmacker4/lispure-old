cmake_minimum_required(VERSION 3.17)
project(lispure C)

set(CMAKE_C_STANDARD 99)

add_executable(lispure src/main.c src/util/string_intern.c src/util/string_intern.h src/parser/lexer.c src/parser/lexer.h src/parser/source.c src/parser/source.h src/parser/token.h src/util/list.h src/parser/token.c src/parser/parser.c src/parser/parser.h src/node/node.c src/node/node.h)