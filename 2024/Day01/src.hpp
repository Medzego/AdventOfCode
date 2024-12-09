#include <iostream>
#include <vector>

class BigBrain
{
public :

    BigBrain();
    void init(const std::string& fileName);

    int compteListsDistance();
    int computeSimilarityScore();

private:

    std::vector<std::string> readFile(const std::string& fileName);
    void isolateLists(const std::vector<std::string>& inputData);

    std::vector<int> firstColumn;
    std::vector<int> secondColumn;
};
