#include "vector_exercises.h"

std::vector<int> arr_to_vector(const int* arr, size_t size)
{
    using namespace std;

    vector<int> vec = vector<int>();
    vec.reserve(size);

    for (size_t i = 0; i < size; i++) vec.push_back(arr[i]);

    return vec;
}

std::vector<int> list_concat(const std::list<int>& first, const std::list<int>& second)
{
    using namespace std;

    auto vec = vector<int>();
    vec.reserve(first.size() + second.size());

    for (auto& item : first) vec.push_back(item);
    for (auto& item : second) vec.push_back(item);

    return vec;
}
