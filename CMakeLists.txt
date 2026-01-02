cmake_minimum_required(VERSION 3.23)
project(NASDAQ_ITCH_PARSER LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -g3 
    -Wall -Wextra -Wpedantic -Werror 
)

add_library(nasdaq_itch_parser INTERFACE)

target_include_directories(nasdaq_itch_parser INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
target_sources(nasdaq_itch_parser PRIVATE ${CPP_SOURCES})

include(CTest)
enable_testing()
add_subdirectory(tests)
