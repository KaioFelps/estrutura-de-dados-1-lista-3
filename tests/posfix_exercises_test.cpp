#include "posfix_exercises.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Test NaivePosfixCalculator", "[NaivePosfixCalculator::calc_posfix, NaivePosfixCalculator::vectorize_expression]")
{
    auto calculator = NaivePosfixCalculator();

    REQUIRE(233 == calculator.calc_posfix("24 32 + 2 / 41 5 * +"));
    CHECK_THROWS(calculator.vectorize_expression("123 a"));
}
