#include "Histogram.h"

#include <iostream>
#include <vector>

Histogram::Histogram()
{}

Histogram::Histogram(const Histogram& other)
    : _count { other._count }
{}

Histogram::~Histogram()
{}

void Histogram::analyze(const std::string& s)
{
    using namespace std;

    for (int i = 0; i < (int)s.size(); i++)
    {
        char c = s[i];
        if (islower(c))
        {
            _count[c - 'a']++;
        }
    }
}

void Histogram::print() const
{
    for (auto c = 'a'; 'c' <= 'z'; ++c)
    {
        std::cout << c << " : " << _count[c - 'a'] << std::endl;
    }
}