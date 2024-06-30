#include <iostream>
#include <string>

int main()
{
    int surface_n;
    std::cin >> surface_n; std::cin.ignore();

    for (int i = 0; i < surface_n; i++)
    {
        int land_x, land_y;
        std::cin >> land_x >> land_y; std::cin.ignore();
    }

    while (true)
    {
        int16_t x, y, h_speed, v_speed, fuel, rotate, power;
        std::cin >> x >> y >> h_speed >> v_speed >> fuel >> rotate >> power; std::cin.ignore();

        uint8_t vFuel = std::abs(v_speed) >= 40 ? 4 : 0;

        std::cout << std::to_string(0) << " " << std::to_string(vFuel) << std::endl;
    }
}