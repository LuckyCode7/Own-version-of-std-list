project(list)
cmake_minimum_required(VERSION 2.8)

add_compile_options(-c
                    -Wall
                    -Wextra
                    -Winit-self
                    -Wold-style-cast
                    -Woverloaded-virtual
                    -Wuninitialized
                    -pedantic
                    -pedantic-errors
                    -std=c++14
                    -g)

set(SRC_LIST
	inc/list.hpp
	inc/node.hpp
	inc/exceptions.hpp
	src/main.cpp
)

include_directories(${PROJECT_SOURCE_DIR})
add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)


