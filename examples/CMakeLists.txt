cmake_minimum_required(VERSION 3.5)

include_directories(..)
set(CMAKE_CXX_STANDARD 11)

add_executable(typograph_example
    main.cpp
)
target_link_libraries(typograph_example
    ondrart_usage
    ondrart_typograph
)
