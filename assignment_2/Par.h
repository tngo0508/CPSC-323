#ifndef PAR_H
#define PAR_H

#include "Lex.h"

class Par : public Lex
{
public:
	//constructor
	Par();

	//syntax rule functions
	void RAT17F(ifstream& infile, ofstream& outfile);
	void OptFunctionDefinition(ifstream& infile, ofstream& outfile);
	void FunctionDefinition(ifstream& infile, ofstream& outfile);
	void FunctionDefinitionPrime(ifstream& infile, ofstream& outfile);
	void Function(ifstream& infile, ofstream& outfile);
	void OptParameterList(ifstream& infile, ofstream& outfile);
	void ParameterList(ifstream& infile, ofstream& outfile);
	void ParameterListPrime(ifstream& infile, ofstream& outfile);
	void Parameter(ifstream& infile, ofstream& outfile);
	void Qualifier(ifstream& infile, ofstream& outfile);
	void Body(ifstream& infile, ofstream& outfile);
	void OptDeclarationList(ifstream& infile, ofstream& outfile);
	void DeclarationList(ifstream& infile, ofstream& outfile);
	void DeclarationListPrime(ifstream& infile, ofstream& outfile);
	void Declaration(ifstream& infile, ofstream& outfile);
	void IDs(ifstream& infile, ofstream& outfile);
	void IDsPrime(ifstream& infile, ofstream& outfile);
	void StatementList(ifstream& infile, ofstream& outfile);
	void StatementListPrime(ifstream& infile, ofstream& outfile);
	void Statement(ifstream& infile, ofstream& outfile);
	void Compound(ifstream& infile, ofstream& outfile);
	void Assign(ifstream& infile, ofstream& outfile);
	void If(ifstream& infile, ofstream& outfile);
	void IfPrime(ifstream& infile, ofstream& outfile);
	void Return(ifstream& infile, ofstream& outfile);
	void ReturnPrime(ifstream& infile, ofstream& outfile);
	void Write(ifstream& infile, ofstream& outfile);
	void Read(ifstream& infile, ofstream& outfile);
	void While(ifstream& infile, ofstream& outfile);
	void Condition(ifstream& infile, ofstream& outfile);
	void Relop(ifstream& infile, ofstream& outfile);
	void Expression(ifstream& infile, ofstream& outfile);
	void ExpressionPrime(ifstream& infile, ofstream& outfile);
	void Term(ifstream& infile, ofstream& outfile);
	void TermPrime(ifstream& infile, ofstream& outfile);
	void Factor(ifstream& infile, ofstream& outfile);
	void Primary(ifstream& infile, ofstream& outfile);
	void PrimaryPrime(ifstream& infile, ofstream& outfile);
	void Empty(ifstream& infile, ofstream& outfile);

	void printError(ofstream& outfile);
	void setSwitch(const bool number);
	void print(ofstream& outfile);
	//Destructor
	~Par();

private:
	bool _switch;
};

#endif