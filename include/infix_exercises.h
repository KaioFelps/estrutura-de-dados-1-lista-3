#pragma once

#include <vector>
#include <string>
#include <stack>

#define OPERATORS_ST std::stack<char>
#define OPERANDS_ST std::stack<float>

#define OPERATORS OPERATORS_ST& operators_stack
#define OPERANDS OPERANDS_ST& operands_stack

enum class Signals
{
    OPENING = '(',
    CLOSING = ')',
};

class NaiveInfixCalculator
{
    public:
        static float calc_infix(const std::string expression) noexcept(false);

    private:
        static void handle_input(char input, OPERATORS, OPERANDS, std::string& number_buffer) noexcept(false);
        static void solve_top_operation(OPERATORS, OPERANDS) noexcept(false);
        static float handle_operation(float right_argument, float left_argument, char operation);
};

