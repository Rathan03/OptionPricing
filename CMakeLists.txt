cmake_minimum_required(VERSION 3.20)

project(OptionPricing)

set(CMAKE_CXX_STANDARD 20)

add_library(OptionPricingLib
    src/option.cpp
    src/marketdata.cpp
    src/blackscholes.cpp
)

target_include_directories(OptionPricingLib PUBLIC include)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    OptionPricingTests
    tests/option_tests.cpp
    tests/marketdata_tests.cpp
    tests/blackscholes_tests.cpp
)

target_link_libraries(
    OptionPricingTests
    PRIVATE
        OptionPricingLib
        GTest::gtest_main
)

enable_testing()

add_test(OptionPricingTests OptionPricingTests)