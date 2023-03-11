cmake_minimum_required(VERSION 3.5)

set(target_name UnitTestFramework)

# ----- compilation settings

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----- compilation modules

set(headers
    support/unit_test.h
)

set(sources 
    support/unit_test.cpp
    gmock/src/gmock-all.cc
    gtest/src/gtest-all.cc
)

add_library(${target_name} STATIC ${sources} ${headers})

target_include_directories(${target_name} PRIVATE gmock)
target_include_directories(${target_name} PRIVATE gtest)
target_include_directories(${target_name} PUBLIC gmock/include)
target_include_directories(${target_name} PUBLIC gtest/include)

target_link_libraries(${target_name} eWeatherLib)