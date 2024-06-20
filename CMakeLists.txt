cmake_minimum_required(VERSION 3.27)

project(UnitTestFramework
    VERSION "1.0.0"
    HOMEPAGE_URL ""
    DESCRIPTION "Unit Test support framework for C++"
    LANGUAGES CXX
)

set(target libutfw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)

set(headers
    support/unit_test.h
)

set(sources 
    support/unit_test.cpp
)

add_library(${target} STATIC ${sources} ${headers})

target_include_directories(${target} PRIVATE gmock)
target_include_directories(${target} PRIVATE gtest)
target_include_directories(${target} PUBLIC googletest/googlemock/include)
target_include_directories(${target} PUBLIC googletest/googletest/include)
