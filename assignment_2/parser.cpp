#include "parser.h"
#include "Lex.h"
#include <fstream>

using namespace std;

/*
	Parser 


*/


void parser::Parser(ifstream &file)
{
	lexer(file);
	if (!(lexeme == "EOF")) {
		print();
	}
}


parser::parser()
{
}

//void parser::Program(ifstream &fin)
//{
//    stmt(fin);
//
//}


//void parser::writeError(string s)
//{
//	cout << s << endl;
//	exit(1);
//}

//<ids> -> identifier | Identifier,IDs
//void parser::iDs(ifstream &fin) {
//	if (token == "identifier") {
//		lexer(fin);
//		if (lexeme == ",") {
//			cout << "<ids>-><identifier>,<ids>\n";
//			lexer(fin);
//			iDs(fin);
//		}
//		else {
//			cout << "Expected ,\n";
//		}
//		cout << "<ids>-><identifier>\n";
//	}
//	else {
//		cout << "Expected Identifier" << endl;
//	}
//
//}

void parser::stmt(ifstream &fin)
{
	
    if (token == "identifier") {
        assign(fin);
        cout << "<Statement>-><Assign>" << endl;
    }

	//if (a>b)
    else if (lexeme == "compound") {
        compound(fin);
        cout << "<Statement>-><compound>" << endl;
    }
    else if (lexeme == "if") {
        ifKeyword(fin);
        cout << "<Statement>-><If>" << endl;
    }
    else if (lexeme == "return") {
        returnKeyword(fin);
        cout << "<Statement>-><Return>" << endl;
    }
    else if (lexeme == "write") {
        writeKeyword(fin);
        cout << "<Statement>-><Write>" << endl;
    }
    else if (lexeme == "read") {
        readKeyword(fin);
        cout << "<Statement>-><Read>" << endl;
    }
    else if (lexeme == "while") {
        whileKeyword(fin);
        cout << "<Statement>-><While>" << endl;
    }
    else {
        writeError("Line number: , error: unexpected string: " + lexeme + ", expected end");
    }
}

void parser::compound(ifstream &fin)
{
}

//Function assign
void parser::assign(ifstream &fin)
{
	if (token == "identifier") {
		lexer(fin);
		if (lexeme == ":=") {
			lexer(fin);
			expression(fin);
			if (lexeme == ";") {
				lexer(fin);
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
	if (lexeme == "write") {
		lexer(fin);
		if (lexeme == "(") {
			lexer(fin);
			expression(fin);
			if (lexeme == ")") {
				lexer(fin);
				if (lexeme == ";") {
					lexer(fin);
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
	if (lexeme == "read") {
		lexer(fin);
		if (lexeme == "(") {
			lexer(fin);
			iDs(fin);
			if (lexeme == ")") {
				lexer(fin);
				if (lexeme == ";") {
					lexer(fin);
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
	if (lexeme == "while") {
		lexer(fin);
		if (lexeme == "(") {
			lexer(fin);
			condition(fin);
			if (lexeme == ")") {
				lexer(fin);
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

//<Return> ::=  return <Return Prime> ;
//<Return Prime> :: = ; | <Expression>;

void parser::returnKeyword(ifstream &fin) {
	if (lexeme == "return") {
		lexer(fin);
		cout << "<Return>-> return <Return Prime>\n";
		if (lexeme == ";") {
			cout << "<Return Prime>-> ;\n";
			lexer(fin);
		}
		else {
			cout << "<Return Prime>-><Expression>\n";
			expression(fin);
			if (lexeme == ";") {
				lexer(fin);
			
			}
		}

	}
	else {
		cout << "Expected return\n";
	}
}

/*
	<Condition>-><Expression><Relop><Expression>
*/
void parser::condition(ifstream &fin)
{
    expression(fin);
    relop(fin);
    expression(fin);
    cout << "<Condition>-><Expression><Relop><Expression>" << endl;
}


void parser::relop(ifstream &fin)
{
    if (lexeme == "=") {
        cout << "<Relop>-> =" << endl;
		lexer(fin);
	}
    else if (lexeme == "/=") {
        cout << "<Relop>-> /=" << endl;
		lexer(fin);
	}
    else if (lexeme == ">") {
        cout << "<Relop>-> >" << endl;
		lexer(fin);
	}
    else if (lexeme == "<") {
        cout << "<Relop>-> <" << endl;
		lexer(fin);
	}
    else if (lexeme == "=>") {
        cout << "<Relop>-> =>" << endl;
		lexer(fin);
    }
    else if (lexeme == "<=") {
        cout << "<Relop>-> <=" << endl;
		lexer(fin);
    }
    else {
        writeError("Expected: " + lexeme + ", expected end");
    }
}

/*
E->TE'
E'->+TE' | -TE'
*/
void parser::expression(ifstream &fin)
{
	cout << "<Expression> -> <Term><Expression Prime>\n";
	term(fin);
	while (lexeme == "+" || lexeme == "-") {
		if (lexeme == "+" || lexeme == "-") {
			if (lexeme == "+") {
				cout << "<Expression Prime> -> + <Term><Expression Prime>";
			}   
			else if (lexeme == "-") {
				cout << "<Expression Prime> -> -<Term><Expression Prime>";
			}
			lexer(fin);
			term(fin);
			
		}
		else {
			cout << "Error Expected" << endl;
		}
	}
	
	
}

void parser::term(ifstream &fin)
{
	cout << "<Term>-><Factor><TermPrime>\n";
	factor(fin);
	while (lexeme == "*" || lexeme == "/") {
		if (lexeme == "*" || lexeme == "/") {
			if (lexeme == "*") {
				cout << "<Term Prime>->*<Factor><Term Prime>";
			}
			else if (lexeme == "/") {
				cout << "<Term Prime>->/<Factor><Term Prime>";
			}
			lexer(fin);
			factor(fin);
		}
		else {
			cout << "Error Expected" << endl;
		}
	}
	
}

//<Factor> -> - <Primary> || <Primary>
void parser::factor(ifstream &fin)
{
	if (lexeme == "-") {
		cout << "<Factor>-> - <Primary>" << endl;
	}
	else {
		cout << "<Factor>-> <Primary>" << endl;
	}
	lexer(fin);
	primary(fin);
}

// <Primary> ::= <Identifier> | < Integer> | <Identifier>[<IDs>] | (<Expression>) | <Real> | true | false
void parser::primary(ifstream &fin)
{
	if (token == "identifier") {
		cout << "<Primary>-><Identifier>" << endl;
		lexer(fin);
	}
	else if (token == "integer") {
		cout << "<Primary>-><Integer>" << endl;
		lexer(fin);
	}
	else if (lexeme == "(") {
		lexer(fin);
		expression(fin);
		if (lexeme == ")") {
			lexer(fin);
		}
		else {
			cout << "Expected )\n";
		}

		cout << "Primary -> (Expression)" << endl;
	}
	else if (token == "real") {
		cout << "<Primary>-><real>" << endl;
		lexer(fin);
	}
	else if (token == "true") {
		cout << "<Primary>-><true>" << endl;
		lexer(fin);
	}
	else if (token == "false") {
		cout << "<Primary>-><false>" << endl;
		lexer(fin);
	}

	/*
		<Identifier>[<IDs>]
	*/
	else {
		cout << "<Primary>-><Identifier>[<IDs>]\n";
		if (lexeme == "[") {
			lexer(fin);
			iDs(fin);
			if (lexeme == "]") {
				lexer(fin);
			}
			else {
				cout << "Expected ]\n";
			}
		}
		else {
			cout << "Expected [\n";
		}
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
