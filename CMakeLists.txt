cmake_minimum_required(VERSION 3.23)
project(NASDAQ_ITCH_PARSER LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE, Debug)
endif()

add_library(project_warnings INTERFACE)

set(COMMON_WARNINGS -Wall -Wextra -Wpedantic -Werror -Wshadow -Wcast-align -Wconversion)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build Mode: Debug (Sanitizers Active)")
    target_compile_options(project_warnings INTERFACE
        ${COMMON_WARNINGS} -Og -g3 
        -fsanitize=address,undefined 
        -fno-omit-frame-pointer
    )
    target_link_options(project_warnings INTERFACE -fsanitize=address,undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build Mode: Release (Maximum Throughput)")
    target_compile_options(project_warnings INTERFACE
        ${COMMON_WARNINGS}} -O3
        -march=native
        -DNDEBUG
        -flto
    )
    target_link_options(project_warnings INTERFACE -flto)
endif()

add_library(nasdaq_itch_parser INTERFACE)

target_include_directories(nasdaq_itch_parser INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(nasdaq_itch_parser INTERFACE project_warnings)

include(CTest)
enable_testing()
add_subdirectory(tests)
