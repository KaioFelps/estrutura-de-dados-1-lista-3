#include <catch2/catch_all.hpp>
#include "list_exercises.h"

TEST_CASE("List exercises", "[arr_to_list]")
{
    const int size = 8;
    int c_array[size] = {54, 3, 5, 67, 93, 905, 71, -493};

    auto generated_list = arr_to_list(c_array, size);

    for (auto it = generated_list.begin(); it != generated_list.end(); it++)
    {
        auto index = std::distance(generated_list.begin(), it);
        REQUIRE(c_array[index] == *it);
    }
}
