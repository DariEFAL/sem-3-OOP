#include <gtest/gtest.h>
#include <stdexcept>
#include "array_ops.h"

TEST(ArrayCreate, ReturnsNonNullForPositiveSize) {
    int* arr = array_create(5);
    EXPECT_NE(arr, nullptr);
    array_delete(arr);
}

TEST(ArrayCreate, HandlesZeroSize) {
    int* arr = array_create(0);
    EXPECT_NE(arr, nullptr);
    array_delete(arr);
}

TEST(ArrayDelete, NullsOutPointer) {
    int* arr = array_create(5);
    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayDelete, HandlesNullptr) {
    int* arr = nullptr;
    array_delete(arr);          // не должно упасть
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayInsert, GoodInserts) {
    std::size_t size = 3;
    std::size_t capacity = 10;
    int* arr = nullptr;
    arr = array_create(capacity);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    array_insert(arr, size, capacity, 1, 99);

    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 3);
    array_delete(arr);
}

TEST(ArrayInsert, ThrowsWhenPosOutOfRange) {
    std::size_t size = 3;
    std::size_t capacity = 10;
    int* arr = array_create(capacity);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    EXPECT_THROW(
        array_insert(arr, size, capacity, 5, 99),
        std::out_of_range
    );

    array_delete(arr);
}

TEST(ArrayInsert, ThrowsWhenCapacityIsExhausted) {
    std::size_t size = 3;
    std::size_t capacity = 3;
    int* arr = array_create(capacity);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    EXPECT_THROW(
        array_insert(arr, size, capacity, 2, 99),
        std::length_error
    );

    array_delete(arr);
}

TEST(ArrayRemove, GoodRemoves) {
    std::size_t size = 5;
    int* arr = array_create(5);
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4; arr[4] = 5;

    array_remove(arr, size, 2);

    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 5);

    array_remove(arr, size, 0);

    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 5);

    array_remove(arr, size, size - 1);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 4);

    array_remove(arr, size, size - 1);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 2);

    array_remove(arr, size, size - 1);
    EXPECT_EQ(size, 0);

    array_delete(arr);
}

TEST(ArrayRemove, ThrowsWhenPosEqualsSize) {
    std::size_t size = 3;
    int* arr = array_create(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    EXPECT_THROW(array_remove(arr, size, 3), std::out_of_range);

    array_delete(arr);
}

TEST(ArrayRemove, ThrowsWhenPosGreaterThanSize) {
    std::size_t size = 3;
    int* arr = array_create(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    EXPECT_THROW(array_remove(arr, size, 5), std::out_of_range);

    array_delete(arr);
}

TEST(ArrayRemove, ThrowsOnEmptyArray) {
    std::size_t size = 0;
    int* arr = array_create(3);

    EXPECT_THROW(array_remove(arr, size, 0), std::out_of_range);

    array_delete(arr);
}

TEST(ArrayResize, ExpandsCapacity) {
    std::size_t size = 3;
    std::size_t capacity = 3;
    int* arr = array_create(capacity);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    arr = array_resize(arr, size, capacity, 10);

    EXPECT_EQ(capacity, 10);
    EXPECT_EQ(size, 3);            // size не меняется
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayResize, ResizeToSameSize) {
    std::size_t size = 3;
    std::size_t capacity = 5;
    int* arr = array_create(capacity);
    arr[0] = 10; arr[1] = 20; arr[2] = 30;

    arr = array_resize(arr, size, capacity, 5);

    EXPECT_EQ(capacity, 5);
    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    array_delete(arr);
}

TEST(ArrayResize, ResizeToZero) {
    std::size_t size = 0;
    std::size_t capacity = 5;
    int* arr = array_create(capacity);

    arr = array_resize(arr, size, capacity, 0);

    EXPECT_EQ(capacity, 0);
    EXPECT_EQ(size, 0);
    array_delete(arr);
}

TEST(ArrayResize, ResizeToSizeEqualToSize) {
    std::size_t size = 3;
    std::size_t capacity = 10;
    int* arr = array_create(capacity);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    arr = array_resize(arr, size, capacity, 3);

    EXPECT_EQ(capacity, 3);
    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(ArrayResize, ThrowsWhenNewCapacityLessThanSize) {
    std::size_t size = 5;
    std::size_t capacity = 10;
    int* arr = array_create(capacity);
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4; arr[4] = 5;

    EXPECT_THROW(
        array_resize(arr, size, capacity, 3),
        std::logic_error
    );

    array_delete(arr);
}