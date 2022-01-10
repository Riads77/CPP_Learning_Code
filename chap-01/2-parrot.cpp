#include <iostream>
int main() {
    int number = 0;
    do
    {
        std::cin >> number;
        std::cout << number << std::endl;
    } while (number != -1);
    return 0;
}