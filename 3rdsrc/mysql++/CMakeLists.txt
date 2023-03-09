cmake_minimum_required(VERSION 3.10)

project(mysqlpp)

include_directories(/usr/include/mysql)

aux_source_directory(./ LIB_SRCS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

add_library(mysqlpp ${LIB_SRCS})

target_link_libraries(${PROJECT_NAME} libmysqlclient.so)

