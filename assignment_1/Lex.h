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
	int int_DFSM(const string str);
	int real_DFSM(string str);
	int identifier_DFSM(string str);
	int char_to_col(const char input) const;
	bool isSeparator( char input) ;
	bool isOperator( char input) ;
	bool checkKeyword(string identifier) ;
	LexToken lexer(ifstream& file);
	void print() const;
	void setToken(const string);
	void setLexeme(const string);
	int Classify(string s);
	~Lex();
private:
	int currentState;
	char input;
};

#endif
