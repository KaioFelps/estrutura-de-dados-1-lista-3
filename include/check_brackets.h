#pragma once

#include <string>
#include <optional>
#include <stack>

enum class ParenthesesType
{
    PARENTHESES,
    BRACKETS,
    CURLY_BRACKETS
};

enum class ParenthesesMark
{
    OPENING,
    CLOSING
};

class Parentheses
{
    public:
        bool closes(const Parentheses& other) const;
        static std::optional<Parentheses> from_char(char input);
        bool is_opening() const;
        bool is_closing() const;
    
    private:
        Parentheses(ParenthesesType type, ParenthesesMark mark);
        ParenthesesType type_;
        ParenthesesMark mark_;
};

class ParenthesesTracker
{
    public:
        ParenthesesTracker();

        bool receive_parentheses(Parentheses parentheses);
        bool is_empty() const;

    private:
        std::stack<Parentheses> stack_;
};

/// @brief Checa se a (ordem da) parentização da expressão passada na string está correta.
/// @param expression 
/// @return `true` se e somente se todos os parenteses abertos fecham na ordem correta. `false` caso contrário.
/// @example
/// ```cpp
/// REQUIRE(check_brackets("[(x + 8) * (9-2)]"));
/// REQUIRE(!check_brackets("[(x + 8) * (9-2])"));
/// ```
bool check_brackets(const std::string& expression);
