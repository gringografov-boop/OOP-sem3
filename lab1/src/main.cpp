#include "str_ops.h"

#include <clocale>
#include <cstddef>
#include <iostream>
#include <limits>

namespace {

    void discard_input_line() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool read_menu_item(int& value) {
        if (std::cin >> value) {
            discard_input_line();
            return true;
        }

        std::cin.clear();
        discard_input_line();
        std::cout << "ОШИБКА ВВОДА. Введите снова.\n";
        return false;
    }

    bool read_size(const char* prompt, std::size_t& value) {
        std::cout << prompt;

        long long input = 0;
        if (!(std::cin >> input)) {
            std::cin.clear();
            discard_input_line();
            std::cout << "ОШИБКА ВВОДА. Введите целое неотрицательное число.\n";
            return false;
        }

        discard_input_line();

        if (input < 0) {
            std::cout << "ОШИБКА ВВОДА. Введите целое неотрицательное число.\n";
            return false;
        }

        value = static_cast<std::size_t>(input);
        return true;
    }

    char* read_line(const char* prompt) {
        std::cout << prompt;

        std::size_t capacity = 16;
        std::size_t length = 0;
        char* buffer = new char[capacity];
        char ch = '\0';

        while (std::cin.get(ch) && ch != '\n') {
            if (ch == '\r') {
                continue;
            }

            if (length + 1 >= capacity) {
                const std::size_t new_capacity = capacity * 2;
                char* new_buffer = new char[new_capacity];

                for (std::size_t i = 0; i < length; ++i) {
                    new_buffer[i] = buffer[i];
                }

                delete[] buffer;
                buffer = new_buffer;
                capacity = new_capacity;
            }

            buffer[length++] = ch;
        }

        buffer[length] = '\0';
        return buffer;
    }

    void print_menu() {
        std::cout << "1. Ввести строку\n"
            << "2. Напечатать\n"
            << "3. Длина\n"
            << "4. Скопировать в буфер и напечатать\n"
            << "5. Алгоритм варианта\n"
            << "0. Выход\n"
            << "Выберите пункт: ";
    }

    void run_variant_operations(const char* text) {
        std::cout << "1. Выделить подстроку\n"
            << "2. Лексикографически сравнить строки\n"
            << "0. Вернуться в главное меню\n"
            << "Выберите пункт: ";

        int choice = 0;
        if (!read_menu_item(choice)) {
            return;
        }

        switch (choice) {
        case 1: {
            std::size_t position = 0;
            std::size_t length = 0;

            if (!read_size("Введите позицию: ", position) ||
                !read_size("Введите длину подстроки: ", length)) {
                return;
            }

            char* substring = str_substr(text, position, length);

            std::cout << "Подстрока: ";
            str_print(substring);
            std::cout << '\n';

            str_delete(substring);
            return;
        }

        case 2: {
            char* other_line = read_line("Введите вторую строку: ");
            const int comparison = str_compare(text, other_line);

            if (comparison < 0) {
                std::cout << "Первая строка лексикографически меньше второй.\n";
            }
            else if (comparison > 0) {
                std::cout << "Первая строка лексикографически больше второй.\n";
            }
            else {
                std::cout << "Строки равны.\n";
            }

            str_delete(other_line);
            return;
        }

        case 0:
            return;

        default:
            std::cout << "Нет такого варианта.\n";
            return;
        }
    }

}

int main() {
    std::setlocale(LC_ALL, ".UTF8");

    bool running = true;
    char* text = nullptr;

    while (running) {
        print_menu();

        int choice = 0;
        if (!read_menu_item(choice)) {
            continue;
        }

        switch (choice) {
        case 0:
            running = false;
            break;

        case 1: {
            char* new_text = read_line("Введите строку: ");

            str_delete(text);
            text = new_text;

            std::cout << "Строка сохранена.\n";
            break;
        }

        case 2:
            std::cout << "Строка: ";
            str_print(text);
            std::cout << '\n';
            break;

        case 3:
            std::cout << "Длина строки: " << str_len(text) << '\n';
            break;

        case 4: {
            const std::size_t length = str_len(text);
            char* copy = new char[length + 1];

            str_copy(copy, text);

            std::cout << "Копия строки: ";
            str_print(copy);
            std::cout << '\n';

            str_delete(copy);
            break;
        }

        case 5:
            run_variant_operations(text);
            break;

        default:
            std::cout << "Такого пункта нет.\n";
            break;
        }
    }

    str_delete(text);
    std::cout << "Память освобождена. Программа завершена.\n";

    return 0;
}