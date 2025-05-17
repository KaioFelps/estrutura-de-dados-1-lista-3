#include "infix_exercises.h"
#include "check_brackets.h"
#include <stdexcept>
#include <sstream>
#include <assert.h>

float NaiveInfixCalculator::calc_infix(const std::string expression) noexcept(false)
{
    if (!check_brackets(expression)) throw std::invalid_argument("Expression has inconsistent parentheses order.");

    std::stack<char> operators_stack;
    std::stack<float> operands_stack;

    auto number_buffer = std::string();

    for (char input : expression)
    {
        NaiveInfixCalculator::handle_input(input, operators_stack, operands_stack, number_buffer);
    }

    while (!operators_stack.empty() && operands_stack.size() >= 2)
    {
        if (operators_stack.top() == (char) Signals::OPENING) break;
        solve_top_operation(operators_stack, operands_stack);
        operators_stack.pop();
    }

    return operands_stack.empty()
        ? .0f
        : operands_stack.top();
}

void NaiveInfixCalculator::handle_input(
    char input,
    OPERATORS,
    OPERANDS,
    std::string& number_buffer
) noexcept(false)
{
    if (isdigit(input))
    {
        number_buffer.push_back(input);
        return;
    }

    if (!number_buffer.empty())
    {
        operands_stack.push(std::stof(number_buffer));
        number_buffer.clear();
    }

    switch (input)
    {
        case (char) Signals::OPENING: operators_stack.push((char)Signals::OPENING); break;
        case (char) Signals::CLOSING: solve_top_operation(operators_stack, operands_stack); break;
        case '+': case '-': if (!operators_stack.empty() && operators_stack.top() != (char) Signals::OPENING)
            {
                solve_top_operation(operators_stack, operands_stack);
            }
        case '*': case '/': operators_stack.push(input); break;
    }
}

void NaiveInfixCalculator::solve_top_operation(
    OPERATORS,
    OPERANDS
) noexcept(false)
{
    if (operands_stack.size() < 2)
    {
        auto err_msg = std::stringstream();
        err_msg
            << "Given infix expression if mal-formed. Found less than two operands to perform the \""
            << operators_stack.top()
            << "\" operation. Current amount of operands is "
            << operands_stack.size()
            << ".";

        throw std::invalid_argument(err_msg.str());
    }

    const auto right_argument = operands_stack.top();
    operands_stack.pop();

    const auto left_argument = operands_stack.top();
    operands_stack.pop();

    const auto operation = operators_stack.top();
    operators_stack.pop();
    
    assert(operation != (char) Signals::OPENING && "Program tried to solve top operation but it's an opening signal.");

    if (operators_stack.top() == (char) Signals::OPENING) operators_stack.pop();

    auto result = handle_operation(right_argument, left_argument, operation);
    operands_stack.push(result);
}

float NaiveInfixCalculator::handle_operation(float right_argument, float left_argument, char operation)
{
    switch(operation)
    {
        case '+': return left_argument + right_argument;
        case '-': return left_argument - right_argument;
        case '*': return left_argument * right_argument;
        case '/': return left_argument / right_argument;
    }

    auto panic_msg = std::stringstream();
    panic_msg << "Program allowed an invalid operator to join the operators stack: " << operation;

    assert(false && panic_msg);
}
