#include "RPN.hpp"

int main(int ac, char** av)
{
    if (ac != 2)
        print_error();
    RPN rpn;
    try
    {
        int result = rpn.evaluate(av[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}