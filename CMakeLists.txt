cmake_minimum_required(VERSION 3.0)
project ("cainit" VERSION 0.4)

add_compile_options(-std=c++11 -Wall)

include(CPack)

file(GLOB SOURCES
    src/include/*.hpp
    src/*.cpp
)

add_executable( cainit ${SOURCES} )