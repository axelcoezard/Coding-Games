#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <numbers>

#define RADIANS(degrees) (degrees * (std::numbers::pi / 180.0))

struct Defibrilator
{
    uint32_t id;
    std::string name;
    std::string address;
    std::string phone;
    double longitude;
    double latitude;
};

static double ParseDouble(std::istream& stream, const char& separator = '\n')
{
    std::string line;
    std::getline(stream, line, separator);
    std::replace(line.begin(), line.end(), ',', '.');
    return std::atof(line.c_str());
}

static Defibrilator ParseDefibrilator()
{
    Defibrilator defibrilator;

    // Conver the std::cin line to a stream
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    // Parse all values and store them in the Defibrilator
    defibrilator.id = ParseDouble(ss, ';');
    std::getline(ss, defibrilator.name, ';');
    std::getline(ss, defibrilator.address, ';');
    std::getline(ss, defibrilator.phone, ';');

    // Convert longitude and latitude to radians
    defibrilator.longitude = RADIANS(ParseDouble(ss, ';'));
    defibrilator.latitude = RADIANS(ParseDouble(ss, ';'));

    return defibrilator;
}

static double CalculateDistance(const Defibrilator& a, double userLongitude, double userLatitude)
{
    constexpr double earthRadius = 6371;
    double x = (userLongitude - a.longitude) * std::cos(0.5 * (a.latitude + userLatitude));
    double y = userLatitude - a.latitude;
    return std::sqrt(x * x + y * y) * earthRadius; 
}

static std::string FindNearestDefibrilator(const std::vector<Defibrilator>& defibrilators, double userLongitude, double userLatitude)
{
    Defibrilator nearestDefibrilator;
    double nearestDistance = std::numeric_limits<double>::max();

    for (const Defibrilator& defibrilator : defibrilators)
    {
        double distance = CalculateDistance(defibrilator, userLongitude, userLatitude);
        if (distance < nearestDistance)
        {
            nearestDefibrilator = defibrilator;
            nearestDistance = distance;
        }
    }

    return nearestDefibrilator.name;
}

int main()
{
    double userLongitude = RADIANS(ParseDouble(std::cin));
    double userLatitude = RADIANS(ParseDouble(std::cin));

    uint32_t defibrilatorCount = ParseDouble(std::cin);

    std::vector<Defibrilator> defibrilators;
    for (uint32_t i = 0; i < defibrilatorCount; i++)
        defibrilators.push_back(ParseDefibrilator());
    
    std::cout << FindNearestDefibrilator(defibrilators, userLongitude, userLatitude);
    std::cout << std::endl;
}