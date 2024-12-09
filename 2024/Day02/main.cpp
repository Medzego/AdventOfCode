#include "src.hpp"

int main()
{
    BigBrain brain;

    std::cout << "First part answer : " << brain.howMuchLinesAreSafe() << std::endl;
    std::cout << "Second part answer : " << brain.howMuchLinesAreAlmostSafe() << std::endl;

    return 0;
}
