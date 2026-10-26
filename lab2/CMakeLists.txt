cmake_minimum_required(VERSION 3.16)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Библиотека класса Matrix
add_library(matrix src/matrix.cpp)

target_include_directories(
    matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Демонстрационная программа
add_executable(lab2 src/main.cpp)
target_link_libraries(lab2 PRIVATE matrix)

# Предупреждения компилятора и кодировка
if(MSVC)
    target_compile_options(matrix PRIVATE /W4 /utf-8)
    target_compile_options(lab2 PRIVATE /W4 /utf-8)
else()
    target_compile_options(matrix PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab2 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Подключение тестов
enable_testing()
add_subdirectory(tests)