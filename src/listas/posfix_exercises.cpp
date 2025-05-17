#include "posfix_exercises.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <stack>

#include <iostream>

typedef struct operands_t{
    float left_operand;
    float right_operand;
} Operands;

Operands extract_operands_from_stack(std::stack<float>& arguments_stack)
{
    auto right_operand = arguments_stack.top();
    arguments_stack.pop();
    auto left_operand = arguments_stack.top();
    arguments_stack.pop();

    return Operands {
        .left_operand = left_operand,
        .right_operand = right_operand,
    };
}

std::vector<std::string> NaivePosfixCalculator::vectorize_expression(std::string expression) noexcept(false)
{
    auto arguments = std::vector<std::string>();
    auto buffer = std::string();

    for (char digit : expression)
    {
        if (digit == ' ')
        {
            if (!buffer.empty()) arguments.push_back(buffer);
            buffer.clear();
            continue;
        }

        buffer.push_back(digit);
    }

    if (!buffer.empty()) arguments.push_back(buffer);

    NaivePosfixCalculator::check_posfix(arguments);

    return arguments;
}

float NaivePosfixCalculator::calc_posfix(std::string expression) const noexcept(false)
{
    const auto vectorized_expression = this->vectorize_expression(std::move(expression));
    auto arguments_stack = std::stack<float>();

    for (const auto& input : vectorized_expression)
    {
        if (isdigit(input[0]))
        {
            arguments_stack.push(std::stoi(input));
            continue;
        }

        if (arguments_stack.size() < 2)
        {
            throw std::invalid_argument("Tried to perform an operation but not enough operands has been input.");
        }

        auto [left_operand, right_operand] = extract_operands_from_stack(arguments_stack);

        switch(input[0])
        {
            case '+': arguments_stack.push(left_operand + right_operand); break;
            case '-': arguments_stack.push(left_operand - right_operand); break;
            case '*': arguments_stack.push(left_operand * right_operand); break;
            case '/': arguments_stack.push(left_operand / right_operand); break;
        }
    }

    return arguments_stack.empty()
        ? 0.0f
        : arguments_stack.top();
}

void NaivePosfixCalculator::check_posfix(std::vector<std::string>& expression) noexcept(false)
{
    const size_t size = 4;
    const char valid_inputs[size] = {'/', '+', '*', '-'};

    int digits_count = 0;

    for (auto& input : expression)
    {
        if (isdigit(input[0]))
        {
            digits_count++;
            continue;
        }

        auto input_as_operand = input[0];
        auto input_is_operand = std::find(valid_inputs, valid_inputs + size, input_as_operand) != valid_inputs + size;
        if (!input_is_operand)
        {
            auto err_msg = std::stringstream();
            err_msg << "Posfix expressions should only contain numbers and one of the operators '/', '+', '-' or '*', but found " << input << ".";
            throw std::invalid_argument(err_msg.str());
        }

        digits_count--;

        if (digits_count < 0)
        {
            throw std::invalid_argument("Posfix expression tries to execute operations without any operand left.");
        }
    }

    if (digits_count != 1)
    {
        auto err_msg = std::stringstream();
        err_msg << "Posfix expressions should evaluate to exactly one value as result, but given expression finished with " << digits_count << " numbers on the stack.";
        throw std::invalid_argument(err_msg.str());
    }
}
