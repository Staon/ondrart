cmake_minimum_required(VERSION 3.5)

project(ondrart_base64 VERSION 1.0)

include_directories(..)
set(CMAKE_CXX_STANDARD 11)

add_library(ondrart_base64 STATIC
    ostream.cpp
)
