#pragma once
#include "Lex.h"
#include <fstream>

class parser : public Lex
{
public:

	void Program(ifstream &);
	bool accept(string s, ifstream&);
	void expect(string s, ifstream&);
	void writeError(string s);
	parser();
	void Parser(ifstream &file);
	void RAT17F(ifstream &);
	void optFunctionDef(ifstream &);
	void functionDef(ifstream &);
	void function(ifstream &);
	void parameterList(ifstream &);
	void parameter(ifstream &);
	void qualifier(ifstream &);
	void body(ifstream &);
	void optDeclartationList(ifstream &);
	void declarationList(ifstream &);
	void Declaration(ifstream &);
	void iDs(ifstream &);
	void stmtList(ifstream &);
	void stmt(ifstream &);
	void compound(ifstream &);
	void assign(ifstream &);
	void ifKeyword(ifstream &);
	void returnKeyword(ifstream &);
	void writeKeyword(ifstream &);
	void readKeyword(ifstream &);
	void whileKeyword(ifstream &);
	void condition(ifstream &);
	void relop(ifstream &);
	void expression(ifstream &);
	void term(ifstream &);
	void factor(ifstream &);
	void primary(ifstream &);
	void empty(ifstream &);
	~parser();
protected:
	string token = getToken();
	string lexeme = getLexeme();

};