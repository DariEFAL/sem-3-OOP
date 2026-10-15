#include <iostream>
#include <stdexcept>
#include "array_ops.h"

void selection_sort(int* arr, std::size_t size) {
    //сортировка выбором
    for (std::size_t i = 0; i + 1 < size; i++) {
        std::size_t min_index = i;

        for (std::size_t j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        std::swap(arr[i], arr[min_index]);
    }
}

bool array_binary_search(const int* arr, std::size_t size, int value, std::size_t& out_index) {
    std::size_t left = 0;
    std::size_t right = size;
    std::size_t p;

    while (left < right) {
        p = left + (right - left) / 2;

        if (value == arr[p]) {
            out_index = p;
            return true;
        }
        if (value < arr[p]) right = p;
        else left = p + 1;
    }

    return false;
}

void array_reverse(int* arr, size_t size) {
    for (std::size_t i = 0; i < size / 2; i++) {
        std::swap(arr[i], arr[size - i - 1]);
    }
}