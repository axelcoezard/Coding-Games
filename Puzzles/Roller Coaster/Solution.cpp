#include <iostream>
#include <string>
#include <queue>

constexpr const uint8_t RIDE_PRICE = 1; // Each person spends 1 dirham per ride

static uint64_t CaculateEarnings(uint32_t& maxRidesCount, const uint32_t& maxPlacesCount, std::queue<uint64_t>& groups)
{
    uint64_t earnedDirhams = 0;

    while (maxRidesCount > 0)
    {
        uint32_t remainingPlacesForThisRide = maxPlacesCount;
        uint32_t groupsToCheck = groups.size();

        while (groupsToCheck >= 1 && remainingPlacesForThisRide >= 1)
        {
            uint64_t places = groups.front();
            if (places > remainingPlacesForThisRide)
                break;

            groups.pop();
            groups.push(places);

            remainingPlacesForThisRide -= places;
            earnedDirhams += places * RIDE_PRICE;

            groupsToCheck--;
        } 

        maxRidesCount--;
    }

    return earnedDirhams;
}

int main()
{
    std::queue<uint64_t> groups;

    uint32_t maxPlacesCount; // The attraction contains a limited number L of places.
    uint32_t maxRidesCount; // The attraction can only function C number of times per day.
    uint32_t groupsCount; //  The queue contains a number N of groups.

    std::cin >> maxPlacesCount >> maxRidesCount >> groupsCount;
    std::cin.ignore();

    while (groupsCount > 0)
    {
        uint32_t pi;
        std::cin >> pi; std::cin.ignore();

        groups.push(pi);
        groupsCount--;
    }

    std::cout << CaculateEarnings(maxRidesCount, maxPlacesCount, groups) << std::endl;
}