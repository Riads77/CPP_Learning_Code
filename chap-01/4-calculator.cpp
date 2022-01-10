#include <iostream>
#include <string>
#include <vector>

void display_result(int result)
{
    std::cout << "Result is " << result << std::endl;
}

int compute_result(char op, std::vector<int> values)
{
    auto result = 0;

    if (op == '+')
    {
        for (auto v : values)
        {
            result += v;
        }
    }
    else if (op == '*')
    {
        result = 1;
        for (auto v : values)
        {
            result *= v;
        }
    }
    else if (op == '-')
    {
        result = values[0];
        for (auto i = 1u; i < values.size(); ++i)
        {
            result -= values[i];
        }
    }
    return result;
}

bool parse_params(char op, std::vector<int> values, int arg, char** argv)
{
    if (arg < 2)
    {
        std::cerr << "Expected operator as first argument." << std::endl;
        return false;
    }

    std::string op_str = argv[1];

    if (op_str != "+" && op_str != "*" && op_str != "-")
    {
        std::cerr << "Expected operator to be '+', '*' or '-'." << std::endl;
        return false;
    }

    op = op_str[0];

    for (auto arg_i = 2; arg_i < arg; ++arg_i)
    {
        auto value = std::stoi(argv[arg_i]);
        values.emplace_back(value);
    }

    if (op == '-' && values.empty())
    {
        std::cerr << "Operator '-' expects at least one _op_strerand to substract from." << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    char             op = '?';
    std::vector<int> values;

    if (!parse_params(op, values, argc, argv))
    {
        return -1;
    }

    auto result = compute_result(op, values);

    display_result(result);

    return 0;
}
