#include "posfix_exercises.h"
#include "infix_exercises.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Test NaivePosfixCalculator", "[NaivePosfixCalculator::calc_posfix, NaivePosfixCalculator::vectorize_expression]")
{
    REQUIRE(233 == NaivePosfixCalculator::calc_posfix("24 32 + 2 / 41 5 * +"));
    CHECK_THROWS(NaivePosfixCalculator::vectorize_expression("123 a"));
}

TEST_CASE("It should convert a valid posfix expression to a infix one", "[NaivePosfixCalculator::]")
{
    const auto posfix_expr = std::string("6 9 + 3 / 6 4 - *");
    const auto infix_translated_expr = NaivePosfixCalculator::into_infix(posfix_expr);

    REQUIRE("(6 + 9) / 3 * (6 - 4)" == infix_translated_expr);
    REQUIRE(NaiveInfixCalculator::calc_infix(infix_translated_expr) == NaivePosfixCalculator::calc_posfix(posfix_expr));
}
