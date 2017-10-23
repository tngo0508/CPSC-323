#pragma once
#include "Lex.h"

class parser
{
public:

	Lex currentToken;
	string getToken();
	bool accept(string s);
	void expect(string s);
	parser();
	void RAT17F();
	void optFunctionDef();
	void functionDef();
	void function();
	void parameterList();
	void parameter();
	void qualifier();
	void body();
	void optDeclartationList();
	void declarationList();
	void Declaration();
	void iDs();
	void stmtList();
	void stmt();
	void compound();
	void assign();
	void ifKeyword();
	void returnKeyword();
	void writeKeyword();
	void readKeyword();
	void whileKeyword();
	void condition();
	void relop();
	void expression();
	void term();
	void factor();
	void primary();
	void empty();
	~parser();
};

