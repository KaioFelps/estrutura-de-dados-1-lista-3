#include "stack_exercises.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Stack exercises", "[arr_to_stack]")
{
    const int size = 8;
    int c_array[size] = {54, 3, 5, 67, 93, 905, 71, -493};

    auto generated_stack = arr_to_stack(c_array, size);

    size_t index = size -1;
    while(generated_stack.size() > 0)
    {
        auto element = generated_stack.top();
        generated_stack.pop();
        auto arr_element = c_array[index--];

        REQUIRE(arr_element == element);
    }
}