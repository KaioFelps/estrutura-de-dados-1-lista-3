#include "check_brackets.h"
#include <stack>

bool check_brackets(const std::string& expression)
{
    using namespace std;

    auto tracker = ParenthesesTracker();
    
    for (char character : expression)
    {
        auto as_parentheses = Parentheses::from_char(character);
        if (!as_parentheses.has_value()) continue;
        if (!tracker.receive_parentheses(as_parentheses.value())) return false;
    }
    
    return tracker.is_empty();
}

Parentheses::Parentheses(ParenthesesType type, ParenthesesMark mark) : type_(type), mark_(mark)
{
}

bool Parentheses::closes(const Parentheses& other) const
{
    if (this->mark_ == ParenthesesMark::OPENING) return false;
    if (this->type_ != other.type_) return false;

    return other.mark_ == ParenthesesMark::OPENING;
}

std::optional<Parentheses> Parentheses::from_char(char input)
{
    ParenthesesType type;
    ParenthesesMark mark;

    switch (input)
    {
        case '(': case ')': type = ParenthesesType::PARENTHESES; break;
        case '[': case ']': type = ParenthesesType::BRACKETS; break;
        case '{': case '}': type = ParenthesesType::CURLY_BRACKETS; break;
        default: return std::nullopt;
    }

    switch (input)
    {
        case '(': case '[': case '{': mark = ParenthesesMark::OPENING; break;
        case ')': case ']': case '}': mark = ParenthesesMark::CLOSING; break;
        default: return std::nullopt;
    }

    return Parentheses(type, mark);
}

bool Parentheses::is_opening() const
{
    return this->mark_ == ParenthesesMark::OPENING;
}

bool Parentheses::is_closing() const
{
    return !this->is_opening();
}

ParenthesesTracker::ParenthesesTracker() : stack_(std::stack<Parentheses>())
{
}

bool ParenthesesTracker::receive_parentheses(Parentheses parentheses)
{
    if (this->stack_.empty() && parentheses.is_closing()) return false;

    if (parentheses.is_opening())
    {
        this->stack_.push(parentheses);
        return true;
    }

    const auto& top = this->stack_.top();

    if (parentheses.closes(top))
    {
        this->stack_.pop();
        return true;
    }

    return false;
}

bool ParenthesesTracker::is_empty() const
{
    return this->stack_.empty();
}
