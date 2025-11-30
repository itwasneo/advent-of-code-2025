cmake_minimum_required(VERSION 3.15)
project(advent-of-code-2025)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(Catch2)

set(DAYS
        src/day_01.cpp
)

set(SOURCES
        src/main.cpp
        src/utils.cpp
        ${DAYS}
)

set(HEADERS
        include/day_01.hpp
        include/v3.hpp
)

add_executable(main
        ${SOURCES}
        ${HEADERS}
)

add_executable(tests
        tests/test_example.cpp
        tests/test_utils.cpp
        src/utils.cpp
        ${DAYS}
        ${HEADERS}
)

# Link Libraries
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
# --------------

# Include Directories
target_include_directories(main PRIVATE include)
target_include_directories(tests PRIVATE include)
# --------------