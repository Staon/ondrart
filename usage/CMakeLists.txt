cmake_minimum_required(VERSION 3.5)

project(ondrart_usage VERSION 1.0)

include_directories(.. ../ondrart/usage ../ondrart/typograph)

add_library(ondrart_usage STATIC
    usage.cpp
)

    
    