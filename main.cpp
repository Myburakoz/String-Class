#include <iostream>
#include "STR.h"
using namespace std;

int main()
{
    try
    {
        cout << boolalpha;

        Str s1;

        s1.push_back('a');

        cout << s1 << endl;

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}