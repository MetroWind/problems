#include <iostream>
#include <string>

using namespace std;

int ways(string code)
{
    auto Size = code.size();
    if(Size == 0)
    {
        return 1;
    }

    if(code[0] == '0')
    {
        return 0;
    }

    size_t Ways = 0;

    if(code[0] == '1')
    {
        Ways += ways(code.substr(1));
        if(Size > 1)
        {
            Ways += ways(code.substr(2));
        }
    }
    else if(code[0] == '2')
    {
        Ways += ways(code.substr(1));
        if(Size > 1 && code[1] <= '6')
        {
            Ways += ways(code.substr(2));
        }
    }
    else
    {
        Ways += ways(code.substr(1));
    }
    return Ways;
}

int waysFast(string code)
{
    size_t Ways = 1, Prev = 1;
    auto Size = code.size();
    if(Size == 0)
    {
        return 0;
    }
    if(code[0] == '0')
        return 0;
    for(auto i = Size; i --> 1 ;)
    {
        if(code[i] == '0')
        {
            if(code[i-1] == '1' || (code[i-1] == '2' and code[i] <= '6'))
            {
                i--;
            }
            else
            {
                return 0;
            }
        }
        else if(code[i-1] == '1' || (code[i-1] == '2' and code[i] <= '6'))
        {
            // Think about why "1212" should return 5, and you'll
            // understand.
            Ways += Prev;
            Prev = Ways - Prev;
        }
        else
        {
            Prev = Ways;
        }
    }
    return Ways;
}

int main()
{
    std::cout << waysFast("1") << std::endl;
}
