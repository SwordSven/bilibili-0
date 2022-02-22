cmake_minimum_required(VERSION 3.0)

project(bilibili-0)

include_directories(include)
aux_source_directory(src SRC_DIR)

add_compile_options(-g -Wall -std=c99)

add_executable(1
    app/main.c
    ${SRC_DIR}
)
