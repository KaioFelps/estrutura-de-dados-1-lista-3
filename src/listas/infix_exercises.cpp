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

    NaiveInfixCalculator::handle_operations_left(operators_stack, operands_stack);
    
    if (operands_stack.size() != 1)
    {
        auto err_msg = std::stringstream();
        err_msg
            << "Program should end with only one operand left (the result), but it has finished with "
            << operands_stack.size()
            << " operand(s) and "
            << operators_stack.size()
            << " operator(s) left:\n"
            << "Operators: ";
        
        while (!operators_stack.empty())
        {
            err_msg << operators_stack.top() << " ";
            operators_stack.pop();
        }

        err_msg << "\nOperands: ";
        while (!operands_stack.empty())
        {
            err_msg << operands_stack.top() << " ";
            operands_stack.pop();
        }
        
        throw std::runtime_error(err_msg.str());
    }

    return operands_stack.top();
}

void NaiveInfixCalculator::handle_operations_left(OPERATORS, OPERANDS)
{
    while(!operators_stack.empty() && operands_stack.size() > 1)
    {
        solve_top_operation(operators_stack, operands_stack, false);
    }
}

void NaiveInfixCalculator::handle_input(
    char input,
    OPERATORS,
    OPERANDS,
    std::string& number_buffer
) noexcept(false)
{
    if (input == ' ') return;

    if (isdigit(input))
    {
        number_buffer.push_back(input);
        return;
    }

    bool has_flushed_operand = false;

    if (!number_buffer.empty())
    {
        operands_stack.push(std::stof(number_buffer));
        number_buffer.clear();
        has_flushed_operand = true;
    }

    auto is_closing_signal = input == (char) Signals::CLOSING;
    auto has_completed_an_binary_operation =
        has_flushed_operand &&
        !operators_stack.empty() &&
        operators_stack.top() != (char) Signals::OPENING;

    if (is_closing_signal || has_completed_an_binary_operation)
    {
        solve_top_operation(operators_stack, operands_stack, is_closing_signal);
    }

    if (is_closing_signal) return;

    auto is_opening_signal = input == (char) Signals::OPENING;
    auto should_precede = NaiveInfixCalculator::operation_should_proceed(input, operators_stack);

    if (is_opening_signal || should_precede)
    {
        operators_stack.push(input);
        return;
    }

    solve_top_operation(operators_stack, operands_stack, false);
    operators_stack.push(input);
}

bool NaiveInfixCalculator::operation_should_proceed(char operation, OPERATORS)
{
    if (operation == '*' || operation == '/') return true;
    return operators_stack.empty() || operators_stack.top() == (char) Signals::OPENING;
}

void NaiveInfixCalculator::solve_top_operation(
    OPERATORS,
    OPERANDS,
    bool closes_a_parentheses = false
) noexcept(false)
{
    if (operators_stack.size() < 1)
    {
        auto err_msg = std::stringstream();
        err_msg
            << "Given infinx expression might be malformed. Found less than one operator,"
            << " so that its impossible to perform any operation";

        throw std::invalid_argument(err_msg.str());
    }
    
    if (operands_stack.size() < 2)
    {
        auto err_msg = std::stringstream();
        err_msg
            << "Given infix expression might be malformed. Found less than two operands to perform the \""
            << operators_stack.top()
            << "\" operation. Current amount of operands is "
            << operands_stack.size()
            << ".";

        throw std::invalid_argument(err_msg.str());
    }

    const auto operation = operators_stack.top();
    operators_stack.pop();

    // it means it's been already solved, so there's nothing left to do but remove the opening signal from the stack
    if (closes_a_parentheses && operation == (char) Signals::OPENING) return;

    // if it's not closing a parentheses but operation is a opening signal, it might be a bug which must be fixed
    assert(operation != (char) Signals::OPENING && "Program tried to solve top operation but it's an opening signal.");

    // if it has really closed a priority block, then solve the expression and remove opening signal which started
    // this priority block
    if (closes_a_parentheses && operators_stack.top() == (char) Signals::OPENING) operators_stack.pop();

    const auto right_argument = operands_stack.top();
    operands_stack.pop();

    const auto left_argument = operands_stack.top();
    operands_stack.pop();

    auto result = handle_operation(right_argument, left_argument, operation);
    operands_stack.push(result);
}

float NaiveInfixCalculator::handle_operation(float right_argument, float left_argument, char operation) noexcept(false)
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

    throw std::runtime_error(panic_msg.str());
}
