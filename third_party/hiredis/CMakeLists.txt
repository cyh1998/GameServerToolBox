cmake_minimum_required(VERSION 3.10)                    

project(hiredis)

aux_source_directory(./ LIB_SRCS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

add_library(hiredis ${LIB_SRCS})

