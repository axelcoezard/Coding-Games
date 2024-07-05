#include <iostream>
#include <string>

int main()
{
    while (true)
    {
        uint32_t maxHeight = 0, maxIndex = 0;
        
        for (int i = 0; i < 8; i++)
        {
            int height; // represents the height of one mountain.
            std::cin >> height; std::cin.ignore();

            if (height > maxHeight)
                maxHeight = height, maxIndex = i;
        }

        std::cout << maxIndex << std::endl; // The index of the mountain to fire on.
    }
}