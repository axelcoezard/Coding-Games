#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numbers>

struct Vector
{
    double x;
    double y;
};

struct ShuttleProperties
{
    Vector position;
    Vector speed; // the horizontal and vertical speed (in m/s), can be negative.
    int32_t fuel; // the quantity of remaining fuel in liters.
    int32_t rotation;  // the rotation angle in degrees (-90 to 90).
    int32_t power; // the thrust power (0 to 4).
};

std::vector<Vector> ParseSurfacePoints()
{
    std::vector<Vector> points;

    // First, parse the number of points used to draw the surface of Mars.
    uint32_t count;
    std::cin >> count;
    std::cin.ignore();

    points.resize(count);

    // Then, parse all the surface points
    for (uint32_t i = 0; i < count; i++)
    {
        Vector point = {0, 0};
        std::cin >> point.x; // X coordinate of a surface point. (0 to 6999)
        std::cin >> point.y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        std::cin.ignore();

        points.push_back(point);
    }

    return points;
}

ShuttleProperties ParseShuttleProperties()
{
    ShuttleProperties shuttleProperties;

    std::cin >> shuttleProperties.position.x;
    std::cin >> shuttleProperties.position.y;
    std::cin >> shuttleProperties.speed.x;
    std::cin >> shuttleProperties.speed.y;
    std::cin >> shuttleProperties.fuel;
    std::cin >> shuttleProperties.rotation;
    std::cin >> shuttleProperties.power;
    std::cin.ignore();

    return shuttleProperties;
}

double CalculateDistance(const Vector& a, const Vector& b)
{
    double xx = b.x - a.x;
    double yy = b.y - a.y;
    return std::sqrt(xx * xx + yy * yy);
}

double CalculateAngle(const Vector& a, const Vector& b)
{
    return std::atan2(b.x - a.x, b.y - a.y) * 180.0 / std::numbers::pi;
}

Vector CalculateLandingCoordinates(const std::vector<Vector>& surfacePoints)
{
    Vector coordinates;
    for (uint32_t i = 1; i < surfacePoints.size(); i++)
    {
        const Vector landingA = surfacePoints.at(i - 1);
        const Vector landingB = surfacePoints.at(i);
        const double abAngle = CalculateAngle(landingA, landingB);
        const double abDistance = CalculateDistance(landingA, landingB);

        if (abAngle == 0 && abDistance >= 1000)
        {
            coordinates = {
                (landingA.x + landingB.x) / 2.0,
                (landingA.y + landingB.y) / 2.0
            };
            break;
        }
    }
    return coordinates;
}

int main()
{
    std::vector<Vector> surfacePoints = ParseSurfacePoints();

    Vector landingCoordinates = CalculateLandingCoordinates(surfacePoints);

    double initialDistance = -1.0;
    double initialAngle = -1.0;

    while (true)
    {
        auto shuttle = ParseShuttleProperties();

        double distance = CalculateDistance(shuttle.position, landingCoordinates);
        double angle = CalculateAngle(shuttle.position, landingCoordinates);

        if (initialDistance < 0) initialDistance = distance;
        if (initialAngle < 0) initialAngle = angle;

        double progress = 1.0 - std::abs(distance / initialDistance);

        std::cerr << "Landing: " << landingCoordinates.x << " " << landingCoordinates.y << std::endl;
        std::cerr << "Initial Distance: " << initialDistance << std::endl;
        std::cerr << "Distance: " << distance << std::endl;
        std::cerr << "Angle: " << angle << std::endl;
        std::cerr << "Progress: " << std::floor(progress * 100) << "%" << std::endl;

        // TODO: calculte power and rotation to land on landing coordinates
        double desiredRotation = 0.0;
        double desiredPower = 0.0;

        // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
        std::cout << std::floor(desiredRotation) << " " << std::floor(desiredPower);
        std::cout << std::endl;
    }
}
