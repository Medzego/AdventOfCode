#include "src.hpp"

int main()
{
    BigBrain brain;

    std::cout << "First part answer : " << brain.filteredMuls() << std::endl;
    std::cout << "Second part answer : " << brain.filteredAndEnabledMuls() << std::endl;

    return 0;
}
