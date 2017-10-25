#include "parser.h"
#include "Lex.h"
#include <fstream>

using namespace std;



void parser::Parser(ifstream &file)
{
	currentToken.lexer(file);
	if (!(currentToken.getLexeme() == "EOF")) {
		currentToken.print();
	}
}


parser::parser()
{
}

////void parser::Program()
////{
////    stmt();
////
////}
//
//
////void parser::writeError(string s)
////{
////	cout << s << endl;
////	exit(1);
////}
//
//
//void parser::stmt(ifstream &fin)
//{
//    if (currentToken.getToken() == "identifier") {
//        assign(fin);
//        cout << "<Statement>-><Assign>" << endl;
//    }
//    else if (currentToken.getToken() == "compound") {
//        compound(fin);
//        cout << "<Statement>-><compound>" << endl;
//    }
//    else if (currentToken.getToken() == "if") {
//        ifKeyword(fin);
//        cout << "<Statement>-><If>" << endl;
//    }
//    else if (currentToken.getToken() == "return") {
//        returnKeyword(fin);
//        cout << "<Statement>-><Return>" << endl;
//    }
//    else if (currentToken.getToken() == "write") {
//        writeKeyword(fin);
//        cout << "<Statement>-><Write>" << endl;
//    }
//    else if (currentToken.getToken() == "read") {
//        readKeyword(fin);
//        cout << "<Statement>-><Read>" << endl;
//    }
//    else if (currentToken.getToken() == "while") {
//        whileKeyword(fin);
//        cout << "<Statement>-><While>" << endl;
//    }
//    else {
//        writeError("Line number: , error: unexpected string: " + currentToken.getLexeme() + ", expected end");
//    }
//}
//
//void parser::compound(ifstream &fin)
//{
//}
//
////Function assign
//void parser::assign(ifstream &fin)
//{
//	if (currentToken.getToken() == "identifier") {
//		currentToken.lexer(fin);
//		if (currentToken.getLexeme() == ":=") {
//			currentToken.lexer(fin);
//			expression(fin);
//			if (currentToken.getLexeme() == ";") {
//				currentToken.lexer(fin);
//			}
//			else {
//				cout << "Expected ;\n";
//			}
//		}
//		else {
//			cout << "Expected :=\n";
//		}
//	}
//	else {
//		cout << "Expected Identifier\n";
//	}
//}
//
////<write> -> write (<expression>);
//void parser::writeKeyword(ifstream &fin)
//{
//	if (currentToken.getLexeme() == "write") {
//		currentToken.lexer(fin);
//		if (currentToken.getLexeme() == "(") {
//			currentToken.lexer(fin);
//			expression(fin);
//			if (currentToken.getLexeme() == ")") {
//				currentToken.lexer(fin);
//				if (currentToken.getLexeme() == ";") {
//					currentToken.lexer(fin);
//				}
//				else {
//					cout << "Expected ;\n";
//				}
//			}else {
//				cout << "Expected )\n";
//			}
//		}
//		else {
//			cout << "Expected (\n";
//		}
//	}
//	else {
//		cout << "Expected write\n";
//	}
//	cout << "<write> -> write (<expression>);" << endl;
//
//}
//
////<Read> -> read (<IDs>);
//void parser::readKeyword(ifstream &fin)
//{
//	if (currentToken.getLexeme() == "read") {
//		currentToken.lexer(fin);
//		if (currentToken.getLexeme() == "(") {
//			currentToken.lexer(fin);
//			iDs(fin);
//			if (currentToken.getLexeme() == ")") {
//				currentToken.lexer(fin);
//				if (currentToken.getLexeme() == ";") {
//					currentToken.lexer(fin);
//				}
//				else {
//					cout << "Expected ;\n";
//				}
//			}
//			else {
//				cout << "Expected )\n";
//			}
//		}
//		else {
//			cout << "Expected (\n";
//		}
//	}
//	else {
//		cout << "Expected read\n";
//	}
//	cout << "<Read> -> read (<IDs>);" << endl;
//
//
//}
//
////while (<condition>) <Statement>
//void parser::whileKeyword(ifstream &fin) {
//	if (currentToken.getLexeme() == "while") {
//		currentToken.lexer(fin);
//		if (currentToken.getLexeme() == "(") {
//			currentToken.lexer(fin);
//			condition(fin);
//			if (currentToken.getLexeme() == ")") {
//				currentToken.lexer(fin);
//				stmt(fin);
//			}
//			else {
//				cout << "Expected )\n";
//			}
//		}
//		else {
//			cout << "Expected (\n";
//		}
//	}
//	else {
//		cout << "Expected while\n";
//	}
//	cout << "while(<condition>)<Statement>\n";
//}
//
////<return> -> return ; | return <Expression>;
//void parser::returnKeyword(ifstream &fin) {
//	if (currentToken.getLexeme() == "return") {
//		currentToken.lexer(fin);
//		if (currentToken.getLexeme() == ";") {
//			currentToken.lexer(fin);
//		}
//		else {
//			expression(fin);
//			if (currentToken.getLexeme() == ";") {
//				currentToken.lexer(fin);
//			}
//			else {
//				cout << "Expected ;\n";
//			}
//		}
//
//	}
//	else {
//		cout << "Expected return\n";
//	}
//}
//
///*
//	<Condition>-><Expression><Relop><Expression>
//*/
//void parser::condition(ifstream &fin)
//{
//    expression(fin);
//    relop(fin);
//    expression(fin);
//    cout << "<Condition>-><Expression><Relop><Expression>" << endl;
//}
//
//
//void parser::relop(ifstream &fin)
//{
//    if (currentToken.getLexeme() == "=") {
//        cout << "<Relop>-> =" << endl;
//		currentToken.lexer(fin);
//	}
//    else if (currentToken.getLexeme() == "/=") {
//        cout << "<Relop>-> /=" << endl;
//		currentToken.lexer(fin);
//	}
//    else if (currentToken.getLexeme() == ">") {
//        cout << "<Relop>-> >" << endl;
//		currentToken.lexer(fin);
//	}
//    else if (currentToken.getLexeme() == "<") {
//        cout << "<Relop>-> <" << endl;
//		currentToken.lexer(fin);
//	}
//    else if (currentToken.getLexeme() == "=>") {
//        cout << "<Relop>-> =>" << endl;
//		currentToken.lexer(fin);
//    }
//    else if (currentToken.getLexeme() == "<=") {
//        cout << "<Relop>-> <=" << endl;
//		currentToken.lexer(fin);
//    }
//    else {
//        writeError("Expected: " + currentToken.getLexeme() + ", expected end");
//    }
//}
//
///*
//E->TE'
//E'->+TE' | -TE'
//*/
//void parser::expression(ifstream &fin)
//{
//	term(fin);
//	while (currentToken.getLexeme() == "+" || currentToken.getLexeme() == "-") {
//
//		//expect(currentToken.getToken(), fin);
//		if (currentToken.getLexeme() == "+" || currentToken.getLexeme() == "-") {
//			if (currentToken.getLexeme() == "+") {
//				cout << "<Expression Prime> -> + <Term><Expression Prime>";
//			}   
//			else if (currentToken.getLexeme() == "-") {
//				cout << "<Expression Prime> -> -<Term><Expression Prime>";
//			}
//			currentToken.lexer(fin);
//			term(fin);
//			
//		}
//		else {
//			cout << "Error Expected" << endl;
//		}
//	}
//	
//	
//}
//
//void parser::term(ifstream &fin)
//{
//	factor(fin);
//	while (currentToken.getLexeme() == "*" || currentToken.getLexeme() == "/") {
//		expect(currentToken.getLexeme(), fin);
//		factor(fin);
//	}
//	if (currentToken.getLexeme() == "*") {
//		cout << "<Term Prime>->*<Factor><Term Prime>";
//	}
//	else if (currentToken.getLexeme() == "/") {
//		cout << "<Term Prime>->/<Factor><Term Prime>";
//	}
//}
//
////<Factor> -> - <Primary> || <Primary>
//void parser::factor(ifstream &fin)
//{
//	if (currentToken.getLexeme() == "-") {
//		cout << "<Factor>-> - <Primary>" << endl;
//	}
//	else {
//		cout << "<Factor>-> <Primary>" << endl;
//	}
//	currentToken.lexer(fin);
//	primary(fin);
//}
//
//// <Primary> ::= <Identifier> | < Integer> | <Identifier>[<IDs>] | (<Expression>) | <Real> | true | false
//void parser::primary(ifstream &fin)
//{
//	if (currentToken.getToken() == "identifier") {
//		cout << "<Primary>-><Identifier>" << endl;
//		currentToken.lexer(fin);
//	}
//	else if (currentToken.getToken() == "integer") {
//		cout << "<Primary>-><Integer>" << endl;
//		currentToken.lexer(fin);
//	}
//	else if (currentToken.getLexeme() == "(") {
//		currentToken.lexer(fin);
//		expression(fin);
//		if (currentToken.getLexeme() == ")") {
//			currentToken.lexer(fin);
//		}
//		else {
//			cout << "Expected )\n";
//		}
//
//		cout << "Primary -> (Expression)" << endl;
//	}
//	else if (currentToken.getToken() == "real") {
//		cout << "<Primary>-><real>" << endl;
//		currentToken.lexer(fin);
//	}
//	else if (currentToken.getToken() == "true") {
//		cout << "<Primary>-><true>" << endl;
//		currentToken.lexer(fin);
//	}
//	else if (currentToken.getToken() == "false") {
//		cout << "<Primary>-><false>" << endl;
//		currentToken.lexer(fin);
//	}
//
//	/*
//		<Identifier>[<IDs>]
//	*/
//	else {
//		cout << "<Primary>-><Identifier>[<IDs>]\n";
//		if (currentToken.getLexeme() == "[") {
//			currentToken.lexer(fin);
//			iDs(fin);
//			if (currentToken.getLexeme() == "]") {
//				currentToken.lexer(fin);
//			}
//			else {
//				cout << "Expected ]\n";
//			}
//		}
//		else {
//			cout << "Expected [\n";
//		}
//	}
//
//}
//
////void parser::empty()
////{
////    cout << "<Empty>->Epsilon" << endl;
////}
////
////
parser::~parser()
{
}
