#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>

using namespace std;

class Lex
{
    public:
        Lex();
        int int_DFSM(int& currentState, char input);
        string lexer(string str);
        ~Lex();
    private:
        int currentState;
        char input;
};

#endif
