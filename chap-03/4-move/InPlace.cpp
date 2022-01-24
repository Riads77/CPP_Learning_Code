#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main()
{
    std::vector<std::string> many_strings;

    std::string value = "will I move?";

    std::cout << "value is '" << value << "'" << std::endl;

    many_strings.emplace_back(std::move(value));

    std::cout << "value is '" << value << "'" << std::endl;
    std::cout << "many_strings[0] is '" << many_strings[0] << "'" << std::endl;

    return 0;
}
