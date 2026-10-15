#pragma once

#include <cstddef> //для std::size_t

int* array_create(std::size_t capacity);
void array_delete(int*& arr);
int* array_resize(int* arr, std::size_t size, std::size_t& capacity, std::size_t new_capacity);
int* array_insert(int* arr, std::size_t& size, std::size_t capacity, std::size_t pos, int value);
int* array_remove(int* arr, std::size_t& size, std::size_t pos);
void array_print(const int* arr, std::size_t size);

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index);
void array_reverse(int* arr, size_t size); 