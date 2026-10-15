#include <iostream>
#include "array_ops.h"

void clear_input() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int main() {
    std::cout << "\033[1;36m";
    std::cout << "1. Создать массив" << "\t\t" << "6. Удалить массив\n";
    std::cout << "2. Напечатать" << "\t\t\t" << "7. Сортировка\n";
    std::cout << "3. Вставить элемент" << "\t\t" << "8. Сортировка + Бинарный поиск\n";
    std::cout << "4. Удалить элемент" << "\t\t" << "9. Перевернуть массив\n";
    std::cout << "5. Изменить размер" << "\t\t" << "0. Выход\n";
    std::cout << "\033[0m";
    
    int *arr = nullptr;
    std::size_t capacity{};
    std::size_t size{};

    while (1) {
        std::cout << "$ Ваш Выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                std::cout << "EOF\n";
                break;
            }
            clear_input();
            std::cout << "\033[31mНеверный ввод\033[0m\n";
            continue;
        }

        clear_input();

        if (choice == 0) {
            array_delete(arr);
            size = 0;
            capacity = 0;

            std::cout << "\033[36mВыход...\033[0m\n";
            break;
        }

        switch (choice)
        {
        case 1: {
            /*Создание массива*/
            std::cout << "$ Введите вместимость массива: ";

            int cap;
            if (!(std::cin >> cap) || cap < 0) {
                std::cout << "\033[31mНеверный ввод: Должно быть capacity >= 0\033[0m\n";
                break;
            }

            if (arr != nullptr) {
                array_delete(arr);
                std::cout << "\033[32m" << "Старый массив был удален" << "\033[0m\n";
            }

            capacity = static_cast<std::size_t>(cap);
            arr = array_create(capacity);
            std::cout << "\033[32m" << "Создан массив вместимостью " << capacity << "\033[0m\n";
            break;
        }
        case 2: {
            /*Печать*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "\033[32m";
            array_print(arr, size);
            std::cout << "\nВместимость: " << capacity << "\tРазмер: " << size << "\033[0m\n";
            break;
        }
        case 3: {
            /*Вставка элемента*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "$ Введите позицию: ";
            int pos;
            if (!(std::cin >> pos) || pos < 0) {
                std::cout << "\033[31mНеверный ввод: Должно быть 0 <= pos <= size\033[0m\n";
                break;
            }
            clear_input();

            std::cout << "$ Введите значение: ";
            int value;
            if (!(std::cin >> value)) {
                std::cout << "\033[31mНеверный ввод: Значение должно быть типа Int\033[0m\n";
                break;
            }

            std::cout << "\033[32m" << "Массив: ";
            array_print(arr, size);
            std::cout << " -> " << "\033[0m";

            try {
                array_insert(arr, size, capacity, static_cast<std::size_t>(pos), value);
            } catch (const std::exception& e) {
                std::cout << "\033[31mОшибка вставки: " << e.what() << "\033[0m\n";
                break;
            }

            std::cout << "\033[32m";
            array_print(arr, size);
            std::cout << "\033[0m\n";
            break;
        }
        case 4: {
            /*удаление элемента*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "$ Введите позицию: ";
            int pos;
            if (!(std::cin >> pos) || pos < 0) {
                std::cout << "\033[31mНеверный ввод: Должно быть 0 <= pos < size)\033[0m\n";
                break;
            }

            std::cout << "\033[32m" << "Массив: ";
            array_print(arr, size);
            std::cout << " -> " << "\033[0m";

            try {
                array_remove(arr, size, static_cast<std::size_t>(pos));
            } catch (const std::exception& e) {
                std::cout << "\033[31mОшибка удаления: " << e.what() << "\033[0m\n";
                break;
            }

            std::cout << "\033[32m";
            array_print(arr, size);
            std::cout << "\033[0m\n";
            break;
        }
        case 5: {
            /*resize*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "$ Введите новую вместимость массива: ";

            int cap;
            if (!(std::cin >> cap) || cap < 0) {
                std::cout << "\033[31mНеверный ввод (Должно быть: new_capacity >= 0)\033[0m\n";
                break;
            }

            try {
                arr = array_resize(arr, size, capacity, static_cast<std::size_t>(cap));
            } catch (const std::exception& e) {
                std::cout << "\033[31mОшибка resize: " << e.what() << "\033[0m\n";
                break;
            }

            std::cout << "\033[32m" << "Вместимость массива изменена на  " << capacity << "\033[0m\n";
            break;
        }
        case 6: {
            /*Удаление массива*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            array_delete(arr);
            size = 0;
            capacity = 0;
            std::cout << "\033[32m" << "Массив удален\033[0m\n";
            break;
        }
        case 7: {
            /*сортировка выбором*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "\033[32m" << "Массив: ";
            array_print(arr, size);
            std::cout << " -> " << "\033[0m";

            selection_sort(arr, size);

            std::cout << "\033[32m";
            array_print(arr, size);
            std::cout << "\033[0m\n";
            break;
        }
        case 8: {
            /*Бинарный поиск*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "$ Введите значение: ";
            int value;
            if (!(std::cin >> value)) {
                std::cout << "\033[31mНеверный ввод: Значение должно быть типа Int\033[0m\n";
                break;
            }

            std::cout << "\033[32m" << "Сортирую массив \nМассив: ";
            array_print(arr, size);
            std::cout << " -> " << "\033[0m";

            selection_sort(arr, size);

            std::cout << "\033[32m";
            array_print(arr, size);
            std::cout << "\033[0m\n";

            std::size_t find_index;
            if (array_binary_search(arr, size, value, find_index))
                std::cout << "\033[32mЗначение " << value << " было найдено! index: "<< find_index << "\033[0m\n";
            else 
                std::cout << "\033[32mЗначение " << value << " не было найдено!\033[0m\n";
            break;
        }
        case 9: {
            /*Переворот массива*/
            if (arr == nullptr) {
                std::cout << "\033[31mСначала создайте массив\033[0m\n";
                break;
            }

            std::cout << "\033[32m" << "Массив: ";
            array_print(arr, size);
            std::cout << " -> " << "\033[0m";

            array_reverse(arr, size);

            std::cout << "\033[32m";
            array_print(arr, size);
            std::cout << "\033[0m\n";
            break;
        }
        default:
            std::cout << "\033[31mНеверный ввод\033[0m\n";
            break;
        }

    clear_input();
    }
}