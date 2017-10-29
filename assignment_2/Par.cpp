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
		cout << "<RAT17F -> <Opt Function Definitions>"
			<< " %% <Opt Declaration List> <Statement List>\n";
	}
	OptFunctionDefinition(file);
	if (lexeme == "%%")
	{
		lexer(file);
		Lex::print();
		OptDeclarationList(file);
		StatementList(file);
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
			cout << "<Opt Function Definition> -> <Function Definition>\n";
		}
		lexer(file);
		Lex::print();
		FunctionDefinition(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<Opt Function Definition> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::FunctionDefinition(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Function Definition> ->"
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
			cout << "<Function Definition Prime> ->"
				<< " <Function Definition>\n";
		}
		lexer(file);
		Lex::print();
		FunctionDefinition(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<Function Definition Prime> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::Function(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Function> ->"
			<< " <Identifier> (<Opt Parameter List>)"
			<< " <Opt Declaration List> <Body>\n";
	}
	if (token == "identifier")
	{
		if (!_switch)
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
		OptParameterList(file);
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
			cout << "<Opt Parameter List> -> "
				<< "<Parameter List>\n";
		}
		ParameterList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<Opt Parameter List> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::ParameterList(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Parameter List> -> "
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
			cout << "<Parameter List Prime> -> "
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
			cout << "<Parameter List Prime> -> \u03B5\n";
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
			cout << "<Parameter> -> <IDs> : <Qualifier>\n";
		}
		IDs(file);
		if (lexeme == ":")
		{
			lexer(file);
			Lex::print();
			Qualifier(file);
		}
		else
			printError();
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
			cout << "<Qualifier> -> integer\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "keyword" && lexeme == "boolean")
	{
		if (!_switch)
		{
			cout << "<Qualifier> -> boolean\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "keyword" && lexeme == "floating")
	{
		if (!_switch)
		{
			cout << "<Qualifier> -> floating\n";
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
			cout << "<Body> -> { <Statement List> }\n";
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
			cout << "<Opt Declaration List> -> "
				<< "<Declaration List>\n";
		}
		lexer(file);
		Lex::print();
		DeclarationList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<Opt Declaration List> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::DeclarationList(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Declaration List> -> "
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
			cout << "<Declaration List Prime> -> "
				<< "<Declaration List>\n";
		}
		lexer(file);
		Lex::print();
		DeclarationList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<Declaration List Prime> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::Declaration(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Declaration> -> "
			<< "<Qualifier> <IDs>\n";
	}
	Qualifier(file);
	IDs(file);
}

void Par::IDs(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "<IDs> -> "
				<< "<IDs Prime>\n";
		}
		IDsPrime(file);
		lexer(file);
		Lex::print();
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
			cout << "<IDs> -> "
				<< "<IDs Prime>\n";
		}
		IDs(file);
		lexer(file);
		Lex::print();
	}
	else
	{
		if (!_switch)
		{
			cout << "<IDs Prime> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::StatementList(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Statement List> -> "
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
			cout << "<Statement List Prime> -> "
				<< "<Statement List>\n";
		}
		lexer(file);
		Lex::print();
		StatementList(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<IDs Prime> -> \u03B5\n";
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
			cout << "<Statement> -> "
				<< "<Compound>\n";
		}
		lexer(file);
		Lex::print();
		Compound(file);
	}
	else if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<Assign>\n";
		}
		lexer(file);
		Lex::print();
		Assign(file);
	}
	else if (lexeme == "if")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<If>\n";
		}
		lexer(file);
		Lex::print();
		If(file);
	}
	else if (lexeme == "return")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<Return>\n";
		}
		Return(file);
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "return")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<Return>\n";
		}
		lexer(file);
		Lex::print();
		Return(file);
	}
	else if (lexeme == "write")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<Write>\n";
		}
		lexer(file);
		Lex::print();
		Write(file);
	}
	else if (lexeme == "read")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<Read>\n";
		}
		lexer(file);
		Lex::print();
		Read(file);
	}
	else if (lexeme == "while")
	{
		if (!_switch)
		{
			cout << "<Statement> -> "
				<< "<While>\n";
		}
		lexer(file);
		Lex::print();
		While(file);
	}
	else
		printError();
}

void Par::Compound(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Compound> -> "
			<< "{ <StatementList> }\n";
	}
	StatementList(file);
	if (lexeme == "}")
	{
		lexer(file);
		Lex::print();
	}
	else
		printError();
}

void Par::Assign(ifstream& file)
{
	if (lexeme == ":=")
	{
		if (!_switch)
		{
			cout << "<Assign> -> "
				<< "<Identifier> := <Expression>\n";
		}
		lexer(file);
		Lex::print();
		Expression(file);
	}
	else
		printError();
}

void Par::If(ifstream& file)
{
	if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "<If> -> "
				<< "if (<Condition>) <Statement> <If Prime>\n";
		}
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

void Par::IfPrime(ifstream& file)
{
	if (lexeme == "fi")
	{
		if (!_switch)
		{
			cout << "<If Prime> -> "
				<< "fi\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "else")
	{
		if (!_switch)
		{
			cout << "<If Prime> -> "
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
	if (!_switch)
	{
		cout << "<Return> -> "
			<< "return <Return Prime>\n";
	}
	ReturnPrime(file);
}

void Par::ReturnPrime(ifstream& file)
{
	if (lexeme == ";")
	{
		if (!_switch)
		{
			cout << "<Return Prime> -> "
				<< ";\n";
		}
		lexer(file);
		Lex::print();
	}
	else
	{
		if (!_switch)
		{
			cout << "<Return Prime> -> "
				<< "<Expression> ;\n";
		}
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
}

void Par::Write(ifstream& file)
{
	if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "<Write> -> "
				<< "<write (<Expression>);\n";
		}
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

void Par::Read(ifstream& file)
{
	if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "<Read> -> "
				<< "<read (<IDs>);\n";
		}
		lexer(file);
		Lex::print();
		IDs(file);
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

void Par::While(ifstream& file)
{
	if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "<While> -> "
				<< "<while (<Condition>) <Statement>;\n";
		}
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

void Par::Condition(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Condition> -> "
			<< "<Expression> <Relop> <Expression>;\n";
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
			cout << "<Relop> -> =\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "/=")
	{
		if (!_switch)
		{
			cout << "<Relop> -> /=\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == ">")
	{
		if (!_switch)
		{
			cout << "<Relop> -> >\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "<")
	{
		if (!_switch)
		{
			cout << "<Relop> -> <\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "=>")
	{
		if (!_switch)
		{
			cout << "<Relop> -> =>\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "<=")
	{
		if (!_switch)
		{
			cout << "<Relop> -> <=\n";
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
		cout << "<Expression> -> <Term> <Expression Prime>\n";
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
			cout << "<Expression Prime> -> "
				<< "+ <Term> <Expression Prime>\n";
		}
		lexer(file);
		Lex::print();
		Term(file);
		Expression(file);
	}
	else if (lexeme == "-")
	{
		if (!_switch)
		{
			cout << "<Expression Prime> -> "
				<< "- <Term> <Expression Prime>\n";
		}
		lexer(file);
		Lex::print();
		Term(file);
		Expression(file);
	}
	else
	{
		if (!_switch)
		{
			cout << "<Expression Prime> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::Term(ifstream& file)
{
	if (!_switch)
	{
		cout << "<Term> -> <Factor> <Term Prime>\n";
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
			cout << "<Term Prime> -> * <Factor> <Term Prime>\n";
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
			cout << "<Term Prime> -> / <Factor> <Term Prime>\n";
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
			cout << "<Term Prime> -> \u03B5\n";
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
			cout << "<Factor> -> - <Primary>\n";
		}
		Primary(file);
		lexer(file);
		Lex::print();
	}
	else
	{
		if (!_switch)
		{
			cout << "<Factor> -> <Primary>\n";
		}
		Primary(file);

		lexer(file);
		Lex::print();
	}
}

void Par::Primary(ifstream& file)
{
	if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "<Prime> -> <identifier> <Primary Prime>\n";
		}
		lexer(file);
		Lex::print();
		PrimaryPrime(file);
	}
	else if (token == "integer")
	{
		if (!_switch)
		{
			cout << "<Prime> -> <integer>\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "floating")
	{
		if (!_switch)
		{
			cout << "<Prime> -> <floating>\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "<Prime> -> (<Expression>)\n";
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
			cout << "<Prime> -> true\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (lexeme == "false")
	{
		if (!_switch)
		{
			cout << "<Prime> -> false\n";
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
			cout << "<Primary Prime> -> [<IDs>]\n";
		}
		lexer(file);
		Lex::print();
	}
	else
	{
		if (!_switch)
		{
			cout << "<Primary Prime> -> \u03B5\n";
		}
		Empty(file);
	}
}

void Par::Empty(ifstream& file)
{

}

void Par::printError()
{
	cerr << "Error\n";
}

//Destructor
Par::~Par() {}