#include <iostream>
#include <vector>

class BigBrain
{
public :

    BigBrain();
    void init(const std::string& fileName);

    int howMuchLinesAreSafe();
    int howMuchLinesAreAlmostSafe();

private:

    std::vector<std::string> readFile(const std::string& fileName);
    void isolateLines(const std::vector<std::string>& inputData);

    bool lineIsSafe(const std::vector<int>& list);
    bool lineIsAlmostSafe(const std::vector<int>& list);

    std::vector<std::vector<int>> rawData;
};
