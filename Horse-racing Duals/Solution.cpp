#include <iostream>
#include <limits>
#include <string>
#include <vector>

static int32_t ParseInt()
{
    int n;
    std::cin >> n;
    std::cin.ignore();
    return n;
}

int main()
{
    std::vector<int32_t> horsesStrength;
    uint32_t horsesCount = ParseInt();

    for (uint32_t i = 0; i < horsesCount; i++)
        horsesStrength.push_back(ParseInt());
    
    std::sort(horsesStrength.begin(), horsesStrength.end());

    uint32_t minDistance = std::numeric_limits<int32_t>::max();
    for (int i = 1; i < horsesCount; i++)
    {
        uint32_t distance = std::abs(horsesStrength.at(i) - horsesStrength.at(i - 1));
        if (distance < minDistance)
            minDistance = distance;
    }

    std::cout << minDistance << std::endl;
}