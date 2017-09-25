#ifndef LEXER_HPP
#define LEXER_HPP

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
        int int_DFSM(int& currentState, const char input);
        int real_DFSM(int& currentState, const char input);
        int id_DFSM(int& currentState, const char input);
        int char_to_col(const char input) const;
        string lexer(ifstream& file);
        ~Lex();
    private:
        int currentState;
        char input;
};

#endif
