cmake_minimum_required(VERSION 3.15)
project(advent-of-code-2025)

# Compilation Speedups
## Use ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "✓ Using ccache: ${CCACHE_PROGRAM}")
endif()

## Enable parallel builds
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
    message(STATUS "✓ Parallel builds enabled: ${N} cores")
endif()

## Use Ninja if available 
find_program(NINJA_PROGRAM ninja)
if(NINJA_PROGRAM)
    message(STATUS "✓ Ninja available (use: cmake -G Ninja ..)")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Add compilation flags
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

## Compiler Flags
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g1 -O0")

## Default to Release build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

## Catch2 with caching
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.11.0
        GIT_SHALLOW TRUE # Faster clone
)
FetchContent_MakeAvailable(Catch2)

# SOURCE FILES
set(DAYS
        src/day_01.cpp
        # Add more days as needed
)

set(UTILS
    src/utils.cpp
)

set(SOURCES
        src/main.cpp
        ${UTILS}
        ${DAYS}
)

set(HEADERS
        include/day_01.hpp
        include/v3.hpp
)

# LIBRARY TARGET
# Creating a library with shared code. This way, changes to main.cpp don't recompile everything
add_library(aoc_lib STATIC
    ${DAYS}
    ${UTILS}
    ${HEADERS}
)

target_include_directories(aoc_lib PUBLIC include)
target_precompile_headers(aoc_lib PUBLIC
    <vector>
    <string>
    <iostream>
    <algorithm>
    <fstream>
    <sstream>
    <stdexcept>
)

# MAIN EXECUTABLE
add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE aoc_lib)

# Pass project directory for file paths
# TODO: Consider this again
target_compile_definitions(main PRIVATE
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

# TEST EXECUTABLES
set(TEST_SOURCES
    tests/test_example.cpp
    tests/test_utils.cpp
    # Add more test files as needed
)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE 
    aoc_lib
    Catch2::Catch2WithMain
)
target_precompile_headers(tests PRIVATE
    <catch2/catch_test_macros.hpp>
    <catch2/benchmark/catch_benchmark.hpp>
)

# Copy Input Files
if(EXISTS ${CMAKE_SOURCE_DIR}/input)
    add_custom_target(copy_inputs ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/input
            ${CMAKE_BINARY_DIR}/input
        COMMENT "Copying input files to build directory"
    )

    # Make executables depend on copied inputs
    add_dependencies(main copy_inputs)
    add_dependencies(tests copy_inputs)

    message(STATUS "✓ Input files will be copied to build/input")
endif()

# CUSTOM TARGETS

if (CMAKE_GENERATOR STREQUAL "Ninja")
    # Fast rebuild(parallel)
    add_custom_target(fast
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} -j${N}
        COMMENT "Fast parallel build using ${N} cores"
    )

    add_custom_target(rebuild
        COMMAND ninja clean
        COMMAND ninja -j{N}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Clean rebuild"
    )
else()
    # Fast rebuild(parallel)
    add_custom_target(fast
        COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Fast parallel build using ${N} cores"
    )

    add_custom_target(rebuild
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
        COMMENT "Clean rebuild"
    )
endif()


# -----------------------
#   BUILD INFO
# -----------------------
message(STATUS "=================================")
message(STATUS "Build Configuration:")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Parallel Jobs: ${N}")
if(CCACHE_PROGRAM)
    message(STATUS "  Cache: ccache enabled")
endif()
message(STATUS "=================================")
