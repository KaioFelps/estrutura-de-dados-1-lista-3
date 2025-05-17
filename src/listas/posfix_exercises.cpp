#include "posfix_exercises.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <assert.h>

template <typename T>
struct operands {
    T left_operand;
    T right_operand;
};

template <typename T>
operands<T> extract_operands_from_stack(std::stack<T>& arguments_stack)
{
    auto right_operand = arguments_stack.top();
    arguments_stack.pop();

    auto left_operand = arguments_stack.top();
    arguments_stack.pop();

    return {
        .left_operand = left_operand,
        .right_operand = right_operand,
    };
}

std::vector<std::string> NaivePosfixCalculator::vectorize_expression(const std::string& expression) noexcept(false)
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

float NaivePosfixCalculator::calc_posfix(const std::string& expression) noexcept(false)
{
    const auto vectorized_expression = NaivePosfixCalculator::vectorize_expression(std::move(expression));
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

std::string NaivePosfixCalculator::into_infix(const std::string& posfix_expr) noexcept(false)
{
    const auto tokens = NaivePosfixCalculator::vectorize_expression(posfix_expr);

    auto operands_stack = std::stack<std::string>();

    auto number_buffer = std::string();

    for (char input : posfix_expr)
    {
        if (isdigit(input))
        {
            number_buffer.push_back(input);
            continue;
        }

        if (!number_buffer.empty())
        {
            operands_stack.push(number_buffer);
            number_buffer.clear();
        }

        switch (input)
        {
            case '+': case '-':
                NaivePosfixCalculator::prepare_infix_expr_with_precedence_as_operand(input, operands_stack);
                break;
            case '*': case '/':
                NaivePosfixCalculator::prepare_infix_expr_as_operand(input, operands_stack);
                break;
        }
    }

    assert(operands_stack.size() == 1 && "Posfix translation should result in a stack with a single whole infix expression.");
    return operands_stack.top();
}

std::string get_infix_expr(
    char _operator,
    std::stack<std::string>& operands,
    bool surround_with_parentheses = false
)
{
    assert(operands.size() >= 2 && "Program allowed operator to be called with less than 2 operands on the stack, but this should be forbidden");

    auto [left_operand, right_operand] = extract_operands_from_stack(operands);

    auto expr = std::stringstream();

    if (surround_with_parentheses) expr << '(';
    expr
        << left_operand
        << ' '
        << _operator
        << ' '
        << right_operand;
    if (surround_with_parentheses) expr << ')';

    return expr.str();
}

void NaivePosfixCalculator::prepare_infix_expr_with_precedence_as_operand(
    char _operator,
    std::stack<std::string>& operands
) noexcept
{
    operands.push(get_infix_expr(_operator, operands, true));
}

void NaivePosfixCalculator::prepare_infix_expr_as_operand(
    char _operator,
    std::stack<std::string>& operands
) noexcept
{
    operands.push(get_infix_expr(_operator, operands));
}

void NaivePosfixCalculator::check_posfix(const std::vector<std::string>& expression) noexcept(false)
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
