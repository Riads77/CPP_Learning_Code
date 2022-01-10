#include <iostream>

int main() {
    int array[50] = {};

    for (int i = 0; i < 50; ++i)
    { array[i] = i + 1; }

    for (int value : array)
    { std::cout << value << std::endl; }

    return 0;
}
