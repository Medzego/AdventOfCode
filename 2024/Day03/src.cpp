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
    int result = 0;
    std::regex patternMul("mul\\((\\d+),(\\d+)\\)");
    std::regex patternDo("do\\(\\)");
    std::regex patternDont("don't\\(\\)");

    std::regex patternStart("(^)(.*?)(don't\\(\\))");
    std::regex patternDoDont("(do\\(\\))(.*?)(don't\\(\\))"); // TODO : ajouter la possibilité d'avoir le début de chaine de caratères (^) à la place de do

    std::smatch correspondancesMul;
    std::smatch correspondancesDo;
    std::smatch correspondancesDont;
    std::smatch correspondancesDoDont;
    std::smatch correspondancesStart;


    auto beginRaw = rawData.cbegin();
    auto endRaw = rawData.cend();

    std::regex_search(beginRaw, endRaw, correspondancesStart, patternStart);
    // std::cout << correspondancesDoDont[1]<< std::endl;
    // std::cout << "coucou" << std::endl;

    auto begin = std::string(correspondancesStart[2]).cbegin();
    auto end = std::string(correspondancesStart[2]).cend();

    while (std::regex_search(begin, end, correspondancesMul, patternMul))
    {
        std::cout << correspondancesMul[1] << "*" << correspondancesMul[2] << std::endl;
        result += stoi(correspondancesMul[1])*stoi(correspondancesMul[2]);
        begin = correspondancesMul.suffix().first;
    }

    while (std::regex_search(beginRaw, endRaw, correspondancesDoDont, patternDoDont))
    {
        // std::cout << correspondancesDoDont[1]<< std::endl;
        // std::cout << "coucou" << std::endl;

        auto begin = std::string(correspondancesDoDont[2]).cbegin();
        auto end = std::string(correspondancesDoDont[2]).cend();

        while (std::regex_search(begin, end, correspondancesMul, patternMul))
        {
            // std::cout << correspondances[1] << "*" << correspondances[2] << std::endl;
            result += stoi(correspondancesMul[1])*stoi(correspondancesMul[2]);
            begin = correspondancesMul.suffix().first;
        }

        beginRaw = correspondancesDoDont.suffix().first;
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
