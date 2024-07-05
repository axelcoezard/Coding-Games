#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <unordered_set>

const auto FILENAME_FORMAT = std::regex(R"((\w+)\.(\w+))");

uint32_t ParseInteger()
{
    uint32_t value;
    std::cin >> value; std::cin.ignore();
    return value;
}

std::string toLower(const std::string& value)
{
    std::string result(value);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::pair<bool, std::string> IsValidFilename(const std::string& filename)
{
    std::size_t pos = filename.rfind('.');
    if (pos == std::string::npos)
        return {false, ""};

    const std::string right = toLower(filename.substr(pos + 1));
    return {true, right}; 
}

int main()
{
    std::map<std::string, std::string> associationTable;

    int typeCount = ParseInteger(); // Number of elements which make up the association table.
    int filenameCount = ParseInteger(); // Number Q of file names to be analyzed.

    for (int i = 0; i < typeCount; i++) {
        std::string extension; // file extension
        std::string mimeType; // MIME type.
        std::cin >> extension >> mimeType; std::cin.ignore();

        extension = toLower(extension);

        associationTable[extension] = mimeType;
    }

    for (int i = 0; i < filenameCount; i++) {
        std::string filename;
        getline(std::cin, filename); // One file name per line.

        const auto [isValid, extension] = IsValidFilename(filename);
        if (isValid && associationTable.find(extension) != associationTable.end())
            std::cout << associationTable.at(extension) << std::endl;
        else
            std::cout << "UNKNOWN" << std::endl;
    }
}
