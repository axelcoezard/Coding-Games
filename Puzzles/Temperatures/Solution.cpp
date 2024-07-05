#include <iostream>
#include <string>

int32_t ParseInteger()
{
    int32_t value;
    std::cin >> value; std::cin.ignore();
    return value;
}

int main()
{
    int32_t sampleCount = ParseInteger(); // the number of temperatures to analyse
    int32_t minTemperature = INT32_MAX;

    while (sampleCount--)
    {
        int32_t temperature = ParseInteger(); // a temperature expressed as an integer ranging from -273 to 5526
        int32_t distance = abs(minTemperature) - abs(temperature);

        if (distance > 0 || (distance == 0 && temperature > minTemperature))
            minTemperature = temperature;
    }

    std::cout << (minTemperature % INT32_MAX) << std::endl;
}