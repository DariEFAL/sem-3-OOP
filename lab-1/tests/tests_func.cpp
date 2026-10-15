#include <gtest/gtest.h>
#include <stdexcept>
#include "array_ops.h"

TEST(SelectionSort, GoodSorts) {
    int arr[] = {-5, 3, -1, 4, -2};
    selection_sort(arr, 5);

    EXPECT_EQ(arr[0], -5);
    EXPECT_EQ(arr[1], -2);
    EXPECT_EQ(arr[2], -1);
    EXPECT_EQ(arr[3], 3);
    EXPECT_EQ(arr[4], 4);
}

TEST(SelectionSort, HandlesSingleElement) {
    int arr[] = {42};
    selection_sort(arr, 1);
    EXPECT_EQ(arr[0], 42);
}

TEST(SelectionSort, HandlesEmptyArray) {
    int arr[] = {};
    selection_sort(arr, 0);
}

TEST(BinarySearch, FindsElementInMiddle) {
    int arr[] = {1, 3, 5, 7, 9};
    std::size_t index;

    bool found = array_binary_search(arr, 5, 5, index);

    EXPECT_TRUE(found);
    EXPECT_EQ(index, 2);
}

TEST(BinarySearch, ReturnsFalseForMissingElement) {
    int arr[] = {1, 3, 5, 7, 9};
    std::size_t index;

    bool found = array_binary_search(arr, 5, 4, index);

    EXPECT_FALSE(found);
}

TEST(BinarySearch, HandlesEmptyArray) {
    int arr[] = {};
    std::size_t index;

    bool found = array_binary_search(arr, 0, 5, index);

    EXPECT_FALSE(found);
}

TEST(ArrayReverse, ReversesEvenSizedArray) {
    int arr[] = {1, 2, 3, 4};
    array_reverse(arr, 4);

    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 1);
}

TEST(ArrayReverse, HandlesEmptyArray) {
    int arr[] = {};
    array_reverse(arr, 0);   // не должно упасть
}