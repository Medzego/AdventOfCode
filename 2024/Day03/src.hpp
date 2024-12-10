#include <iostream>
#include <vector>

class BigBrain
{
public :

    BigBrain();
    void init(const std::string& fileName);

    int filteredMuls();
    int filteredAndEnabledMuls();

private:

    void readFile(const std::string& fileName);

    std::string rawData;
};
