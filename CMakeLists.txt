cmake_minimum_required(VERSION 3.5)

# The OndraRT uses C++11
set(CMAKE_CXX_STANDARD 11)

# Print commands
set(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(base64)
add_subdirectory(terminal)
add_subdirectory(typograph)
add_subdirectory(usage)
add_subdirectory(examples)
