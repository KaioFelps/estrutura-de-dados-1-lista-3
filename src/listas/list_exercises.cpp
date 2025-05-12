#include "list_exercises.h"

std::list<int> arr_to_list(const int* arr, size_t size)
{
    std::list<int> list_result;

    for (size_t i = 0; i < size; i++)
    {
        list_result.push_back(arr[i]);
    }

    return list_result;
}
