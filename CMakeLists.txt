cmake_minimum_required(VERSION 3.10)
project(insanelang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(insanelang
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
        src/codegen.cpp
)

target_include_directories(insanelang PUBLIC ${PROJECT_SOURCE_DIR}/src)
