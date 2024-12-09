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
    isolateLists(rawData);
}

int BigBrain::compteListsDistance()
{
    int output = 0;

    std::sort(firstColumn.begin(), firstColumn.end());
    std::sort(secondColumn.begin(), secondColumn.end());

    for (int i = 0; i < firstColumn.size(); ++i)
    {
        output += abs(firstColumn.at(i), secondColumn.at(i));
    }

    return output;
}

int BigBrain::computeSimilarityScore()
{
    int output = 0;

    std::vector<std::pair<int, int>> appearances;

    int numberOfAppearances;
    for (const auto& col1 : firstColumn)
    {
        numberOfAppearances = 0;
        for (const auto& col2 : secondColumn)
        {
            if (col1 == col2)
            {
                numberOfAppearances++;
            }
        }
        // std::cout << col1 << " " << numberOfAppearances << std::endl;
        appearances.push_back(std::make_pair(col1, numberOfAppearances));
    }

    for (const auto& app : appearances)
    {
        output += app.first * app.second;
    }

    return output;
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

void BigBrain::isolateLists(const std::vector<std::string>& inputData)
{
    for (const auto& line : inputData)
    {
        std::istringstream stream(line);
        int first, second;
        stream >> first >> second;
        firstColumn.push_back(first);
        secondColumn.push_back(second);
    }
}