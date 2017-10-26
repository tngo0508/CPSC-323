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

	//function returns the column number of the character in the table
	int char_to_col(const char input) const;

	//Helper functions checking separator, operator and keyword
	bool isSeparator(const char input) const;
	bool isOperator(const char input) const;
	bool checkKeyword(string identifier) const;

	//function classify a string into a specific group
	int Classify(string);

	//function returns a token and a lexeme
	void lexer(ifstream& file);

	//function prints token and lexeme
	void print() const;

	//mutators
	void setToken(const string newToken);
	void setLexeme(const string newLexeme);

	//accessors
	string getToken() const;
	string getLexeme() const;

	//destructor
	~Lex();
protected:
	char input;
	string lexeme;
	string token;
};

#endif
