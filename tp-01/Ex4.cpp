#include <iostream>
#include <vector>

std::vector<unsigned int> count_lower(const std::string& s)
{
    using namespace std;

    vector<unsigned int> counts(26);

    for (int i = 0; i < (int)s.size(); i++)
    {
        char c = s[i];
        if (islower(c))
        {
            counts.at(c - 'a')++;
        }
    }
    return counts;
}

void display_lower_occ(const std::vector<unsigned int>& counts)
{
    char c = 'a';
    for (auto value : counts)
    {
        std::cout << c << " : " << value << std::endl;
        c++;
    }
}

int main()
{
    using namespace std;
    string s;
    cin >> s;
    display_lower_occ(count_lower(s));
}