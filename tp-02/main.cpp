#include "Histogram.h"

#include <iostream>

int main()
{
    using namespace std;
    string    s;
    Histogram histogram;

    cin >> s;
    histogram.analyze(s);
    histogram.print();
}