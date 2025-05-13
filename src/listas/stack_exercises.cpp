#include "stack_exercises.h"

std::stack<int> arr_to_stack(const int* arr, size_t size)
{
    std::stack<int> stack;

    for (size_t i = 0; i < size; i++) stack.push(arr[i]);

    return stack;
}
