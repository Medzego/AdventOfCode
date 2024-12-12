#include "src.hpp"

#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>

BigBrain::BigBrain()
{
    init("input.txt");
}

void BigBrain::init(const std::string& fileName)
{
    readFile(fileName);
}

int BigBrain::filteredMuls()
{
    int result = 0;
    std::regex pattern("mul\\((\\d+),(\\d+)\\)");
    std::smatch correspondances;
    auto begin = rawData.cbegin();
    auto end = rawData.cend();

    while (std::regex_search(begin, end, correspondances, pattern))
    {
        // std::cout << correspondances[1] << "*" << correspondances[2] << std::endl;
        result += stoi(correspondances[1])*stoi(correspondances[2]);
        begin = correspondances.suffix().first;
    }

    return result;
}

int BigBrain::filteredAndEnabledMuls()
{
    rawData = "do()" + rawData + "don't()";
    int result = 0;
    std::regex patternMul("mul\\((\\d+),(\\d+)\\)");
    std::regex patternDo("do\\(\\)");
    std::regex patternDont("don't\\(\\)");

    std::smatch correspondancesMul;
    std::smatch correspondancesDo;
    std::smatch correspondancesDont;

    auto begin = rawData.cbegin();
    auto end = rawData.cend();

    auto itDo = begin, itDont = begin;

    bool mulsEnabled = true;
    while (begin != end)
    {
        std::regex_search(begin, end, correspondancesDo, patternDo);
        itDo = correspondancesDo.suffix().first;

        std::regex_search(begin, end, correspondancesDont, patternDont);
        itDont = correspondancesDont.suffix().first;
        while (itDont < itDo)
        {
            std::regex_search(itDont, end, correspondancesDont, patternDont);
            itDont = correspondancesDont.suffix().first;
        }

        while (std::regex_search(itDo, itDont, correspondancesMul, patternMul))
        {
            // std::cout << correspondancesMul[1] << "*" << correspondancesMul[2] << std::endl;
            result += stoi(correspondancesMul[1])*stoi(correspondancesMul[2]);
            itDo = correspondancesMul.suffix().first;
        }

        begin = itDont;
    }

    return result;
}

void BigBrain::readFile(const std::string& fileName)
{
    std::vector<std::string> outputVector;
    std::ifstream file(fileName);

    if (!file)
    {
        std::cerr << "Impossible to open the file" << std::endl;
        return;
    }

    std::string ligne;
    while (std::getline(file, ligne))
    {
        rawData += ligne;
    }

    file.close();
}
