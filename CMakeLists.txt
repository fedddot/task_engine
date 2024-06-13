cmake_minimum_required(VERSION 3.12)

project(test_engine C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(creator INTERFACE)
target_include_directories(creator INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(task INTERFACE)
target_include_directories(task INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(parser INTERFACE)
target_include_directories(parser INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(serializer INTERFACE)
target_include_directories(serializer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(engine INTERFACE)
target_include_directories(engine INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    engine
    INTERFACE
    creator
    task
    parser
    serializer
    data_lib
)

add_subdirectory(data)
add_subdirectory(utils)
add_subdirectory(external)
add_subdirectory(tests EXCLUDE_FROM_ALL)