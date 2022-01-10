#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2)
    {
        std::cerr << "Must have at least one argument." << std::endl;
        return -1;
    }

    int length = std::stoi(argv[1]);
    if (length <= 0)
    {
        std::cerr << "Expected strictly positive value for array size." << std::endl;
        return -1;
    }

    std::cout << length << std::endl;

    // int array[50] = {};

    // for (int i = 0; i < 50; ++i)
    // { array[i] = i + 1; }

    // for (int value : array)
    // { std::cout << value << std::endl; }

    return 0;
}
