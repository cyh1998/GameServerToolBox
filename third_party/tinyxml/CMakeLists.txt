cmake_minimum_required(VERSION 3.10)

project(tinyxml)

aux_source_directory(./ LIB_SRCS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

add_library(tinyxml ${LIB_SRCS})
