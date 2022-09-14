cmake_minimum_required(VERSION 3.0)
project(rd_linux)
option(EXAMPLES "Build Example" OFF)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${PROJECT_SOURCE_DIR}/src/rdlinux.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)   

IF(EXAMPLE)
    add_executable(main ${PROJECT_SOURCE_DIR}/example/main.cpp)
    target_link_libraries(main PUBLIC ${PROJECT_NAME})
ENDIF(EXAMPLE)
