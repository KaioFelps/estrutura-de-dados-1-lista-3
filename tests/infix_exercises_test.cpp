#include "infix_exercises.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Test NaiveInfixCalculator", "[NaiveInfixCalculator::calc_infix]")
{
    REQUIRE(33 == NaiveInfixCalculator::calc_infix("5 + ( 6 * ( 2 + 3 ) - ( 4 / 2 ) )"));
    REQUIRE(33 == NaiveInfixCalculator::calc_infix("5+(6*(2+3)-(4/2))"));

    REQUIRE(10 == NaiveInfixCalculator::calc_infix("( ( ( 6 + 9 ) / 3 ) * ( 6 - 4))"));
    REQUIRE(10 == NaiveInfixCalculator::calc_infix("((6+9) / 3) * (6 - 4)"));
    CHECK_THROWS(NaiveInfixCalculator::calc_infix("((6+9) / 3) * (6 - 4"), "Missing a trailling parentheses");
}
