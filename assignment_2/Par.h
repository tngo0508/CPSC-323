#ifndef PAR_H
#define PAR_H

#include "Lex.h"

class Par : public Lex
{
public:
	//constructor
	Par();

	//syntax rule functions
	void RAT17F(ifstream& file);
	void OptFunctionDefinition(ifstream& file);
	void FunctionDefinition(ifstream& file);
	void FunctionDefinitionPrime(ifstream& file);
	void Function(ifstream& file);
	void OptParameterList(ifstream& file);
	void ParameterList(ifstream& file);
	void ParameterListPrime(ifstream& file);
	void Parameter(ifstream& file);
	void Qualifier(ifstream& file);
	void Body(ifstream& file);
	void OptDeclarationList(ifstream& file);
	void DeclarationList(ifstream& file);
	void DeclarationListPrime(ifstream& file);
	void Declaration(ifstream& file);
	void IDs(ifstream& file);
	void IDsPrime(ifstream& file);
	void StatementList(ifstream& file);
	void StatementListPrime(ifstream& file);
	void Statement(ifstream& file);
	void Compound(ifstream& file);
	void Assign(ifstream& file);
	void If(ifstream& file);
	void IfPrime(ifstream& file);
	void Return(ifstream& file);
	void ReturnPrime(ifstream& file);
	void Write(ifstream& file);
	void Read(ifstream& file);
	void While(ifstream& file);
	void Condition(ifstream& file);
	void Relop(ifstream& file);
	void Expression(ifstream& file);
	void ExpressionPrime(ifstream& file);
	void Term(ifstream& file);
	void TermPrime(ifstream& file);
	void Factor(ifstream& file);
	void Primary(ifstream& file);
	void PrimaryPrime(ifstream& file);
	void Empty(ifstream& file);

	void printError();

	//Destructor
	~Par();

private:
	bool _switch;
};

#endif
