#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Coin
{
    uint32_t count;
    uint32_t value;
};

static uint32_t ParseInteger()
{
    uint32_t value;
    std::cin >> value; std::cin.ignore();
    return value;
}

static int32_t CalculateResult(const uint32_t valueToReach, const std::vector<Coin>& coins)
{
    uint32_t countReached = 0;
    uint32_t valueReached = 0;

    for (const Coin& coin : coins)
    {
        uint32_t countNeeded = std::ceil((valueToReach - valueReached) / (double) coin.value);
        uint32_t count = std::min(coin.count, countNeeded);

        countReached += count;
        valueReached += count * coin.value;

        if (valueReached >= valueToReach)
            return countReached;
    }
    return -1;
}

int main()
{
    uint32_t valueToReach = ParseInteger();
    uint32_t N = ParseInteger();

    std::vector<uint32_t> counts, values;
    std::vector<Coin> coins;

    for (uint32_t i = 0; i < N; i++)
        counts.push_back(ParseInteger());

    for (uint32_t i = 0; i < N; i++)
        values.push_back(ParseInteger());

    for (uint32_t i = 0; i < N; i++)
        coins.push_back({ counts.at(i), values.at(i) });

    std::sort(coins.begin(), coins.end(), [](const Coin& a, const Coin& b) -> bool {
        return b.value > a.value;
    });

    std::cout << CalculateResult(valueToReach, coins) << std::endl;
}