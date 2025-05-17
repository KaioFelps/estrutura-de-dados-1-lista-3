#pragma once

#include <vector>
#include <string>
#include <stack>
#include <optional>

class NaivePosfixCalculator
{
    public:
        NaivePosfixCalculator() = default;
        float calc_posfix(std::string expression) const noexcept(false);
        std::string into_infix(std::string posfix_expr) const noexcept(false);

        static std::vector<std::string> vectorize_expression(std::string expression) noexcept(false);

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
