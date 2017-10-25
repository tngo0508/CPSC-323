#include "Par.h"

//ructor
Par::Par()
{}

//parser
void Par::parser()
{

}

//syntax rule functions
void Par::RAT17F(ifstream& file)
{
	lexer(file);
}

void Par::OptFunctionDefinition(ifstream& file)
{

}

void Par::FunctionDefinition(ifstream& file)
{

}

void Par::FunctionDefinitionPrime(ifstream& file)
{

}

void Par::Function(ifstream& file)
{

}

void Par::OptParameterList(ifstream& file)
{

}

void Par::ParameterList(ifstream& file)
{

}

void Par::ParameterListPrime(ifstream& file)
{

}

void Par::Parameter(ifstream& file)
{

}

void Par::Qualifier(ifstream& file)
{

}

void Par::Body(ifstream& file)
{

}

void Par::OptDeclarationList(ifstream& file)
{

}

void Par::DeclarationList(ifstream& file)
{

}

void Par::DeclarationListPrime(ifstream& file)
{

}

void Par::Declaration(ifstream& file)
{

}

void Par::IDs(ifstream& file)
{

}

void Par::IDsPrime(ifstream& file)
{

}

void Par::StatementList(ifstream& file)
{

}

void Par::StatementListPrime(ifstream& file)
{

}

//need to check token or lexeme
void Par::Statement(ifstream& file)
{
	if (token == "identifier") {
		cout << "<Statement>-><Assign>" << endl;
		Assign(file);
	}
	else if (lexeme == "compound") {
		cout << "<Statement>-><compound>" << endl;
		Compound(file);
	}
	else if (lexeme == "if") {
		cout << "<Statement>-><If>" << endl;
		If(file);
	}
	else if (lexeme == "return") {
		cout << "<Statement>-><Return>" << endl;
		Return(file);
	}
	else if (lexeme == "write") {
		cout << "<Statement>-><Write>" << endl;
		Write(file);
	}
	else if (lexeme == "read") {
		cout << "<Statement>-><Read>" << endl;
		Read(file);
	}
	else if (lexeme == "while") {
		cout << "<Statement>-><While>" << endl;
		While(file);
	}
	else {
		cout << ("Line number: , error: unexpected string: " + lexeme + ", expected end") << endl;
	}
}

void Par::Compound(ifstream& file)
{
	cout << "<Statement>-><Assign>" << endl;

}

void Par::Assign(ifstream& file)
{
	if (token == "identifier") {
		lexer(file);
		if (lexeme == ":=") {
			lexer(file);
			Expression(file);
			if (lexeme == ";") {
				lexer(file);
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

void Par::If(ifstream& file)
{

}

void Par::IfPrime(ifstream& file)
{

}

void Par::Return(ifstream& file)
{

}

void Par::ReturnPrime(ifstream& file)
{

}

void Par::Write(ifstream& file)
{
	if (lexeme == "write") {
		lexer(file);
		if (lexeme == "(") {
			cout << "<Read> -> read (<IDs>);" << endl;
			lexer(file);
			Expression(file);
			if (lexeme == ")") {
				lexer(file);
				if (lexeme == ";") {
					lexer(file);
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
		cout << "Expected write\n";
	}
}

void Par::Read(ifstream& file)
{
	if (lexeme == "read") {
		lexer(file);
		if (lexeme == "(") {
			cout << "<Read> -> read (<IDs>);" << endl;
			lexer(file);
			IDs(file);
			if (lexeme == ")") {
				lexer(file);
				if (lexeme == ";") {
					lexer(file);
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
}

void Par::While(ifstream& file)
{
	if (lexeme == "while") {
		lexer(file);
		if (lexeme == "(") {
			cout << "while(<condition>)<Statement>\n";
			lexer(file);
			Condition(file);
			if (lexeme == ")") {
				lexer(file);
				Statement(file);
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
}

void Par::Condition(ifstream& file)
{
	Expression(file);
	Relop(file);
	Expression(file);
	cout << "<Condition>-><Expression><Relop><Expression>" << endl;
}

void Par::Relop(ifstream& file)
{
	if (lexeme == "=") {
		cout << "<Relop>-> =" << endl;
		lexer(file);
	}
	else if (lexeme == "/=") {
		cout << "<Relop>-> /=" << endl;
		lexer(file);
	}
	else if (lexeme == ">") {
		cout << "<Relop>-> >" << endl;
		lexer(file);
	}
	else if (lexeme == "<") {
		cout << "<Relop>-> <" << endl;
		lexer(file);
	}
	else if (lexeme == "=>") {
		cout << "<Relop>-> =>" << endl;
		lexer(file);
	}
	else if (lexeme == "<=") {
		cout << "<Relop>-> <=" << endl;
		lexer(file);
	}
	else {
		cout << "Error" << endl;
	}
}

void Par::Expression(ifstream& file)
{
	cout << "<Expression> -> <Term><Expression Prime>\n";
	Term(file);
	ExpressionPrime(file);
}

void Par::ExpressionPrime(ifstream& file)
{
	

}

void Par::Term(ifstream& file)
{
	cout << "<Term>-><Factor><TermPrime>\n";
	Factor(file);
	TermPrime(file);
}

void Par::TermPrime(ifstream& file)
{

}

void Par::Factor(ifstream& file)
{

}

//need to check token or lexeme
void Par::Primary(ifstream& file)
{
	if (token == "identifier") {
		cout << "<Primary>-><Identifier>" << endl;
		lexer(file);
	}
	else if (token == "integer") {
		cout << "<Primary>-><Integer>" << endl;
		lexer(file);
	}
	else if (lexeme == "(") {
		lexer(file);
		Expression(file);
		if (lexeme == ")") {
			lexer(file);
		}
		else {
			cout << "Expected )\n";
		}

		cout << "Primary -> (Expression)" << endl;
	}
	else if (token == "real") {
		cout << "<Primary>-><real>" << endl;
		lexer(file);
	}
	else if (token == "true") {
		cout << "<Primary>-><true>" << endl;
		lexer(file);
	}
	else if (token == "false") {
		cout << "<Primary>-><false>" << endl;
		lexer(file);
	}

	/*
	<Identifier>[<IDs>]
	*/
	else {
		cout << "<Primary>-><Identifier>[<IDs>]\n";
		if (lexeme == "[") {
			lexer(file);
			IDs(file);
			if (lexeme == "]") {
				lexer(file);
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

void Par::Empty(ifstream& file)
{

}

//Destructor
Par::~Par(){}
