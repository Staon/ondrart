cmake_minimum_required(VERSION 3.5)

project(ondrart_typograph VERSION 1.0)

include_directories(.. ../ondrart/typograph)
set(CMAKE_CXX_STANDARD 11)

add_library(ondrart_typograph STATIC
    linedriver.cpp
    linedriverios.cpp
    linedriverpre.cpp
    typoerror.cpp
    typograph.cpp
    typographblock.cpp
    typographblockattrs.cpp
    typographblockbox.cpp
    typographblockcols.cpp
    typographblockholder.cpp
    typographblockpar.cpp
    typographblockseq.cpp
    typographblocktext.cpp
    typographstate.cpp
    typotokenizer.cpp
)

    
    