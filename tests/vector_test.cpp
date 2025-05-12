#include <catch2/catch_all.hpp> 
#include "vector_exercises.h"

TEST_CASE("Vector exercises", "[arr_to_vector, list_concat]")
{
    SECTION("`arr_to_vector` should return a new vector containing all items from c array")
    {
        const int size = 8;
        int c_array[size] = {54, 3, 5, 67, 93, 905, 71, -493};

        auto vec = arr_to_vector(c_array, size);

        for (int i = 0; i < size; i++) REQUIRE(vec.at(i) == c_array[i]);
    }

    SECTION("`list_concat` should return a new vector containing items from two lists")
    {
        using namespace std;
        list<int> first = list<int>({10, 540, 288, -459});
        list<int> second = list<int>({29, 49, 85, -394, 578});

        auto concatenation_vec = list_concat(first, second);

        REQUIRE(concatenation_vec.size() == first.size() + second.size());

        size_t i = 0;
        for (; i < first.size(); i++)
        {
            auto iterator = first.begin();
            std::advance(iterator, i);
            REQUIRE(concatenation_vec.at(i) == *iterator);
        }

        for (size_t j = 0; j < second.size(); j++)
        {
            auto iterator = second.begin();
            std::advance(iterator, j);
            REQUIRE(concatenation_vec.at(i + j) == *iterator);
        }
    }
}
