#include <iostream>
int main() {
    int number = 0;
    while (true)
    {
        std::cin >> number;
        std::cout << number << std::endl;
        if (number == -1)
        { break; }
    }
    return 0;
}