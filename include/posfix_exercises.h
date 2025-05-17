#pragma once

#include <vector>
#include <string>
#include <stack>
#include <optional>

class NaivePosfixCalculator
{
    public:
        static float calc_posfix(const std::string& expression) noexcept(false);
        static std::string into_infix(const std::string& posfix_expr) noexcept(false);

        static std::vector<std::string> vectorize_expression(const std::string& expression) noexcept(false);

    private:
        static void check_posfix(const std::vector<std::string>& expression) noexcept(false);

        static void prepare_infix_expr_with_precedence_as_operand(
            char _operator,
            std::stack<std::string>& operands
        ) noexcept;

        static void prepare_infix_expr_as_operand(
            char _operator,
            std::stack<std::string>& operands
        ) noexcept;
};
