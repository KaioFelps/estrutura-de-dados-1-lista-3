#include <vector>
#include <string>
#include <optional>

class NaivePosfixCalculator
{
    public:
        NaivePosfixCalculator() = default;
        float calc_posfix(std::string expression) const noexcept(false);
        static std::vector<std::string> vectorize_expression(std::string expression) noexcept(false);

    private:
        static void check_posfix(std::vector<std::string>& expression) noexcept(false);
};
