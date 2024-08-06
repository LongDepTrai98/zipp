cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
project(minipp)

add_executable(${PROJECT_NAME}
    include/minipp.hpp
    src/minipp.cpp
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE lib/minizip/include
    PRIVATE include
)

target_link_libraries(${PROJECT_NAME}
    debug  ${CMAKE_CURRENT_SOURCE_DIR}/lib/minizip/debug/lib/minizip.lib
    debug  ${CMAKE_CURRENT_SOURCE_DIR}/lib/minizip/debug/lib/zlibd.lib
    optimized  ${CMAKE_CURRENT_SOURCE_DIR}/lib/minizip/release/lib/minizip.lib
    optimized  ${CMAKE_CURRENT_SOURCE_DIR}/lib/minizip/release/lib/zlib.lib
)