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
	int int_DFSM(const string str);
	int real_DFSM(const string str);
	int identifier_DFSM(const string str);
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
	~Lex();
private:
	char input;
	string lexeme;
	string token;
};

#endif
