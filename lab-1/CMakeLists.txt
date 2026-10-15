cmake_minimum_required(VERSION 3.16)
project(lab-1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Библиотека с чистыми функциями ---
add_library(lab1_lib
    src/array_ops.cpp
    src/func_for_var2.cpp
)
target_include_directories(lab1_lib PUBLIC src)

# Флаги компилятора для отладки
target_compile_options(lab1_lib PRIVATE
    -Wall -Wextra -Wpedantic
)

# --- Основная программа ---
add_executable(program main.cpp)
target_link_libraries(program PRIVATE lab1_lib)

# --- Google Test ---
include(FetchContent)

FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Тесты ---
enable_testing()

add_executable(tests
    tests/test.cpp
)
target_link_libraries(tests PRIVATE
    lab1_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
