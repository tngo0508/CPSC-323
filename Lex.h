#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>

using namespace std;

struct LexToken {
	string lexeme;
	string token;
};


class Lex
{
public:
	Lex();
	int int_DFSM(int& currentState, const char input);
	int real_DFSM(int& currentState, const char input);
	int identifier_DFSM(int&currentState, const char input);
	int char_to_col(const char input) const;
	bool isSeparator(char input);
	bool isOperator(char input);
	bool checkKeyword(string identifier);
	string lexer(ifstream& file);
	~Lex();
private:
	int currentState;
	char input;
};

#endif
