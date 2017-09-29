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
	//constructor
	Lex();

	//finite state machine for integer
	int int_DFSM(const string str);

	//finite state machine for real
	int real_DFSM(const string str);

	//finite state machine for identifier
	int identifier_DFSM(const string str);

	//function convert a character to column number in transition table
	int char_to_col(const char input) const;
	bool isSeparator(const char input) const;
	bool isOperator(const char input) const;
	bool checkKeyword(string identifier) const;
	int Classify(string);
	void lexer(ifstream& file);
	void print() const;
	void setToken(const string newToken);
	void setLexeme(const string newLexeme);
	string getToken() const;
	string getLexeme() const;

	//destructor
	~Lex();
private:
	char input;
	string lexeme;
	string token;
};

#endif
