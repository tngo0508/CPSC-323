#ifndef LEXER.H
#define LEXER.H

#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

class lexer
{
    int char_to_col();
    int int_DFSM(string arg);
    int real_DFSM(string arg);
}

#endif#
