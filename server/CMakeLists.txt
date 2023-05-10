set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_PATH})

file(GLOB_RECURSE SERVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SERVER_INC "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

include_directories(${PROJECT_SOURCE_DIR}/utility)

include_directories("${PROJECT_SOURCE_DIR}/third_party/behaviac/inc")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/AI/cpp)

add_executable(server ${SERVER_INC} ${SERVER_SRC})

target_link_libraries(server libbehaviac utility ${CMAKE_THREAD_LIBS_INIT})