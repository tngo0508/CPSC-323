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
	void RAT17F() const;
	void OptFunctionDefinition()const;
	void FunctionDefinition() const;
	void FunctionDefinitionPrime() const;
	void Function() const;
	void OptParameterList() const;
	void ParameterList() const;
	void ParameterListPrime() const;
	void Parameter() const;
	void Qualifier() const;
	void Body() const;
	void OptDeclarationList() const;
	void DeclarationList() const;
	void DeclarationListPrime() const;
	void Declaration() const;
	void IDs() const;
	void IDsPrime() const;
	void StatementList() const;
	void StatementListPrime() const;
	void Statement() const;
	void Compound() const;
	void Assign() const;
	void If() const;
	void IfPrime() const;
	void Return() const;
	void ReturnPrime() const;
	void Write() const;
	void Read() const;
	void While() const;
	void Condition() const;
	void Relop() const;
	void Expression() const;
	void ExpressionPrime() const;
	void Term() const;
	void TermPrime() const;
	void Factor() const;
	void Primary() const;
	void Empty() const;

	//Destructor
	~Par();
private:
	
};

#endif
