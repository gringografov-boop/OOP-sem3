cmake_minimum_required(VERSION 3.16)

project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(str_ops src/str_ops.cpp)
target_include_directories(str_ops PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab1 src/main.cpp)
target_link_libraries(lab1 PRIVATE str_ops)

if(MSVC)
    target_compile_options(str_ops PRIVATE /W4 /utf-8)
    target_compile_options(lab1 PRIVATE /W4 /utf-8)
else()
    target_compile_options(str_ops PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab1 PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_subdirectory(tests)
