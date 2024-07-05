#include <iostream>
#include <cmath>

uint32_t GCD(uint32_t a, uint32_t b)
{
    uint32_t quotient = std::floor(a / b);
    uint32_t rest = a % b;

    std::cout << a << "=" << b << "*" << quotient << "+" << rest  << std::endl;

    return rest == 0 ? b : GCD(b, rest);
}

int main()
{
    uint32_t a;
    uint32_t b;
    std::cin >> a >> b;

    uint32_t gcd = GCD(a, b);
    std::cout << "GCD(" << a << "," << b << ")=" << gcd << std::endl;
}