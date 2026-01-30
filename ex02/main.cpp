//############################################################
//#                                                          #
//#   ██████╗ ██████╗ ███╗   ██╗                             #
//#   ██╔══██╗╚════██╗████╗  ██║                             #
//#   ██████╔╝ █████╔╝██╔██╗ ██║                             #
//#   ██╔══██╗██╔═══╝ ██║╚██╗██║                             #
//#   ██████╔╝███████╗██║ ╚████║                             #
//#   ╚═════╝ ╚══════╝╚═╝  ╚═══╝                             #
//#                                                          #
//#   File    : main.cpp                                     #
//#   Created : 2026-01-30 17:16                             #
//#   Updated : 2026-01-30 17:16                             #
//#                                                          #
//############################################################

#include "PmergeMe.hpp"

void print_before(char **av)
{
    std::cout << "Before: ";
    for (size_t i = 1; av[i]; i++)
    {
        std::cout << av[i];
        if (av[i + 1])
            std::cout << " ";
    }
    std::cout << std::endl;
}

int main(int ac, char **av )
{
	if (ac < 2)
    {
        std::cerr << "Error: Need at least one argument" << std::endl;
        return 1;
    }
    PmergeMe pmergeme;
    try
    {
        pmergeme.parseInput(ac - 1, &av[1]);
        print_before(av);
        pmergeme.sortContainers();
        pmergeme.printContainers();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}