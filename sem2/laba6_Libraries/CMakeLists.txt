cmake_minimum_required(VERSION 3.10)
project(MyProject)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_library(my_library 
    src/functions.c
)

if(BUILD_SHARED_LIBS)
    set_target_properties(my_library PROPERTIES 
        POSITION_INDEPENDENT_CODE ON
    )
endif()

add_executable(my_program src/main.c)
target_link_libraries(my_program my_library)
