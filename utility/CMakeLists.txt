include_directories(${PROJECT_SOURCE_DIR}/third_party)
include_directories(/usr/include/mysql)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/base   BASE_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/db     DB_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/func   FUNC_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/hotfix HOTFIX_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/load   LOAD_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/proc   PROC_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/thread THREAD_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/timer  TIMER_SRCS)

set(CMAKE_CXX_FLAGS "-rdynamic -std=c++14")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_PATH})

add_library(utility ${BASE_SRCS} ${DB_SRCS} ${FUNC_SRCS} ${HOTFIX_SRCS} ${LOAD_SRCS} ${PROC_SRCS} ${THREAD_SRCS} ${TIMER_SRCS})
