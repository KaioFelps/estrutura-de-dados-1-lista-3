#include "check_brackets.h"
#include <catch2/catch_all.hpp>

TEST_CASE("It should differ valid parentheses orders from correct ones", "[check_bracket]")
{
    SECTION("Correct opening-closing parentheses should be truthy")
    {
        REQUIRE(check_brackets("(a + b)"));
        REQUIRE(check_brackets("[x * (y + z)]"));
        REQUIRE(check_brackets("{if (a > b) [return x];}"));
        REQUIRE(check_brackets("([valor])"));
        REQUIRE(check_brackets("{[()]}"));
        REQUIRE(check_brackets("((numero + 3) * (outro_valor - 2))"));
        REQUIRE(check_brackets("[({soma(a, b)})]"));
        REQUIRE(check_brackets("(x)[y]{z}"));
        REQUIRE(check_brackets("{([x] + {y})}"));
        REQUIRE(check_brackets("(([[{{valid}}]]))"));
    }

    SECTION("Closing parenthesis which haven't been opened should return falsy")
    {
        REQUIRE(!check_brackets("texto)"));
        REQUIRE(!check_brackets("[(x + y]"));
        REQUIRE(!check_brackets("{return (x + 2];}"));
        REQUIRE(!check_brackets("if (a > b] return a;"));
        REQUIRE(!check_brackets("{(x * y) + 2})"));
        REQUIRE(!check_brackets("([nome] + idade}"));
    }

    SECTION("Incorrect order of parentheses closings should make it return falsy")
    {
        REQUIRE(!check_brackets("(a + b]"));
        REQUIRE(!check_brackets("[func(x))]"));
        REQUIRE(!check_brackets("{[2 + 3)]}"));
        REQUIRE(!check_brackets("({texto[123}])"));
        REQUIRE(!check_brackets("[{(valor})]"));
    }

    SECTION("Parentheses without closings should be falsy")
    {
        REQUIRE(!check_brackets("(incompleto"));
        REQUIRE(!check_brackets("[sem_fecho"));
        REQUIRE(!check_brackets("{a + (b * c)"));
        REQUIRE(!check_brackets("((nivel1) + (nivel2)"));
        REQUIRE(!check_brackets("[{(x + y)}"));
        REQUIRE(!check_brackets("{{[x + y * (z]}"));
    }
}
