#include "parser.h"
#include "Lex.h"
#include <fstream>

using namespace std;

ifstream fin;


//void parser::Parser(ifstream &file)
//{
//	
//}

//Get next Token
//Does not work
//Should be NextToken(filestream)
Lex parser::getNextToken() 
{
	currentToken.lexer(fin);
	return currentToken;
}

void parser::Program()
{
	stmt();

}

/*
	if lexeme and token equals parameter s, get next token and lexeme;
*/
bool parser::accept(string s)
{
	if (currentToken.getLexeme() == s || currentToken.getToken() == s) {
		getNextToken();
		return true;
	}
	return false;
}

/*
	if not eof maker then error message,  expected
	else go to function accept
*/
void parser::expect(string s)
{
	if (!accept(s)) {
		writeError("Line number: , Error: unexpected string: " + currentToken.getLexeme() + ", expected " + s);
	}
}

void parser::writeError(string s)
{
	cout << s << endl;
	exit(1);
}

parser::parser()
{
}


void parser::RAT17F()
{
}

void parser::optFunctionDef()
{
}

void parser::functionDef()
{
}

void parser::function()
{
}

void parser::parameterList()
{
}

void parser::parameter()
{
}

void parser::qualifier()
{
}

void parser::body()
{
}

void parser::optDeclartationList()
{
}

void parser::declarationList()
{
}

void parser::Declaration()
{
}

void parser::iDs()
{
}

void parser::stmtList()
{
}

void parser::stmt()
{
	if (currentToken.getToken() == "identifier") {
		assign();
		cout << "<Statement>-><Assign>" << endl;
	}
	else if (currentToken.getToken() == "compound") {
		compound();
		cout << "<Statement>-><compound>" << endl;
	}
	else if (currentToken.getToken() == "if") {
		ifKeyword();
		cout << "<Statement>-><If>" << endl;
	}
	else if (currentToken.getToken() == "return") {
		returnKeyword();
		cout << "<Statement>-><Return>" << endl;
	}
	else if (currentToken.getToken() == "write") {
		writeKeyword();
		cout << "<Statement>-><Write>" << endl;
	}
	else if (currentToken.getToken() == "read") {
		readKeyword();
		cout << "<Statement>-><Read>" << endl;
	}
	else if (currentToken.getToken() == "while") {
		whileKeyword();
		cout << "<Statement>-><While>" << endl;
	}
	else {
		writeError("Line number: , error: unexpected string: " + currentToken.getLexeme() + ", expected end");
		accept(currentToken.getLexeme()); //get next lexeme
	}
}

void parser::compound()
{
}

void parser::assign()
{
	expect("identifier");
	expect(":=");
	expression();
	expect(";");
	cout << "<Assign>-><Identifier>:=<Expression>;" << endl;
}

void parser::ifKeyword()
{
}

void parser::returnKeyword()
{
}

void parser::writeKeyword()
{
	expect("write");
	expect("(");
	expression();
	expect(")");
	expect(";");
	cout << "<Write> -> write (<Expression>);" << endl;
}

void parser::readKeyword()
{
	expect("read");
	expect("(");
	iDs();
	expect(")");
	expect(";");
	cout << "<Read> -> read (<IDs>);" << endl;
}

void parser::whileKeyword()
{
}

void parser::condition()
{
	expression();
	relop();
	expression();
	cout << "<Condition>-><Expression><Relop><Expression>" << endl;
}

void parser::relop()
{
	if (currentToken.getLexeme() == "=") {
		cout << "<Relop>-> =" << endl;
	}
	else if (currentToken.getLexeme() == "/=") {
		cout << "<Relop>-> /=" << endl;
	}
	else if (currentToken.getLexeme() == ">") {
		cout << "<Relop>-> >" << endl;
	}
	else if (currentToken.getLexeme() == "<") {
		cout << "<Relop>-> <" << endl;
	}
	else if (currentToken.getLexeme() == "=>") {
		cout << "<Relop>-> =>" << endl;
	}
	else if (currentToken.getLexeme() == "<=") {
		cout << "<Relop>-> <=" << endl;
	}
	else {
		writeError("Line number: , error: unexpected string: " + currentToken.getLexeme() + ", expected end");
		accept(currentToken.getLexeme()); //get next lexeme
	}
}

/*
	E->TE'
	E'->+TE' | -TE'
*/
void parser::expression()
{
	term();
	while (currentToken.getLexeme() == "+" || currentToken.getLexeme() == "-") {
		
		expect(currentToken.getToken());
		term();
	}
	if (currentToken.getLexeme() == "+") {
		cout << "<Expression Prime> -> + <Term><Expression Prime>";
	}
	else if (currentToken.getLexeme() == "-") {
		cout << "<Expression Prime> -> -<Term><Expression Prime>";
	}

}

/*

*/

void parser::term()
{
	factor();
	while (currentToken.getLexeme() == "*" || currentToken.getLexeme() == "/") {
		expect(currentToken.getLexeme());
		factor();
	}
	if (currentToken.getLexeme() == "*") {
		cout << "<Term Prime>->*<Factor><Term Prime>";
	}
	else if (currentToken.getLexeme() == "/") {
		cout << "<Term Prime>->/<Factor><Term Prime>";
	}
}

void parser::factor()
{
	if (currentToken.getToken() == "-") {
		cout << "<Factor>-> - <Primary>" << endl;
		primary();
	}
	else {
		cout << "<Factor>-> <Primary>" << endl;
		primary();
	}
}

// lack of Identifer[IDs]
void parser::primary()
{
	if (accept("identifier")) {
		cout << "<Primary>-><Identifier>" << endl;
	}
	else if (accept("integer")) {
		cout << "<Primary>-><Interger>" << endl;
	}
	else if (accept("(")) {
		expression();
		expect(")");
		cout << "Primary -> (Expression)" << endl;
	}
	else if (accept("real")) {
		cout << "<Primary>-><real>" << endl;
	}
	else if (accept("true")) {
		cout << "<Primary>-><true>" << endl;
	}
	else if (accept("false")) {
		cout << "<Primary>-><false>" << endl;
	}

}

void parser::empty()
{
	cout << "<Empty>->Epsilon" << endl;
}


parser::~parser()
{
}
