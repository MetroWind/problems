#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int& getMapSite(std::vector<int>& map, int row, int col, unsigned int size);
int str2Int(const std::string& s);

int main()
{
    unsigned int Size = 0;
    std::cin >> Size;
    std::vector<std::string> MapRaw(Size);
    for(auto i = 0; i < Size; i++)
    {
        std::cin >> MapRaw[i];
    }

    // Convert map strings to actual map.
    std::vector<int> Map(Size * Size); // Outter --> Inner: Row, Col.
    for(auto Row = 0; Row < Size; Row++)
    {
        for(auto Col = 0; Col < Size; Col++)
        {
            getMapSite(Map, Row, Col, Size) = str2Int(MapRaw[Row].substr(Col, 1));
            std::cout << getMapSite(Map, Row, Col, Size);
        }
        std::cout << std::endl;
    }

    return 0;
}

int& getMapSite(std::vector<int>& map, int row, int col, unsigned int size)
{
    return map[row * size + col];
}

int str2Int(const std::string& s)
{
    int numb;
    std::istringstream(s) >> numb;
    return numb;
}
