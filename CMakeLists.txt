cmake_minimum_required(VERSION 3.5)
project(BLT_TESTS VERSION 0.0.1)

option(ENABLE_ADDRSAN "Enable the address sanitizer" OFF)
option(ENABLE_UBSAN "Enable the ub sanitizer" OFF)
option(ENABLE_TSAN "Enable the thread data race sanitizer" OFF)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(BLT-Graphics)

include_directories(include/)
file(GLOB_RECURSE source_files src/*.cpp)

add_executable(BLT_TESTS ${source_files})

target_link_libraries(BLT_TESTS BLT_GRAPHICS)