cmake_minimum_required(VERSION 3.20)

project(OptionPricing)

set(CMAKE_CXX_STANDARD 20)

add_executable(OptionPricing main.cpp src/option.cpp)

target_include_directories(OptionPricing PUBLIC include)