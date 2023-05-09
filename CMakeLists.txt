cmake_minimum_required(VERSION 3.10)

project(toolbox)

find_package(Threads REQUIRED)

set(LIB_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory ("${PROJECT_SOURCE_DIR}/utility")
add_subdirectory ("${PROJECT_SOURCE_DIR}/third_party/behaviac")

add_subdirectory ("${PROJECT_SOURCE_DIR}/server")
