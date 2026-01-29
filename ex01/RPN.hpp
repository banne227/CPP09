#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <cstdlib>

typedef enum { ADD, SUBTRACT, MULTIPLY, DIVIDE } Operator;

typedef enum { NUMBER, OPERATOR, SPACE, INVALID } TokenType;

class ImposibleOperation : public std::exception
{
    public:
        const char* what() const throw() 
        {
            return "Error: Imposible divison by zero.";
        }
};

class RPN
{
    public:
        RPN();
        ~RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);

        int evaluate(const std::string& expression);
};

void print_error(void);

#endif