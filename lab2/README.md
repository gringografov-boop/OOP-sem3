# Лабораторная работа 2 — вариант 19

Полная реализация семейства C: класс `Matrix` с ручным управлением памятью и методом
`submatrix(size_t row, size_t col) const`.

## Состав проекта

- `include/matrix.h` — интерфейс класса.
- `src/matrix.cpp` — реализация.
- `src/main.cpp` — демонстрационная программа.
- `tests/matrix_tests.cpp` — 20 тестов Google Test.
- `CMakeLists.txt` — сборка библиотеки, демонстрации и тестов.

В классе реализованы:

- пустой и параметризованный конструкторы;
- конструкторы копирования и перемещения;
- деструктор;
- присваивание через copy-and-swap;
- `rows`, `cols`, `get`, `set`, `add`, `mul`, `print`;
- вариант 19: создание копии без указанной строки и столбца;
- проверка индексов, размеров операций и переполнения размера буфера.

Класс не использует `std::string`, `std::vector`, `std::array` и умные указатели.
Элементы хранятся построчно в `double*`, память выделяется через `new[]` и
освобождается через `delete[]`.

## Обычная сборка

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Запуск примера:

```bash
./build/matrix_demo
```

В многоконфигурационном генераторе путь может быть
`build/Debug/matrix_demo.exe`.

## AddressSanitizer

Для GCC или Clang:

```bash
cmake -S . -B build-asan -DENABLE_ASAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

Можно использовать и команду из задания:

```bash
cmake -S . -B build-asan -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

При первой конфигурации CMake загружает Google Test 1.15.2, поэтому нужен доступ
к интернету. Если Google Test уже установлен в системе, блок `FetchContent`
можно заменить на `find_package(GTest REQUIRED)`.

## Поведение при ошибках

- `get`, `set` и `submatrix` выбрасывают `std::out_of_range` при неверном индексе.
- `add` выбрасывает `std::invalid_argument`, если размеры не совпадают.
- `mul` выбрасывает `std::invalid_argument`, если число столбцов слева не равно
  числу строк справа.
- Слишком большой размер матрицы приводит к `std::length_error` до умножения
  размеров.
