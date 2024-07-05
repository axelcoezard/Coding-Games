#include <iostream>
#include <string>

int main()
{
    while (true)
    {
        std::string enemy_1, enemy_2;
        uint32_t dist_1, dist_2;

        std::cin >> enemy_1 >> dist_1 >> enemy_2 >> dist_2;
        std::cin.ignore();

        std::cout << (dist_1 < dist_2 ? enemy_1 : enemy_2) << std::endl;
    }
}