#include <iostream>
#include <string>
#include <vector>
#include <set>

bool CheckSudoku(const std::vector<uint32_t>& sudoku)
{
    // First: check rows
    for (uint32_t i = 0; i < 9; i++)
    {
        std::set<uint32_t> checker;
        for (uint32_t j = 0; j < 9; j++)
        {
            uint32_t value = sudoku.at(i + j * 9);

            if (value == 0)
                continue;

            if (checker.find(value) != checker.end())
                return false;

            checker.insert(value);
        }
    }

    // Check: check columns
    for (uint32_t i = 0; i < 9; i++)
    {
        std::set<uint32_t> checker;
        for (uint32_t j = 0; j < 9; j++)
        {
            uint32_t value = sudoku.at(j + i * 9);

            if (value == 0)
                continue;

            if (checker.find(value) != checker.end())
                return false;

            checker.insert(value);
        }
    }

    // Third: check sub-grids
    for (int block = 0; block < 9; block++)
    {
        std::set<uint32_t> checker;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                uint32_t row = 3 * (block / 3) + i;
                uint32_t col = 3 * (block % 3) + j;
                uint32_t value = sudoku.at(row + col * 9);

                if (value == 0)
                    continue;

                if (checker.find(value) != checker.end())
                    return false;

                checker.insert(value);
            }
        }
    }

    return true;
}


int main()
{
    std::vector<uint32_t> sudoku(9 * 9);

    for (uint32_t i = 0; i < 9; i++)
    {
        for (uint32_t j = 0; j < 9; j++)
        {
            std::cin >> sudoku.at(i + j * 9);
            std::cin.ignore();
        }
    }

    std::cout << (CheckSudoku(sudoku) ? "true" : "false") << std::endl;
}
