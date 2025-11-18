cmake_minimum_required(VERSION 3.25)
project(lexer)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件搜索路径（关键步骤）
include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(lexer main.cpp include/token.h include/lexer.h src/lexer.cpp src/parser.cpp include/parser.h)
