#include<iostream>
#include<string>
#include "Token.h"
#include "Token_stream.h"

Token_stream ts;

/* 
    Bitwise Expression Grammar

    Expression: 
        Term
            |
            Expression | Term
    Term:
        Primary
              |
              Term ^ Primary
    Primary:
        Number
            |
            Primary & Number
    Number:
        Integer, ASCII, (Unary)(Integer, ASCII)
*/

int number()
{
    Token t = ts.get();

    switch(t.kind)
    {
        case '#':
        {
            return t.value;
        }
        default:
        {
            std::cerr << "Invalid number\n";
            exit(-1);
        }
    }
}

int primary()
{
    int left = number();
    Token t = ts.get();

    switch(t.kind)
    {
        case '&':
        {
            return left & primary();
            break;
        }
        default:
        {
            ts.putback(t);
            return left;
        }
    }
}

int term()
{
    int left = primary();
    Token t = ts.get();

    switch(t.kind)
    {
        case '^':
        {
            return left ^ term();
            break;
        }
        default:
        {
            ts.putback(t);
            return left;
        }
    }
}

int expression()
{
    int left = term();
    Token t = ts.get();

    switch(t.kind)
    {
        case '|':
        {
            return left | expression();
            break;
        }
        default:
        {
            std::cout<< "Expression: " << left << "\n";
            return left;
        }
    }
}


int main()
{
    while(std::cin)
    {
        std::cout << ">    " << expression() << "\n";
    }
    
    return 0;
}