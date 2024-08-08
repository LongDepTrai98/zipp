cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
project(zipp)

add_executable(${PROJECT_NAME}
    include/zipp.hpp
    src/zipp.cpp
    src/main.cpp
    lib/minizip/minishared.h
    lib/minizip/tmzip.h
    lib/minizip/unzip.h
    lib/minizip/zip.h
    lib/minizip/crypt.h
    lib/minizip/ioapi.h
    lib/minizip/ioapi_buf.h
    lib/minizip/ioapi_mem.h
    lib/minizip/iowin32.h
    lib/minizip/minishared.c
    lib/minizip/miniunz.c
    lib/minizip/minizip.c
    lib/minizip/tmzip.c
    lib/minizip/unzip.c
    lib/minizip/zip.c
    lib/minizip/crypt.c
    lib/minizip/ioapi.c
    lib/minizip/ioapi_buf.c
    lib/minizip/ioapi_mem.c
    lib/minizip/iowin32.c
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE lib
    PRIVATE lib/zlib/include
    PRIVATE include
)

target_link_libraries(${PROJECT_NAME}
    debug  ${CMAKE_CURRENT_SOURCE_DIR}/lib/zlib/debug/lib/zlibd.lib
    optimized  ${CMAKE_CURRENT_SOURCE_DIR}/lib/zlib/release/lib/zlib.lib
)

add_compile_definitions(NOMAIN)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)