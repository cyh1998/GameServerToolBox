cmake_minimum_required(VERSION 3.10)

project(utility)

include_directories(../3rdsrc)

aux_source_directory(./base BASE_SRCS)
aux_source_directory(./func FUNC_SRCS)
aux_source_directory(./thread THREAD_SRCS)
aux_source_directory(./load LOAD_SRCS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)

add_library(utility ${BASE_SRCS} ${FUNC_SRCS} ${THREAD_SRCS} ${LOAD_SRCS})
