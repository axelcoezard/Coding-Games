#include <iostream>
#include <string>

int main()
{
    uint32_t light_x; // the X position of the light of power
    uint32_t light_y; // the Y position of the light of power
    uint32_t initial_tx; // Thor's starting X position
    uint32_t initial_ty; // Thor's starting Y position

    std::cin >> light_x >> light_y >> initial_tx >> initial_ty;
    std::cin.ignore();

    uint32_t thor_x = initial_tx;
    uint32_t thor_y = initial_ty;

    // game loop
    while (true)
    {
        uint32_t remaining_turns; // The remaining amount of turns Thor can move. Do not remove this line.
        std::cin >> remaining_turns;
        std::cin.ignore();

        std::string directionX;
        if (thor_x > light_x)       thor_x--, directionX = 'W';
        else if (thor_x < light_x)  thor_x++, directionX = 'E';

        std::string directionY;
        if (thor_y > light_y)       thor_y--, directionY = 'N';
        else if (thor_y < light_y)  thor_y++, directionY = 'S';

        std::cout << directionY << directionX << std::endl;
    }
}