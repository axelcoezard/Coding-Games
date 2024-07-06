#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

constexpr const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
constexpr const char ALPHABET_SIZE = 26;

static void PerformCaesarShift(std::string& message, const uint32_t shift, bool encode)
{
    const std::string messageCopy(message);
    for (uint32_t i = 0; i < messageCopy.length(); i++)
    {
        int32_t effectiveShift = (shift + i) % ALPHABET_SIZE;
        if (encode) message[i] = 'A' + (messageCopy[i] - 'A' + effectiveShift) % ALPHABET_SIZE;
        else        message[i] = 'A' + (messageCopy[i] - 'A' - effectiveShift + ALPHABET_SIZE) % ALPHABET_SIZE;
    }
}

static void PerformRotorShift(std::string& message, const std::string& rotor, bool encode)
{
    const std::string messageCopy(message);
    for (uint32_t i = 0; i < messageCopy.length(); i++)
    {
        if (encode) message[i] = rotor[std::string(ALPHABET).find_first_of(messageCopy[i])];
        else        message[i] = ALPHABET[rotor.find_first_of(messageCopy[i])];
    }
}

static void Encode(std::string& message, const uint32_t initialShift, const std::vector<std::string>& rotors)
{
    PerformCaesarShift(message, initialShift, true);

    for (auto it = rotors.begin(); it != rotors.end(); ++it)
        PerformRotorShift(message, *it, true);
}

static void Decode(std::string& message, const uint32_t initialShift, const std::vector<std::string>& rotors)
{
    for (auto it = rotors.rbegin(); it != rotors.rend(); ++it)
        PerformRotorShift(message, *it, false);

    PerformCaesarShift(message, initialShift, false);
}

int main()
{
    std::string operation;
    getline(std::cin, operation);

    uint32_t initialShift;
    std::cin >> initialShift; std::cin.ignore();

    std::vector<std::string> rotors;
    for (uint32_t i = 0; i < 3; i++)
    {
        std::string rotor;
        getline(std::cin, rotor);
        rotors.push_back(rotor);
    }

    std::string message;
    getline(std::cin, message);

    if (operation == "ENCODE")  Encode(message, initialShift, rotors);
    else                        Decode(message, initialShift, rotors);

    std::cout << message << std::endl;
}