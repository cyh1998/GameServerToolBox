cmake_minimum_required(VERSION 3.10)                    

project(jsoncpp)

include_directories(../)

aux_source_directory(./ LIB_SRCS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

add_library(jsoncpp ${LIB_SRCS})
