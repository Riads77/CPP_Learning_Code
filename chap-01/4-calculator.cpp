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

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Expected operator as first argument." << std::endl;
        return -1;
    }

    std::string op = argv[1];

    if (op != "+" && op != "*" && op != "-")
    {
        std::cerr << "Expected operator to be '+', '*' or '-'." << std::endl;
        return -1;
    }

    std::vector<int> values;
    for (auto arg_i = 2; arg_i < argc; ++arg_i)
    {
        auto value = std::stoi(argv[arg_i]);
        values.emplace_back(value);
    }

    if (op == "-" && values.empty())
    {
        std::cerr << "Operator '-' expects at least one operand to substract from." << std::endl;
        return -1;
    }

    auto result = compute_result(op[0], values);

    display_result(result);

    return 0;
}
