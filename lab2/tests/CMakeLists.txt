include(FetchContent)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

# Совместимые настройки runtime для Windows/MSVC
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(lab2_tests matrix_tests.cpp)

target_link_libraries(
    lab2_tests
    PRIVATE matrix GTest::gtest_main
)

if(MSVC)
    target_compile_options(lab2_tests PRIVATE /W4 /utf-8)
else()
    target_compile_options(
        lab2_tests PRIVATE -Wall -Wextra -Wpedantic
    )
endif()

include(GoogleTest)
gtest_add_tests(
    TARGET lab2_tests
    SOURCES matrix_tests.cpp
)