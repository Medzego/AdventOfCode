#include "src.hpp"

#include <sstream>
#include <fstream>
#include <algorithm>

namespace
{
    int abs(int a, int b)
    {
        return (a < b) ? (b - a) : (a - b);
    }
}

BigBrain::BigBrain()
{
    init("input.txt");
}

void BigBrain::init(const std::string& fileName)
{
    auto rawData = readFile(fileName);
    isolateLines(rawData);
}

bool BigBrain::lineIsSafe(const std::vector<int>& list)
{
    bool increasing = false;
    if (list.size() > 1)
    {
        increasing = list.at(1) > list.at(0);
    }

    bool soFarSoGood = true;
    for(int i = 0; i < list.size() - 1; ++i)
    {
        bool increaseButNotTooMuch = increasing && ((list.at(i + 1) - list.at(i)) <= 3) && ((list.at(i + 1) - list.at(i)) > 0);
        bool decreaseButNotTooMuch = !increasing && ((list.at(i) - list.at(i + 1)) <= 3) && ((list.at(i) - list.at(i + 1)) > 0);

        soFarSoGood &= increaseButNotTooMuch || decreaseButNotTooMuch;
    }

    // for (auto n : list) { std::cout << n << " ";}
    // std::cout << " => incr ? " << increasing << " safe ? " << soFarSoGood << std::endl;
    return soFarSoGood;
}

bool BigBrain::lineIsAlmostSafe(const std::vector<int>& list)
{
    bool increasing = false;
    if (list.size() > 1)
    {
        increasing = list.at(1) > list.at(0);
    }

    bool soFarSoGood = true;
    int accidents = 1;
    for(int i = 0; i < list.size() - 1; ++i)
    {
        bool increaseButNotTooMuch = increasing && ((list.at(i + 1) - list.at(i)) <= 3) && ((list.at(i + 1) - list.at(i)) > 0);
        bool decreaseButNotTooMuch = !increasing && ((list.at(i) - list.at(i + 1)) <= 3) && ((list.at(i) - list.at(i + 1)) > 0);

        soFarSoGood &= increaseButNotTooMuch || decreaseButNotTooMuch || accidents-- > 0;
    }

    // for (auto n : list) { std::cout << n << " ";}
    // std::cout << "safe ? " << soFarSoGood << std::endl;
    return soFarSoGood;
}

int BigBrain::howMuchLinesAreSafe()
{
    int numberSafeLines = 0;
    for (const auto& line : rawData)
    {
        if (lineIsSafe(line))
        {
            numberSafeLines++;
        }
    }

    return numberSafeLines;
}

int BigBrain::howMuchLinesAreAlmostSafe()
{
    int numberSafeLines = 0;
    for (const auto& line : rawData)
    {
        if (lineIsAlmostSafe(line))
        {
            numberSafeLines++;
        }
    }

    return numberSafeLines;
}

std::vector<std::string> BigBrain::readFile(const std::string& fileName)
{
    std::vector<std::string> outputVector;
    std::ifstream file(fileName);

    if (!file)
    {
        std::cerr << "Impossible to open the file" << std::endl;
        return outputVector;
    }

    std::string ligne;
    while (std::getline(file, ligne))
    {
        outputVector.push_back(ligne);
    }

    file.close();

    return outputVector;
}

void BigBrain::isolateLines(const std::vector<std::string>& inputData)
{
    for (const auto& line : inputData)
    {
        std::istringstream stream(line);
        std::vector<int> vectLine;
        int number;
        while (stream >> number)
        {
            vectLine.push_back(number);
        }

        rawData.push_back(vectLine);
    }
}