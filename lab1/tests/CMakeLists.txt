include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(test_variant test_variant.cpp)
target_link_libraries(test_variant PRIVATE str_ops GTest::gtest_main)

if(MSVC)
    target_compile_options(test_variant PRIVATE /W4 /utf-8)
else()
    target_compile_options(test_variant PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GoogleTest)
gtest_discover_tests(test_variant)
