#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

constexpr const uint8_t ASCII_BIT_COUNT = 7;

std::vector<uint8_t> GetMessageAsBits(const std::string& message)
{
    std::vector<uint8_t> bits;
    for (auto& c : message)
    {
        for (int8_t j = ASCII_BIT_COUNT - 1; j >= 0; j--)
            bits.push_back((c >> j) & 1);
    }
    return bits;
}

std::string EncodeBits(const std::vector<uint8_t>& bits)
{
    std::stringstream ss;

    uint8_t last_bit = bits.at(0);
    uint32_t last_count = 0;
    for (auto& bit : bits)
    {
        if (bit == last_bit)
        {
            last_count++;
            continue;
        }

        ss << (last_bit == 0 ? "00" : "0");
        ss << " ";

        for (uint32_t i = 0; i < last_count; i++)
            ss << "0";
        ss << " ";

        last_bit = bit;
        last_count = 1;
    }

    ss << (last_bit == 0 ? "00" : "0");
    ss << " ";

    for (uint32_t i = 0; i < last_count; i++)
        ss << "0";

    return ss.str();
}

int main()
{
    std::string message;
    getline(std::cin, message);
    
    std::vector<uint8_t> bits = GetMessageAsBits(message);
    std::cout << EncodeBits(bits) << std::endl;
}
