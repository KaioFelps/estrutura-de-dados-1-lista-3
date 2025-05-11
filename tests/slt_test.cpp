#include <iostream>
#include <sstream>
#include <catch2/catch_all.hpp> 

TEST_CASE("it should be able to execute")
{
    std::stringstream fake_buffer;

    auto cout_buffer = std::cout.rdbuf(fake_buffer.rdbuf());

    std::cout << "Hello World!";

    std::cout.rdbuf(cout_buffer);

    REQUIRE("Hello World!" == fake_buffer.str());
}
