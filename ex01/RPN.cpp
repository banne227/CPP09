#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}
RPN::RPN(const RPN& other) { *this = other; }
RPN& RPN::operator=(const RPN& other) 
{
    (void)other;
    return *this;
}

int operation(Operator op, int a, int b)
{
    switch (op)
    {
        case ADD:
            return a + b;
        case SUBTRACT:
            return a - b;
        case MULTIPLY:
            return a * b;
        case DIVIDE:
            if (b == 0)
                throw ImposibleOperation();
            return a / b;
        default:
            throw ImposibleOperation();
    }
}

TokenType getTokenType(char c)
{
    if (std::isdigit(c))
        return NUMBER;
    else if (c == '+' || c == '-' || c == '*' || c == '/')
        return OPERATOR;
    else if (std::isspace(c))
        return SPACE;
    else
        return INVALID;
}

void print_error(void)
{
    std::cout << "Error" << std::endl;
    exit(1);
}

Operator get_operator(char c)
{
    switch (c)
    {
        case '+':
            return ADD;
        case '-':
            return SUBTRACT;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        default:
            throw ImposibleOperation();
    }
}

int RPN::evaluate(const std::string& expression)
{
    std::stack<int> stack;
    int a, b, result;
    long unsigned int i = 0;
    while (i < expression.length())
    {
        char c = expression[i];
        TokenType type = getTokenType(c);

        if (type == SPACE)
        {
            i++;
            continue;
        }
        else if (type == INVALID)
            print_error();
           
        else if (type == NUMBER)
            stack.push(c - '0');
        else if (type == OPERATOR)
        {
            if (stack.size() < 2)
                print_error();
            b = stack.top(); stack.pop();
            a = stack.top(); stack.pop();
            Operator op = get_operator(c);
            result = operation(op, a, b);
            stack.push(result);
        }
        i++;
    }
    if (stack.size() != 1)
        print_error();
    return stack.top();
}