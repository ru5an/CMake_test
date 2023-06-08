cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(Main)

add_library(InOutPut 
    src/InOutPut/InOutPut.cpp 
    src/InOutPut/InOutPut.h
)

add_library(RationalNumbers 
    src/RationalNumbers/RationalNumbers.cpp 
    src/RationalNumbers/RationalNumbers.h
)

add_library(Menu 
    src/Menu/Menu.cpp 
    src/Menu/Menu.h
)

add_executable(main 
    src/Main.cpp
)


target_link_libraries(RationalNumbers 
    PUBLIC InOutPut
)

target_link_libraries(Menu 
    PRIVATE RationalNumbers
)

target_link_libraries(main 
    PRIVATE Menu
)