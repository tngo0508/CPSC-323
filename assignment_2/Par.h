#ifndef PAR_H
#define PAR_H

#include "Lex.h"

class Par : public Lex 
{
public:
	//constructor
	Par();

	//parser
	void parser();

	//syntax rule functions
	void RAT17F(ifstream& file) const;
	void OptFunctionDefinition(ifstream& file)const;
	void FunctionDefinition(ifstream& file) const;
	void FunctionDefinitionPrime(ifstream& file) const;
	void Function(ifstream& file) const;
	void OptParameterList(ifstream& file) const;
	void ParameterList(ifstream& file) const;
	void ParameterListPrime(ifstream& file) const;
	void Parameter(ifstream& file) const;
	void Qualifier(ifstream& file) const;
	void Body(ifstream& file) const;
	void OptDeclarationList(ifstream& file) const;
	void DeclarationList(ifstream& file) const;
	void DeclarationListPrime(ifstream& file) const;
	void Declaration(ifstream& file) const;
	void IDs(ifstream& file) const;
	void IDsPrime(ifstream& file) const;
	void StatementList(ifstream& file) const;
	void StatementListPrime(ifstream& file) const;
	void Statement(ifstream& file) const;
	void Compound(ifstream& file) const;
	void Assign(ifstream& file) const;
	void If(ifstream& file) const;
	void IfPrime(ifstream& file) const;
	void Return(ifstream& file) const;
	void ReturnPrime(ifstream& file) const;
	void Write(ifstream& file) const;
	void Read(ifstream& file) const;
	void While(ifstream& file) const;
	void Condition(ifstream& file) const;
	void Relop(ifstream& file) const;
	void Expression(ifstream& file) const;
	void ExpressionPrime(ifstream& file) const;
	void Term(ifstream& file) const;
	void TermPrime(ifstream& file) const;
	void Factor(ifstream& file) const;
	void Primary(ifstream& file) const;
	void Empty(ifstream& file) const;

	//Destructor
	~Par();

private:
	
};

#endif
