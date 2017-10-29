#include "Par.h"

//constructor
Par::Par()
{
	_switch = false;
}

//syntax rule functions
void Par::RAT17F(ifstream& file)
{
	lexer(file);
	Lex::print();
	if (!_switch)
	{
		cout << "\t<RAT17F -> <Opt Function Definitions>"
			<< " %% <Opt Declaration List> <Statement List>\n";
	}
	OptFunctionDefinition(file);
	if (lexeme == "%%")
	{
		lexer(file);
		Lex::print();
		OptDeclarationList(file);
		StatementList(file);
		if (!(lexeme == "EOF"))
		{
			cerr << "This is not EOF marker.\n"
				<< "Error at line " << lineNum << endl;
		}
		lineNum = 1;
	}
	else
		printError();
}

void Par::OptFunctionDefinition(ifstream& file)
{
	if (lexeme == "@")
	{
		if (!_switch)
		{
			cout << "\t<Opt Function Definition> -> "
				<< "<Function Definition>\n";
		}
		/*lexer(file);
		Lex::print();*/
		FunctionDefinition(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Opt Function Definition> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::FunctionDefinition(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Function Definition> ->"
			<< " <Function> <Function Definition Prime>\n";
	}
	Function(file);
	FunctionDefinitionPrime(file);
}

void Par::FunctionDefinitionPrime(ifstream& file)
{
	if (lexeme == "@")
	{
		if (!_switch)
		{
			cout << "\t<Function Definition Prime> ->"
				<< " <Function Definition>\n";
		}
		/*lexer(file);
		Lex::print();*/
		FunctionDefinition(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Function Definition Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Function(ifstream& file)
{
	if (lexeme == "@")
	{
		if (!_switch)
		{
			cout << "\t<Function> ->"
				<< " @ <Identifier> (<Opt Parameter List>)"
				<< " <Opt Declaration List> <Body>\n";
		}
		lexer(file);
		Lex::print();
		if (token == "identifier")
		{
			lexer(file);
			Lex::print();
			if (lexeme == "(")
			{
				lexer(file);
				Lex::print();
				OptParameterList(file);
				if (lexeme == ")")
				{
					lexer(file);
					Lex::print();
					OptDeclarationList(file);
					Body(file);
				}
				else
					printError();
			}
			else
				printError();
		}
		else
			printError();
	}
	else
		printError();

}

void Par::OptParameterList(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<Opt Parameter List> -> "
				<< "<Parameter List>\n";
		}
		/*lexer(file);
		Lex::print();*/
		ParameterList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Opt Parameter List> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::ParameterList(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Parameter List> -> "
			<< "<Parameter> <Parameter List Prime>\n";
	}
	Parameter(file);
	ParameterListPrime(file);
}

void Par::ParameterListPrime(ifstream& file)
{
	if (lexeme == ",")
	{
		if (!_switch)
		{
			cout << "\t<Parameter List Prime> -> "
				<< ", <Parameter>\n";
		}
		lexer(file);
		Lex::print();
		ParameterList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Parameter List Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Parameter(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<Parameter> -> <IDs> : <Qualifier>\n";
		}
		IDs(file);
		if (lexeme == ":")
		{
			lexer(file);
			Lex::print();
			Qualifier(file);
		}
	}
	else
		printError();
}

void Par::Qualifier(ifstream& file)
{
	if (token == "keyword" && lexeme == "integer")
	{
		if (!_switch)
		{
			cout << "\t<Qualifier> -> integer\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "keyword" && lexeme == "boolean")
	{
		if (!_switch)
		{
			cout << "\t<Qualifier> -> boolean\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "keyword" && lexeme == "floating")
	{
		if (!_switch)
		{
			cout << "\t<Qualifier> -> floating\n";
		}
		lexer(file);
		Lex::print();
	}
	else
		printError();
}

void Par::Body(ifstream& file)
{
	if (lexeme == "{")
	{
		if (!_switch)
		{
			cout << "\t<Body> -> { <Statement List> }\n";
		}
		lexer(file);
		Lex::print();
		StatementList(file);
		if (lexeme == "}")
		{
			lexer(file);
			Lex::print();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::OptDeclarationList(ifstream& file)
{
	if (lexeme == "integer" || lexeme == "boolean" || lexeme == "floating")
	{
		if (!_switch)
		{
			cout << "\t<Opt Declaration List> -> <Declaration List>\n";
		}
		/*lexer(file);
		Lex::print();*/
		DeclarationList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Opt Declaration List> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::DeclarationList(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Declaration List> -> "
			<< "<Declaration> ; <Declaration List Prime>\n";
	}
	Declaration(file);
	if (lexeme == ";")
	{
		lexer(file);
		Lex::print();
		DeclarationListPrime(file);
	}
	else
		printError();
}

void Par::DeclarationListPrime(ifstream& file)
{
	if (lexeme == "integer" || lexeme == "boolean" || lexeme == "floating")
	{
		if (!_switch)
		{
			cout << "\t<Declaration List Prime> -> "
				<< "<Declaration List>\n";
		}
		/*lexer(file);
		Lex::print();*/
		DeclarationList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Declaration List Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Declaration(ifstream& file)
{
	if (lexeme == "integer" || lexeme == "boolean" || lexeme == "floating")
	{
		if (!_switch)
		{
			cout << "\t<Declaration> -> "
				<< "<Qualifier> <IDs>\n";
		}
		/*lexer(file);
		Lex::print();*/
		Qualifier(file);
		IDs(file);
	}
	else
		printError();
}

void Par::IDs(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<IDs> -> "
				<< "<identifier> <IDs Prime>\n";
		}
		lexer(file);
		Lex::print();
		IDsPrime(file);
	}
	else
		printError();
}

void Par::IDsPrime(ifstream& file)
{
	if (lexeme == ",")
	{
		if (!_switch)
		{
			cout << "\t<IDsPrime> -> "
				<< ", <IDs>\n";
		}
		lexer(file);
		Lex::print();
		IDs(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<IDs Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::StatementList(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Statement List> -> "
			<< "<Statement> <Statement List Prime>\n";
	}
	Statement(file);
	StatementListPrime(file);
}

void Par::StatementListPrime(ifstream& file)
{
	if (lexeme == "{" || token == "identifier" || lexeme == "if" ||
		lexeme == "return" || lexeme == "write" || lexeme == "write" ||
		lexeme == "read" || lexeme == "while")
	{
		if (!_switch)
		{
			cout << "\t<Statement List Prime> -> "
				<< "<Statement List>\n";
		}
		/*lexer(file);
		Lex::print();*/
		StatementList(file);
	}
	else
	{
		if (!_switch && !(lexeme == "EOF"))
		{
			cout << "\t<Statement List Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Statement(ifstream& file)
{
	if (lexeme == "{")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Compound>\n";
		}
		/*lexer(file);
		Lex::print();*/
		Compound(file);
	}
	else if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Assign>\n";
		}
		/*lexer(file);
		Lex::print();*/
		Assign(file);
	}
	else if (lexeme == "if")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<If>\n";
		}
		/*lexer(file);
		Lex::print();*/
		If(file);
	}
	else if (lexeme == "return")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Return>\n";
		}
		/*lexer(file);
		Lex::print();*/
		Return(file);
	}
	else if (lexeme == "write")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Write>\n";
		}
		/*lexer(file);
		Lex::print();*/
		Write(file);
	}
	else if (lexeme == "read")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Read>\n";
		}
		/*lexer(file);
		Lex::print()*/;
		Read(file);
	}
	else if (lexeme == "while")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<While>\n";
		}
		/*lexer(file);
		Lex::print()*/;
		While(file);
	}
	else
		printError();
}

void Par::Compound(ifstream& file)
{
	if (lexeme == "{")
	{
		if (!_switch)
		{
			cout << "\t<Compound> -> "
				<< "{ <StatementList> }\n";
		}
		lexer(file);
		Lex::print();
		StatementList(file);
		if (lexeme == "}")
		{
			lexer(file);
			Lex::print();
		}
	}
	else
		printError();
}

void Par::Assign(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<Assign> -> "
				<< "<Identifier> := <Expression>;\n";
		}
		lexer(file);
		Lex::print();
		if (lexeme == ":=")
		{
			lexer(file);
			Lex::print();
			Expression(file);
			if (lexeme == ";")
			{
				lexer(file);
				Lex::print();
			}
			else
				printError();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::If(ifstream& file)
{
	if (lexeme == "if")
	{
		if (!_switch)
		{
			cout << "\t<If> -> "
				<< "if (<Condition>) <Statement> <If Prime>\n";
		}
		lexer(file);
		Lex::print();
		if (lexeme == "(")
		{
			lexer(file);
			Lex::print();
			Condition(file);
			if (lexeme == ")")
			{
				lexer(file);
				Lex::print();
				Statement(file);
				IfPrime(file);
			}
			else
				printError();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::IfPrime(ifstream& file)
{
	if (lexeme == "fi")
	{
		if (!_switch)
		{
			cout << "\t<If Prime> -> "
				<< "fi\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "else")
	{
		if (!_switch)
		{
			cout << "\t<If Prime> -> "
				<< "else <Statement> fi\n";
		}
		lexer(file);
		Lex::print();
		Statement(file);
		if (lexeme == "fi")
		{
			lexer(file);
			Lex::print();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::Return(ifstream& file)
{
	if (lexeme == "return")
	{
		if (!_switch)
		{
			cout << "\t<Return> -> "
				<< "return <Return Prime>\n";
		}
		lexer(file);
		Lex::print();
		ReturnPrime(file);
	}
	else
		printError();
}

void Par::ReturnPrime(ifstream& file)
{
	if (lexeme == ";")
	{
		if (!_switch)
		{
			cout << "\t<Return Prime> -> "
				<< ";\n";
		}
		lexer(file);
		Lex::print();
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Return Prime> -> "
				<< "<Expression>;\n";
		}
		/*lexer(file);
		Lex::print();*/
		Expression(file);
		if (lexeme == ";")
		{
			lexer(file);
			Lex::print();
		}
		else
			printError();
	}
}

void Par::Write(ifstream& file)
{
	if (lexeme == "write")
	{
		if (!_switch)
		{
			cout << "\t<Write> -> "
				<< "<write (<Expression>);\n";
		}
		lexer(file);
		Lex::print();
		if (lexeme == "(")
		{
			lexer(file);
			Lex::print();
			Expression(file);
			if (lexeme == ")")
			{
				lexer(file);
				Lex::print();
				if (lexeme == ";")
				{
					lexer(file);
					Lex::print();
				}
				else
					printError();
			}
			else
				printError();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::Read(ifstream& file)
{
	if (lexeme == "read")
	{
		if (!_switch)
		{
			cout << "\t<Read> -> "
				<< "read (<IDs>);\n";
		}
		lexer(file);
		Lex::print();
		if (lexeme == "(")
		{
			lexer(file);
			Lex::print();
			IDs(file);
			if (lexeme == ")")
			{
				lexer(file);
				Lex::print();
				if (lexeme == ";")
				{
					lexer(file);
					Lex::print();
				}
				else
					printError();
			}
			else
				printError();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::While(ifstream& file)
{
	if (lexeme == "while")
	{
		if (!_switch)
		{
			cout << "\t<While> -> "
				<< "<while (<Condition>) <Statement>\n";
		}
		lexer(file);
		Lex::print();
		if (lexeme == "(")
		{
			lexer(file);
			Lex::print();
			Condition(file);
			if (lexeme == ")")
			{
				lexer(file);
				Lex::print();
				Statement(file);
			}
			else
				printError();
		}
		else
			printError();
	}
	else
		printError();
}

void Par::Condition(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Condition> -> "
			<< "<Expression> <Relop> <Expression>\n";
	}
	Expression(file);
	Relop(file);
	Expression(file);
}

void Par::Relop(ifstream& file)
{
	if (lexeme == "=")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> =\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "/=")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> /=\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == ">")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> >\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "<")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> <\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "=>")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> =>\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "<=")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> <=\n";
		}
		lexer(file);
		Lex::print();
	}
	else
		printError();
}

void Par::Expression(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Expression> -> <Term> <Expression Prime>\n";
	}
	Term(file);
	ExpressionPrime(file);
}

void Par::ExpressionPrime(ifstream& file)
{
	if (lexeme == "+")
	{
		if (!_switch)
		{
			cout << "\t<Expression Prime> -> "
				<< "+ <Term> <Expression Prime>\n";
		}
		lexer(file);
		Lex::print();
		Term(file);
		ExpressionPrime(file);
	}
	else if (lexeme == "-")
	{
		if (!_switch)
		{
			cout << "\t<Expression Prime> -> "
				<< "- <Term> <Expression Prime>\n";
		}
		lexer(file);
		Lex::print();
		Term(file);
		ExpressionPrime(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Expression Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Term(ifstream& file)
{
	if (!_switch)
	{
		cout << "\t<Term> -> <Factor> <Term Prime>\n";
	}
	Factor(file);
	TermPrime(file);
}

void Par::TermPrime(ifstream& file)
{
	if (lexeme == "*")
	{
		if (!_switch)
		{
			cout << "\t<Term Prime> -> * <Factor> <Term Prime>\n";
		}
		lexer(file);
		Lex::print();
		Factor(file);
		TermPrime(file);
	}
	else if (lexeme == "/")
	{
		if (!_switch)
		{
			cout << "\t<Term Prime> -> / <Factor> <Term Prime>\n";
		}
		lexer(file);
		Lex::print();
		Factor(file);
		TermPrime(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Term Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Factor(ifstream& file)
{
	if (lexeme == "-")
	{
		if (!_switch)
		{
			cout << "\t<Factor> -> - <Primary>\n";
		}
		lexer(file);
		Lex::print();
		Primary(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Factor> -> <Primary>\n";
		}
		/*lexer(file);
		Lex::print();*/
		Primary(file);
	}
}

void Par::Primary(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<Primary> -> <identifier> <Primary Prime>\n";
		}
		lexer(file);
		Lex::print();
		PrimaryPrime(file);
	}
	else if (token == "integer")
	{
		if (!_switch)
		{
			cout << "\t<Primary> -> <integer>\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "floating")
	{
		if (!_switch)
		{
			cout << "\t<Primary> -> <floating>\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "\t<Primary> -> (<Expression>)\n";
		}
		lexer(file);
		Lex::print();
		Expression(file);
		if (lexeme == ")")
		{
			lexer(file);
			Lex::print();
		}
		else
			printError();
	}
	else if (lexeme == "true")
	{
		if (!_switch)
		{
			cout << "\t<Prime> -> true\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "false")
	{
		if (!_switch)
		{
			cout << "\t<Prime> -> false\n";
		}
		lexer(file);
		Lex::print();
	}
	else
		printError();
}

void Par::PrimaryPrime(ifstream& file)
{
	if (lexeme == "[")
	{
		if (!_switch)
		{
			cout << "\t<Primary Prime> -> [<IDs>]\n";
		}
		lexer(file);
		Lex::print();
		IDs(file);
		if (lexeme == "]")
		{
			lexer(file);
			Lex::print();
		}
		else
			printError();
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Primary Prime> -> " << "Epsilon" << endl;
		}
		Empty(file);
	}
}

void Par::Empty(ifstream& file)
{

}

void Par::printError()
{
	cerr << "Error at line " << lineNum <<endl;
	lineNum = 1;
}

//Destructor
Par::~Par() {}