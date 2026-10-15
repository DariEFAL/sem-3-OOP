#include <iostream>
#include <stdexcept>
#include "array_ops.h"

int* array_create(std::size_t capacity) {
    return new int[capacity];
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t& capacity, std::size_t new_capacity) {
    if (new_capacity < size) throw std::logic_error("new_capacity < size");
    
    int* new_arr = array_create(new_capacity);

    for (std::size_t i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    capacity = new_capacity;

    array_delete(arr);
    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t capacity, std::size_t pos, int value) {
    if (pos > size) throw std::out_of_range("pos is out of range; valid range is [0, size]");
    if (capacity == size) throw std::length_error("capacity is exhausted");

    for (std::size_t i = size; i > pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos] = value;
    size++;

    return arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (pos >= size) throw std::out_of_range("pos is out of range; valid range is [0, size]");
    
    for (std::size_t i = pos; i < size; i++) {
        arr[i] = arr[i+1];
    }
    size--;

    return arr;
}

void array_print(const int* arr, std::size_t size) {
    std::cout << "{ ";
    for (std::size_t i = 0; i < size; i++) {
        if (i == size - 1) std::cout << arr[i];
        else std::cout << arr[i] << ", ";
    }
    std::cout << " }";
}

