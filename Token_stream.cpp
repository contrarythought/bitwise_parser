#include "Token.h"
#include "Token_stream.h"
#include<iostream>
#include<string>

#define NUM '#'

Token Token_stream::get()
{
   // Token tok; // return value
   // if buffer already has a token in it, return that token
   if(is_full)
   {
       is_full = false;
       return buffer;
   }

    char ch;
    std::cin >> ch;

    switch(ch)
    {
        /** cases where it's an int without unary operators */
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            int val = 0;

            // put character back in in order to read the double value of it
            std::cin.putback(ch);

            // read in val
            std::cin >> val;

            return Token{NUM, val};
        }

        /** cases where it's a unary operator */
        case '~':
        {
            unsigned comp_count = 1;
            char ch;
            std::cin >> ch;
            while(ch == '~')
            {
                comp_count++;
                std::cin >> ch;
            }

            std::cin.putback(ch); // first char that is not ~ needs to be put back into input stream so that it can be reused

            int val = 0;
            std::cin >> val;

            if(comp_count % 2 != 0)
                val = ~val;

            return Token{NUM, val};
        }
        case '&':
        case '|':
        case '^':
        case '=':
        {
            return Token{ch};
        }
        default:
        {
            std::cerr << "Invalid input\n";
            exit(-1);
        }

    }
}

void Token_stream::putback(Token t)
{
    // if the token buffer is already full, return error
    if(is_full)
    {
        std::cerr << "Buffer is already full\n";
        exit(-1);
    }

    buffer = t;
    is_full = true;
}