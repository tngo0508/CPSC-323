#include "parser.h"
#include "Lex.h"
#include <fstream>

using namespace std;



void parser::Parser(ifstream &file)
{
	
}


parser::parser()
{
}

//void parser::Program()
//{
//    stmt();
//
//}


//void parser::writeError(string s)
//{
//	cout << s << endl;
//	exit(1);
//}


//void parser::stmt()
//{
//    if (currentToken.getToken() == "identifier") {
//        assign();
//        cout << "<Statement>-><Assign>" << endl;
//    }
//    else if (currentToken.getToken() == "compound") {
//        compound();
//        cout << "<Statement>-><compound>" << endl;
//    }
//    else if (currentToken.getToken() == "if") {
//        ifKeyword();
//        cout << "<Statement>-><If>" << endl;
//    }
//    else if (currentToken.getToken() == "return") {
//        returnKeyword();
//        cout << "<Statement>-><Return>" << endl;
//    }
//    else if (currentToken.getToken() == "write") {
//        writeKeyword();
//        cout << "<Statement>-><Write>" << endl;
//    }
//    else if (currentToken.getToken() == "read") {
//        readKeyword();
//        cout << "<Statement>-><Read>" << endl;
//    }
//    else if (currentToken.getToken() == "while") {
//        whileKeyword();
//        cout << "<Statement>-><While>" << endl;
//    }
//    else {
//        writeError("Line number: , error: unexpected string: " + currentToken.getLexeme() + ", expected end");
//        accept(currentToken.getLexeme()); //get next lexeme
//    }
//}
//
//void parser::compound()
//{
//}
//
void parser::assign(ifstream &fin)
{
	if (currentToken.getToken() == "identifier") {
		currentToken.lexer(fin);
		if (currentToken.getLexeme() == ":=") {
			currentToken.lexer(fin);
			expression(fin);
			if (currentToken.getLexeme() == ";") {
				currentToken.lexer(fin);
			}
			else {
				cout << "Expected ;\n";
			}
		}
		else {
			cout << "Expected :=\n";
		}
	}
	else {
		cout << "Expected Identifier\n";
	}
}

//<write> -> write (<expression>);
void parser::writeKeyword(ifstream &fin)
{
	if (currentToken.getLexeme() == "write") {
		currentToken.lexer(fin);
		if (currentToken.getLexeme() == "(") {
			currentToken.lexer(fin);
			expression(fin);
			if (currentToken.getLexeme() == ")") {
				currentToken.lexer(fin);
				if (currentToken.getLexeme() == ";") {
					currentToken.lexer(fin);
				}
				else {
					cout << "Expected ;\n";
				}
			}else {
				cout << "Expected )\n";
			}
		}
		else {
			cout << "Expected (\n";
		}
	}
	else {
		cout << "Expected write\n";
	}
	cout << "<write> -> write (<expression>);" << endl;

}

//<Read> -> read (<IDs>);
void parser::readKeyword(ifstream &fin)
{
	if (currentToken.getLexeme() == "read") {
		currentToken.lexer(fin);
		if (currentToken.getLexeme() == "(") {
			currentToken.lexer(fin);
			iDs(fin);
			if (currentToken.getLexeme() == ")") {
				currentToken.lexer(fin);
				if (currentToken.getLexeme() == ";") {
					currentToken.lexer(fin);
				}
				else {
					cout << "Expected ;\n";
				}
			}
			else {
				cout << "Expected )\n";
			}
		}
		else {
			cout << "Expected (\n";
		}
	}
	else {
		cout << "Expected read\n";
	}
	cout << "<Read> -> read (<IDs>);" << endl;


}

//while (<condition>) <Statement>
void parser::whileKeyword(ifstream &fin) {
	if (currentToken.getLexeme() == "while") {
		currentToken.lexer(fin);
		if (currentToken.getLexeme() == "(") {
			currentToken.lexer(fin);
			condition(fin);
			if (currentToken.getLexeme() == ")") {
				currentToken.lexer(fin);
				stmt(fin);
			}
			else {
				cout << "Expected )\n";
			}
		}
		else {
			cout << "Expected (\n";
		}
	}
	else {
		cout << "Expected while\n";
	}
	cout << "while(<condition>)<Statement>\n";
}

//
void parser::returnKeyword(ifstream &fin) {



}
//void parser::condition()
//{
//    expression();
//    relop();
//    expression();
//    cout << "<Condition>-><Expression><Relop><Expression>" << endl;
//}
//
//void parser::relop()
//{
//    if (currentToken.getLexeme() == "=") {
//        cout << "<Relop>-> =" << endl;
//    }
//    else if (currentToken.getLexeme() == "/=") {
//        cout << "<Relop>-> /=" << endl;
//    }
//    else if (currentToken.getLexeme() == ">") {
//        cout << "<Relop>-> >" << endl;
//    }
//    else if (currentToken.getLexeme() == "<") {
//        cout << "<Relop>-> <" << endl;
//    }
//    else if (currentToken.getLexeme() == "=>") {
//        cout << "<Relop>-> =>" << endl;
//    }
//    else if (currentToken.getLexeme() == "<=") {
//        cout << "<Relop>-> <=" << endl;
//    }
//    else {
//        writeError("Line number: , error: unexpected string: " + currentToken.getLexeme() + ", expected end");
//        accept(currentToken.getLexeme()); //get next lexeme
//    }
//}
//
/*
E->TE'
E'->+TE' | -TE'
*/
void parser::expression(ifstream &fin)
{
	term(fin);
	while (currentToken.getLexeme() == "+" || currentToken.getLexeme() == "-") {

		//expect(currentToken.getToken(), fin);
		if (currentToken.getLexeme() == "+" || currentToken.getLexeme() == "-") {
			if (currentToken.getLexeme() == "+") {
				cout << "<Expression Prime> -> + <Term><Expression Prime>";
			}
			else if (currentToken.getLexeme() == "-") {
				cout << "<Expression Prime> -> -<Term><Expression Prime>";
			}
			currentToken.lexer(fin);
			term(fin);
			
		}
		else {
			cout << "Error Expected" << endl;
		}
	}
	
	
}

void parser::term(ifstream &fin)
{
	factor(fin);
	while (currentToken.getLexeme() == "*" || currentToken.getLexeme() == "/") {
		expect(currentToken.getLexeme(), fin);
		factor(fin);
	}
	if (currentToken.getLexeme() == "*") {
		cout << "<Term Prime>->*<Factor><Term Prime>";
	}
	else if (currentToken.getLexeme() == "/") {
		cout << "<Term Prime>->/<Factor><Term Prime>";
	}
}

//<Factor> -> - <Primary> || <Primary>
void parser::factor(ifstream &fin)
{
	if (currentToken.getLexeme() == "-") {
		cout << "<Factor>-> - <Primary>" << endl;
	}
	else {
		cout << "<Factor>-> <Primary>" << endl;
	}
	currentToken.lexer(fin);
	primary(fin);
}

// lack of Identifer[IDs]
void parser::primary(ifstream &fin)
{
	if (accept("identifier", fin)) {
		cout << "<Primary>-><Identifier>" << endl;
	}
	else if (accept("integer", fin)) {
		cout << "<Primary>-><Interger>" << endl;
	}
	else if (accept("(", fin)) {
		expression(fin);
		expect(")", fin);
		cout << "Primary -> (Expression)" << endl;
	}
	else if (accept("real", fin)) {
		cout << "<Primary>-><real>" << endl;
	}
	else if (accept("true", fin)) {
		cout << "<Primary>-><true>" << endl;
	}
	else if (accept("false", fin)) {
		cout << "<Primary>-><false>" << endl;
	}

}

//void parser::empty()
//{
//    cout << "<Empty>->Epsilon" << endl;
//}
//
//
parser::~parser()
{
}
