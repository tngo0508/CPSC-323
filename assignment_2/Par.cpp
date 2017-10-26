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
	OptDeclarationList(file);
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
		Empty(file);
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
		FunctionDefinition(file);
	}
	else
		Empty(file);
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
		if (_switch)
		{
			cout << "<Opt Parameter List> -> "
				<< "<Parameter List>\n";
		}
		lexer(file);
		Lex::print();
		ParameterList(file);
	}
	else
		Empty(file);
}

void Par::ParameterList(ifstream& file)
{
	if (_switch)
	{
		cout << "<Parameter List> -> "
			<< "<Parameter> <Parameter List Prime\n";
	}
	Parameter(file);
	ParameterListPrime(file);
}

void Par::ParameterListPrime(ifstream& file)
{
	if (lexeme == ",")
	{
		if (_switch)
		{
			cout << "<Parameter List Prime> -> "
				<< ", <Parameter>\n";
		}
		lexer(file);
		Lex::print();
		ParameterList(file);
	}
	else
		Empty(file);
}

void Par::Parameter(ifstream& file)
{
	if (token == "identifier")
	{
		if (_switch)
		{
			cout << "<Parameter> -> <IDs> : <Qualifier>\n";
		}
		lexer(file);
		Lex::print();
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
		if (_switch)
		{
			cout << "<Qualifier> -> integer\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "keyword" && lexeme == "boolean")
	{
		if (_switch)
		{
			cout << "<Qualifier> -> boolean\n";
		}
		lexer(file);
		Lex::print();
	}
	else if (token == "keyword" && lexeme == "floating")
	{
		if (_switch)
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

void Par::Statement(ifstream& file)
{

}

void Par::Compound(ifstream& file)
{

}

void Par::Assign(ifstream& file)
{

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

}

void Par::Read(ifstream& file)
{

}

void Par::While(ifstream& file)
{

}

void Par::Condition(ifstream& file)
{

}

void Par::Relop(ifstream& file)
{

}

void Par::Expression(ifstream& file)
{

}

void Par::ExpressionPrime(ifstream& file)
{

}

void Par::Term(ifstream& file)
{

}

void Par::TermPrime(ifstream& file)
{

}

void Par::Factor(ifstream& file)
{

}

void Par::Primary(ifstream& file)
{

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