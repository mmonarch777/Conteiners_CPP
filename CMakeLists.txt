cmake_minimum_required(VERSION 3.21)
project(conteiner)

file(GLOB
        FC "test/sources/vector_tests/constructor.cpp")

set(CMAKE_CXX_STANDARD 98)

add_executable(conteiner ${FC})
