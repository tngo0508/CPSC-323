#include "Par.h"
#include <iostream>
#include <string>
#define BLANK -9999

using namespace std;

int memory_address = 10000;
bool isFromRead = false;
int count_sym = 0;
bool isFromDeclaration = false;
string prevLexeme;
string temp;

//constructor
Par::Par()
{
	_switch = true; //Used to turn on/off syntax rules
	sym_idx = 0;
	sym_table[sym_idx].mem_loc = 0;
	instr_idx = 1;
}

bool Par::check_sym(string lexeme)
{
	for (int i = 0; i < sym_idx; i++)
	{
		if (lexeme == sym_table[i].id) {
			if (isFromDeclaration == true)
				count_sym++;
			return true;
		}

	}
	return false;
}

void Par::gen_sym(string lexeme, string id_type)
{
	sym_table[sym_idx].id = lexeme;
	sym_table[sym_idx].mem_loc = memory_address;
	sym_table[sym_idx].idType = id_type;
	sym_idx++;
	memory_address++;
}

void Par::printSym() const
{
	cout << "\nSYMBOL TABLE\n";
	for (int i = 0; i < sym_idx; i++)
	{
		cout << sym_table[i].id << " " << sym_table[i].mem_loc << " "
			<< sym_table[i].idType;
		cout << endl;
	}
}

int Par::get_address(string save) const
{
	int address = 0;
	for (int i = 0; i < sym_idx; i++) {
		if (sym_table[i].id == save) {
			address = sym_table[i].mem_loc;
		}
	}
	return address;
}

void Par::backPatch(int jump_addr)
{
	int addr = jumpstack.top();
	jumpstack.pop();
	instr_table[addr].oprnd = jump_addr;
}

void Par::gen_instr(string op, int oprnd)
{
	instr_table[instr_idx].address = instr_idx;
	instr_table[instr_idx].op = op;
	instr_table[instr_idx].oprnd = oprnd;
	instr_idx++;
}

void Par::printInstr() const
{
	string a;
	cout << "\nINSTRUCTION TABLE\n";
	for (int i = 1; i < instr_idx; i++)
	{
		if (instr_table[i].oprnd == BLANK) {
			a = "";
			cout << instr_table[i].address << " " << instr_table[i].op << " "
				<< a;
			cout << endl;
		}
		else {
			cout << instr_table[i].address << " " << instr_table[i].op << " "
				<< instr_table[i].oprnd;
			cout << endl;
		}

	}
}

string Par::getType(string input) const
{
	string a = "";
	for (int i = 0; i < sym_idx; i++) {
		if (sym_table[i].id == input) {
			a = sym_table[i].idType;
		}
	}

	if (input == "true" || input == "false") {
		a = "boolean";
	}
	return a;

}

/*
Check Type of current lexeme vs previous lexeme
if does not match, print error
*/
void Par::checkTypeMatch(string prevLexeme, string lexeme)
{
	if (getType(prevLexeme) == "boolean" || getType(lexeme) == "boolean") {
		cerr << "No Arithmetic operations are allowed for booleans." << endl;
		system("pause");
		exit(1);
	}


}

//Function to turn on/off syntax rules
void Par::setSwitch(const bool number)
{
	_switch = number;
}

//Print token and lexeme
void Par::print(ofstream& outfile)
{
	if (!_switch)
	{
		Lex::print();
		outfile << "Token: " << left << setw(20) << this->token
			<< "Lexeme: " << setw(20) << this->lexeme << endl;
	}
}

//syntax rule functions
void Par::RAT17F(ifstream& infile, ofstream& outfile)
{
	//Get the first token in file.txt
	lexer(infile);
	print(outfile);
	if (!_switch)
	{
		cout << "\t<RAT17F> -> "
			<< " %% <Opt Declaration List> <Statement List>\n";
		outfile << "\t<RAT17F> -> "
			<< " %% <Opt Declaration List> <Statement List>\n";
	}
	if (lexeme == "%%")
	{
		lexer(infile);
		print(outfile);
		OptDeclarationList(infile, outfile);
		StatementList(infile, outfile);
		if (!(lexeme == "EOF"))
		{
			outfile << "This is not EOF marker.\n"
				<< "Error at line " << lineNum << endl
				<< "Only <Opt Declaration List> <StatementList> is allowed after %%.\n";
			cerr << "This is not EOF marker.\n"
				<< "Error at line " << lineNum << endl
				<< "Only <Opt Declaration List> <StatementList> is allowed after %%.\n";
			system("Pause");
			exit(1);
		}

		//reset the line number after finishing syntax checking for a file.txt
		lineNum = 1;
	}
	else
	{
		printError(outfile);
		outfile << "Invalid separator, '%%' is expected "
			<< " after function definitions and before declaration list.\n";
		cerr << "Invalid separator, '%%' is expected "
			<< " after function definitions and before declaration list.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Qualifier(ifstream& infile, ofstream& outfile)
{
	if (token == "keyword" && lexeme == "integer")
	{
		current_type = lexeme;
		if (!_switch)
		{
			cout << "\t<Qualifier> -> integer\n";
			outfile << "\t<Qualifier> -> integer\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (token == "keyword" && lexeme == "boolean")
	{
		current_type = lexeme;
		if (!_switch)
		{
			cout << "\t<Qualifier> -> boolean\n";
			outfile << "\t<Qualifier> -> boolean\n";
		}
		lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Qualifier syntax error\n"
			<< "Invalid keyword\n";
		outfile << "'integer', 'boolean' keyword is expected"
			<< " after ':'.\n";
		cerr << "Qualifier syntax error\n"
			<< "Invalid keyword\n";
		cerr << "'integer', 'boolean' keyword is expected"
			<< " after ':'.\n";
		system("Pause");
		exit(1);
	}
}

void Par::OptDeclarationList(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "integer" || lexeme == "boolean")
	{
		if (!_switch)
		{
			cout << "\t<Opt Declaration List> -> <Declaration List>\n";
			outfile << "\t<Opt Declaration List> -> <Declaration List>\n";
		}
		DeclarationList(infile, outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Opt Declaration List> -> " << "Epsilon" << endl;
			outfile << "\t<Opt Declaration List> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::DeclarationList(ifstream& infile, ofstream& outfile)
{
	isFromDeclaration = true;
	if (!_switch)
	{
		cout << "\t<Declaration List> -> "
			<< "<Declaration> ; <Declaration List Prime>\n";
		outfile << "\t<Declaration List> -> "
			<< "<Declaration> ; <Declaration List Prime>\n";
	}
	Declaration(infile, outfile);
	if (lexeme == ";")
	{
		lexer(infile);
		print(outfile);
		DeclarationListPrime(infile, outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Declaration List syntax error\n";
		outfile << "Invalid separator, ';' is expected"
			<< " at the end of declaration.\n";
		cerr << "Declaration List syntax error\n";
		cerr << "Invalid separator, ';' is expected"
			<< " at the end of declaration.\n";
		system("Pause");
		exit(1);
	}
	isFromDeclaration = false;
}

void Par::DeclarationListPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "integer" || lexeme == "boolean")
	{
		if (!_switch)
		{
			cout << "\t<Declaration List Prime> -> "
				<< "<Declaration List>\n";
			outfile << "\t<Declaration List Prime> -> "
				<< "<Declaration List>\n";
		}
		DeclarationList(infile, outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Declaration List Prime> -> " << "Epsilon" << endl;
			outfile << "\t<Declaration List Prime> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::Declaration(ifstream& infile, ofstream& outfile)
{
	if (!_switch)
	{
		cout << "\t<Declaration> -> "
			<< "<Qualifier> <IDs>\n";
		outfile << "\t<Declaration> -> "
			<< "<Qualifier> <IDs>\n";
	}
	Qualifier(infile, outfile);
	IDs(infile, outfile);
}

void Par::IDs(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!check_sym(lexeme) && isFromRead == false)
		{
			gen_sym(lexeme, current_type);
		}
		else if (!check_sym(lexeme) && isFromRead == true)
		{
			cerr << "Identifier " << lexeme << " has not been declared yet.\n";
			system("pause");
			exit(1);
		}
		if (count_sym == 2) {
			cerr << "Identifier " << lexeme << " is already declared.\n";
			system("pause");
			exit(1);
		}

		if (!_switch)
		{
			cout << "\t<IDs> -> "
				<< "<identifier> <IDs Prime>\n";
			outfile << "\t<IDs> -> "
				<< "<identifier> <IDs Prime>\n";
		}
		lexer(infile);
		print(outfile);
		IDsPrime(infile, outfile);
	}
	else
	{
		printError(outfile);
		outfile << "IDs syntax error\n";
		outfile << "Invalid token, <identifier> is expected"
			" after '(' or ','.\n";
		cerr << "IDs syntax error\n";
		cerr << "Invalid token, <identifier> is expected"
			" after '(' or ','.\n";
		system("Pause");
		exit(1);
	}
}

void Par::IDsPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == ",")
	{
		if (!_switch)
		{
			cout << "\t<IDsPrime> -> "
				<< ", <IDs>\n";
			outfile << "\t<IDsPrime> -> "
				<< ", <IDs>\n";
		}
		lexer(infile);
		print(outfile);
		IDs(infile, outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<IDs Prime> -> " << "Epsilon" << endl;
			outfile << "\t<IDs Prime> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::StatementList(ifstream& infile, ofstream& outfile)
{
	if (!_switch)
	{
		cout << "\t<Statement List> -> "
			<< "<Statement> <Statement List Prime>\n";
		outfile << "\t<Statement List> -> "
			<< "<Statement> <Statement List Prime>\n";
	}
	Statement(infile, outfile);
	StatementListPrime(infile, outfile);
}

void Par::StatementListPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "{" || token == "identifier" || lexeme == "if" ||
		lexeme == "return" || lexeme == "write" || lexeme == "write" ||
		lexeme == "read" || lexeme == "while")
	{
		if (!_switch)
		{
			cout << "\t<Statement List Prime> -> "
				<< "<Statement List>\n";
			outfile << "\t<Statement List Prime> -> "
				<< "<Statement List>\n";
		}
		StatementList(infile, outfile);
	}
	else
	{
		if (!_switch && !(lexeme == "EOF"))
		{
			cout << "\t<Statement List Prime> -> " << "Epsilon" << endl;
			outfile << "\t<Statement List Prime> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::Statement(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "{")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Compound>\n";
			outfile << "\t<Statement> -> "
				<< "<Compound>\n";
		}
		Compound(infile, outfile);
	}
	else if (token == "identifier")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Assign>\n";
			outfile << "\t<Statement> -> "
				<< "<Assign>\n";
		}
		Assign(infile, outfile);
	}
	else if (lexeme == "if")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<If>\n";
			outfile << "\t<Statement> -> "
				<< "<If>\n";
		}
		If(infile, outfile);
	}
	else if (lexeme == "return")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Return>\n";
			outfile << "\t<Statement> -> "
				<< "<Return>\n";
		}
		Return(infile, outfile);
	}
	else if (lexeme == "write")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Write>\n";
			outfile << "\t<Statement> -> "
				<< "<Write>\n";
		}
		Write(infile, outfile);
	}
	else if (lexeme == "read")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<Read>\n";
			outfile << "\t<Statement> -> "
				<< "<Read>\n";
		}
		Read(infile, outfile);
	}
	else if (lexeme == "while")
	{
		if (!_switch)
		{
			cout << "\t<Statement> -> "
				<< "<While>\n";
			outfile << "\t<Statement> -> "
				<< "<While>\n";
		}
		While(infile, outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Statement syntax error\n";
		outfile << "Invalid token or keyword or separator\n";
		outfile << "<identifier>, 'if', 'return', 'write', 'read','while' "
			<< "keyword or '{'is expected at the beginning of a statement.\n";
		cerr << "Statement syntax error\n";
		cerr << "Invalid token or keyword or separator\n";
		cerr << "<identifier>, 'if', 'return', 'write', 'read','while' "
			<< "keyword or '{'is expected at the beginning of a statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Compound(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "{")
	{
		if (!_switch)
		{
			cout << "\t<Compound> -> "
				<< "{ <StatementList> }\n";
			outfile << "\t<Compound> -> "
				<< "{ <StatementList> }\n";
		}
		lexer(infile);
		print(outfile);
		StatementList(infile, outfile);
		if (lexeme == "}")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Compound syntax error\n";
			outfile << "Invalid separator, '}' is expected"
				<< " at the end of statement list(code block).\n";
			cerr << "Compound syntax error\n";
			cerr << "Invalid separator, '}' is expected"
				<< " at the end of statement list(code block).\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Compound syntax error\n";
		outfile << "Invalid separator, '{' is expected"
			<< " at the beginning of statement list(code block).\n";
		cerr << "Compound syntax error\n";
		cerr << "Invalid separator, '{' is expected"
			<< " at the beginning of statement list(code block).\n";
		system("Pause");
		exit(1);
	}
}

void Par::Assign(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!check_sym(lexeme))
		{
			cerr << "Identifier " << lexeme << " has not been declared yet.\n";
			system("pause");
			exit(1);
		}
		if (!_switch)
		{
			cout << "\t<Assign> -> "
				<< "<Identifier> := <Expression>;\n";
			outfile << "\t<Assign> -> "
				<< "<Identifier> := <Expression>;\n";
		}
		string save = lexeme;
		temp = lexeme;
		lexer(infile);
		print(outfile);
		if (lexeme == ":=")
		{
			lexer(infile);
			print(outfile);
			Expression(infile, outfile);
			int addr = get_address(save);
			gen_instr("POPM", addr);
			if (lexeme == ";")
			{
				lexer(infile);
				print(outfile);
			}
			else
			{
				printError(outfile);
				outfile << "Assign syntax error\n";
				outfile << "Invalid separator, ';' is expected"
					" at the end of assign statement.\n";
				cerr << "Assign syntax error\n";
				cerr << "Invalid separator, ';' is expected"
					" at the end of assign statement.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "Assign syntax error\n";
			outfile << "Invalid operator, ':=' is expected"
				<< " after <identifier> and before <expression>.\n";
			cerr << "Assign syntax error\n";
			cerr << "Invalid operator, ':=' is expected"
				<< " after <identifier> and before <expression>.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Assign syntax error\n";
		outfile << "Invalid token, <identifier> is expected"
			" at the beginning of assign statement.\n";
		cerr << "Assign syntax error\n";
		cerr << "Invalid token, <identifier> is expected"
			" at the beginning of assign statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::If(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "if")
	{
		if (!_switch)
		{
			cout << "\t<If> -> "
				<< "if (<Condition>) <Statement> <If Prime>\n";
			outfile << "\t<If> -> "
				<< "if (<Condition>) <Statement> <If Prime>\n";
		}
		int addr = instr_idx;
		lexer(infile);
		print(outfile);
		if (lexeme == "(")
		{
			lexer(infile);
			print(outfile);
			Condition(infile, outfile);
			if (lexeme == ")")
			{
				lexer(infile);
				print(outfile);
				Statement(infile, outfile);
				IfPrime(infile, outfile);
				backPatch(instr_idx);
			}
			else
			{
				printError(outfile);
				outfile << "If statement syntax error\n";
				outfile << "Invalid separator, ')' is expected"
					<< " after condition.\n";
				cerr << "If statement syntax error\n";
				cerr << "Invalid separator, ')' is expected"
					<< " after condition.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "If statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " before condition.\n";
			cerr << "If statement syntax error\n";
			cerr << "Invalid separator, '(' is expected"
				<< " before condition.\n";

			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "If statement syntax error\n";
		outfile << "Invalid keyword, 'if' keyword is expected"
			<< " at the beginning of If statement.\n";
		cerr << "If statement syntax error\n";
		cerr << "Invalid keyword, 'if' keyword is expected"
			<< " at the beginning of If statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::IfPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "fi")
	{
		if (!_switch)
		{
			cout << "\t<If Prime> -> "
				<< "fi\n";
			outfile << "\t<If Prime> -> "
				<< "fi\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "else")
	{
		if (!_switch)
		{
			cout << "\t<If Prime> -> "
				<< "else <Statement> fi\n";
			outfile << "\t<If Prime> -> "
				<< "else <Statement> fi\n";
		}
		lexer(infile);
		print(outfile);
		Statement(infile, outfile);
		if (lexeme == "fi")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "If statement syntax error\n";
			outfile << "Invalid keyword, 'fi' is expected"
				<< " at the end of If statement.\n";
			cerr << "If statement syntax error\n";
			cerr << "Invalid keyword, 'fi' is expected"
				<< " at the end of If statement.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "If statement syntax error\n";
		outfile << "Invalid keyword, 'fi' is expected at the end of If Statement\n"
			<< "Or 'else' is expected if there is an If-else statement.\n";
		cerr << "If statement syntax error\n";
		cerr << "Invalid keyword, 'fi' is expected at the end of If Statement\n"
			<< "Or 'else' is expected if there is an If-else statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Return(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "return")
	{
		if (!_switch)
		{
			cout << "\t<Return> -> "
				<< "return <Return Prime>\n";
			outfile << "\t<Return> -> "
				<< "return <Return Prime>\n";
		}
		lexer(infile);
		print(outfile);
		ReturnPrime(infile, outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Return statement syntax error\n";
		outfile << "Invalid keyword, 'return' is expected"
			<< " at the beginning of Return statement.\n";
		cerr << "Return statement syntax error\n";
		cerr << "Invalid keyword, 'return' is expected"
			<< " at the beginning of Return statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::ReturnPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == ";")
	{
		if (!_switch)
		{
			cout << "\t<Return Prime> -> "
				<< ";\n";
			outfile << "\t<Return Prime> -> "
				<< ";\n";
		}
		lexer(infile);
		print(outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Return Prime> -> "
				<< "<Expression>;\n";
			outfile << "\t<Return Prime> -> "
				<< "<Expression>;\n";
		}
		Expression(infile, outfile);
		if (lexeme == ";")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Return statement syntax error\n";
			outfile << "Invalid separator, ';' is expected"
				<< " at the end of Return statement.\n";
			cerr << "Return statement syntax error\n";
			cerr << "Invalid separator, ';' is expected"
				<< " at the end of Return statement.\n";
			system("Pause");
			exit(1);
		}
	}
}

void Par::Write(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "write")
	{
		if (!_switch)
		{
			cout << "\t<Write> -> "
				<< "<write (<Expression>);\n";
			outfile << "\t<Write> -> "
				<< "<write (<Expression>);\n";
		}
		lexer(infile);
		print(outfile);
		if (lexeme == "(")
		{
			lexer(infile);
			print(outfile);
			Expression(infile, outfile);
			if (lexeme == ")")
			{
				gen_instr("STDOUT", BLANK);
				lexer(infile);
				print(outfile);
				if (lexeme == ";")
				{
					lexer(infile);
					print(outfile);
				}
				else
				{
					printError(outfile);
					outfile << "Write statement syntax error\n";
					outfile << "Invalid separator, ';' is expected"
						<< " at the end of Write statement.\n";
					cerr << "Write statement syntax error\n";
					cerr << "Invalid separator, ';' is expected"
						<< " at the end of Write statement.\n";
					system("Pause");
					exit(1);
				}
			}
			else
			{
				printError(outfile);
				outfile << "Write statement syntax error\n";
				outfile << "Invalid separator, ')' is expected"
					<< " before ';' and after <Expression>.\n";
				cerr << "Write statement syntax error\n";
				cerr << "Invalid separator, ')' is expected"
					<< " before ';' and after <Expression>.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "Write statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " after 'write' keyword and before <Expression>.\n";
			cerr << "Write statement syntax error\n";
			cerr << "Invalid separator, '(' is expected"
				<< " after 'write' keyword and before <Expression>.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Write statement syntax error\n";
		outfile << "Invalid keyword, 'write' is expected"
			<< " at the beginning of Write statement.\n";
		cerr << "Write statement syntax error\n";
		cerr << "Invalid keyword, 'write' is expected"
			<< " at the beginning of Write statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Read(ifstream& infile, ofstream& outfile)
{
	isFromRead = true;
	if (lexeme == "read")
	{
		if (!_switch)
		{
			cout << "\t<Read> -> "
				<< "read (<IDs>);\n";
			outfile << "\t<Read> -> "
				<< "read (<IDs>);\n";
		}
		lexer(infile);
		print(outfile);
		if (lexeme == "(")
		{
			lexer(infile);
			string save = lexeme;
			print(outfile);
			IDs(infile, outfile);
			if (lexeme == ")")
			{
				int addr = get_address(save);
				gen_instr("STDIN", BLANK);
				gen_instr("POPM", addr);
				lexer(infile);
				print(outfile);
				if (lexeme == ";")
				{
					lexer(infile);
					print(outfile);
				}
				else
				{
					printError(outfile);
					outfile << "Read statement syntax error\n";
					outfile << "Invalid separator, ';' is expected"
						<< " at the end of Read statement.\n";
					cerr << "Read statement syntax error\n";
					cerr << "Invalid separator, ';' is expected"
						<< " at the end of Read statement.\n";
					system("Pause");
					exit(1);
				}
			}
			else
			{
				printError(outfile);
				outfile << "Read statement syntax error\n";
				outfile << "Invalid separator, ')' is expected"
					<< " after <IDs> and before ';'.\n";
				cerr << "Read statement syntax error\n";
				cerr << "Invalid separator, ')' is expected"
					<< " after <IDs> and before ';'.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "Read statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " after 'read' keyword and before <IDs>.\n";
			cerr << "Read statement syntax error\n";
			cerr << "Invalid separator, '(' is expected"
				<< " after 'read' keyword and before <IDs>.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Read statement syntax error\n";
		outfile << "Invalid keyword, 'read' is expected"
			<< " at the beginning of Read statement.\n";
		cerr << "Read statement syntax error\n";
		cerr << "Invalid keyword, 'read' is expected"
			<< " at the beginning of Read statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::While(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "while")
	{
		if (!_switch)
		{
			cout << "\t<While> -> "
				<< "<while (<Condition>) <Statement>\n";
			outfile << "\t<While> -> "
				<< "<while (<Condition>) <Statement>\n";
		}
		int addr = instr_idx;
		gen_instr("LABEL", BLANK);
		lexer(infile);
		print(outfile);
		if (lexeme == "(")
		{
			lexer(infile);
			print(outfile);
			Condition(infile, outfile);
			if (lexeme == ")")
			{
				lexer(infile);
				if (lexeme == "do") {
					lexer(infile);
					Statement(infile, outfile);
					gen_instr("JUMP", addr);
					backPatch(instr_idx);
				}
				else {
					printError(outfile);
					outfile << "While statement syntax error\n";
					outfile << "Do is expected\n";
					cerr << "While statement syntax error\n";
					cerr << "Do is expected\n";
					system("Pause");
					exit(1);
				}
			}
			else
			{
				printError(outfile);
				outfile << "While statement syntax error\n";
				outfile << "Invalid separator, ')' is expected"
					<< " after condition and before any statements.\n";
				cerr << "While statement syntax error\n";
				cerr << "Invalid separator, ')' is expected"
					<< " after condition and before any statements.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "While statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " before condition and after 'while' keyword.\n";
			cerr << "While statement syntax error\n";
			cerr << "Invalid separator, '(' is expected"
				<< " before condition and after 'while' keyword.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "While-loop syntax error\n";
		outfile << "Invalid keyword, 'while' is expected"
			<< " at the beginning of While-loop.\n";
		cerr << "While-loop syntax error\n";
		cerr << "Invalid keyword, 'while' is expected"
			<< " at the beginning of While-loop.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Condition(ifstream& infile, ofstream& outfile)
{
	if (!_switch)
	{
		cout << "\t<Condition> -> "
			<< "<Expression> <Relop> <Expression>\n";
		outfile << "\t<Condition> -> "
			<< "<Expression> <Relop> <Expression>\n";
	}
	Expression(infile, outfile);
	string op = lexeme;
	Relop(infile, outfile);
	Expression(infile, outfile);
	if (op == "=")
	{
		gen_instr("EQ", BLANK);
		jumpstack.push(instr_idx);
		gen_instr("JUMPZ", BLANK);
	}
	else if (op == "/=")
	{
		gen_instr("NEQ", BLANK);
		jumpstack.push(instr_idx);
		gen_instr("JUMPZ", BLANK);
	}
	else if (op == ">")
	{
		gen_instr("GRT", BLANK);
		jumpstack.push(instr_idx);
		gen_instr("JUMPZ", BLANK);
	}
	else if (op == "<")
	{
		gen_instr("LES", BLANK);
		jumpstack.push(instr_idx);
		gen_instr("JUMPZ", BLANK);
	}
	else if (op == "=>")
	{
		gen_instr("GEQ", BLANK);
		jumpstack.push(instr_idx);
		gen_instr("JUMPZ", BLANK);
	}
	else if (op == "<=")
	{
		gen_instr("LEQ", BLANK);
		jumpstack.push(instr_idx);
		gen_instr("JUMPZ", BLANK);
	}
	else
	{
		printError(outfile);
		outfile << "Relop syntax error\n";
		outfile << "Invalid operator\n"
			<< "'=', '/=', '>', '<', '=>' or '<=' is expected"
			<< " between 2 <Expression>.\n";
		cerr << "Relop syntax error\n";
		cerr << "Invalid operator\n"
			<< "'=', '/=', '>', '<', '=>' or '<=' is expected"
			<< " between 2 <Expression>.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Relop(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "=")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> =\n";
			outfile << "\t<Relop> -> =\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "/=")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> /=\n";
			outfile << "\t<Relop> -> /=\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == ">")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> >\n";
			outfile << "\t<Relop> -> >\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "<")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> <\n";
			outfile << "\t<Relop> -> <\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "=>")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> =>\n";
			outfile << "\t<Relop> -> =>\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "<=")
	{
		if (!_switch)
		{
			cout << "\t<Relop> -> <=\n";
			outfile << "\t<Relop> -> <=\n";
		}
		lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Relop syntax error\n";
		outfile << "Invalid operator\n"
			<< "'=', '/=', '>', '<', '=>' or '<=' is expected"
			<< " between 2 <Expression>.\n";
		cerr << "Relop syntax error\n";
		cerr << "Invalid operator\n"
			<< "'=', '/=', '>', '<', '=>' or '<=' is expected"
			<< " between 2 <Expression>.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Expression(ifstream& infile, ofstream& outfile)
{
	if (!_switch)
	{
		cout << "\t<Expression> -> <Term> <Expression Prime>\n";
		outfile << "\t<Expression> -> <Term> <Expression Prime>\n";
	}
	Term(infile, outfile);
	ExpressionPrime(infile, outfile);
}

void Par::ExpressionPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "+")
	{
		if (!_switch)
		{
			cout << "\t<Expression Prime> -> "
				<< "+ <Term> <Expression Prime>\n";
			outfile << "\t<Expression Prime> -> "
				<< "+ <Term> <Expression Prime>\n";
		}
		lexer(infile);
		checkTypeMatch(prevLexeme, lexeme);
		print(outfile);
		Term(infile, outfile);
		gen_instr("ADD", BLANK);
		ExpressionPrime(infile, outfile);
	}
	else if (lexeme == "-")
	{
		if (!_switch)
		{
			cout << "\t<Expression Prime> -> "
				<< "- <Term> <Expression Prime>\n";
			outfile << "\t<Expression Prime> -> "
				<< "- <Term> <Expression Prime>\n";
		}
		lexer(infile);
		checkTypeMatch(prevLexeme, lexeme);
		print(outfile);
		Term(infile, outfile);
		gen_instr("SUB", BLANK);
		ExpressionPrime(infile, outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Expression Prime> -> " << "Epsilon" << endl;
			outfile << "\t<Expression Prime> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::Term(ifstream& infile, ofstream& outfile)
{
	if (!_switch)
	{
		cout << "\t<Term> -> <Factor> <Term Prime>\n";
		outfile << "\t<Term> -> <Factor> <Term Prime>\n";
	}
	Factor(infile, outfile);
	TermPrime(infile, outfile);
}

void Par::TermPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "*")
	{
		if (!_switch)
		{
			cout << "\t<Term Prime> -> * <Factor> <Term Prime>\n";
			outfile << "\t<Term Prime> -> * <Factor> <Term Prime>\n";
		}
		lexer(infile);
		checkTypeMatch(prevLexeme, lexeme);
		print(outfile);
		Factor(infile, outfile);
		gen_instr("MUL", BLANK);
		TermPrime(infile, outfile);
	}
	else if (lexeme == "/")
	{
		if (!_switch)
		{
			cout << "\t<Term Prime> -> / <Factor> <Term Prime>\n";
			outfile << "\t<Term Prime> -> / <Factor> <Term Prime>\n";
		}
		lexer(infile);
		checkTypeMatch(prevLexeme, lexeme);
		print(outfile);
		Factor(infile, outfile);
		gen_instr("DIV", BLANK);
		TermPrime(infile, outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Term Prime> -> " << "Epsilon" << endl;
			outfile << "\t<Term Prime> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::Factor(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "-")
	{
		if (!_switch)
		{
			cout << "\t<Factor> -> - <Primary>\n";
			outfile << "\t<Factor> -> - <Primary>\n";
		}
		prevLexeme = lexeme;
		lexer(infile);
		print(outfile);
		Primary(infile, outfile);
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Factor> -> <Primary>\n";
			outfile << "\t<Factor> -> <Primary>\n";
		}
		Primary(infile, outfile);
	}
}

void Par::Primary(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!(getType(temp) == getType(lexeme)) && !(temp == "")) {
			cerr << "The type of " << temp << " and " << lexeme << " must match" << endl;
			system("pause");
			exit(1);
		}
		if (!check_sym(lexeme))
		{
			cerr << "Identifier " << lexeme << " has not been declared yet.\n";
			system("pause");
			exit(1);
		}
		if (!_switch)
		{
			cout << "\t<Primary> -> <identifier> <Primary Prime>\n";
			outfile << "\t<Primary> -> <identifier> <Primary Prime>\n";
		}
		int addr = get_address(lexeme);
		gen_instr("PUSHM", addr);
		prevLexeme = lexeme;
		lexer(infile);
		print(outfile);
		PrimaryPrime(infile, outfile);
	}
	else if (token == "integer")
	{
		if (!(getType(temp) == getType(lexeme)) && !(temp == "")) {
			cerr << "The type of " << temp << " and " << lexeme << " must match" << endl;
			system("pause");
			exit(1);
		}
		if (!_switch)
		{
			cout << "\t<Primary> -> <integer>\n";
			outfile << "\t<Primary> -> <integer>\n";
		}
		int a = 0;
		if (prevLexeme == "-")
		{
			prevLexeme = prevLexeme + lexeme;
			a = stoi(prevLexeme);
		}
		else
			a = stoi(lexeme);
		gen_instr("PUSHI", a);
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "(")
	{
		if (!_switch)
		{
			cout << "\t<Primary> -> (<Expression>)\n";
			outfile << "\t<Primary> -> (<Expression>)\n";
		}
		lexer(infile);
		print(outfile);
		Expression(infile, outfile);
		if (lexeme == ")")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Invalid separator, ')' is expected.\n";
			cerr << "Invalid separator, ')' is expected.\n";
			system("Pause");
			exit(1);
		}
	}
	else if (lexeme == "true")
	{
		if (!_switch)
		{
			cout << "\t<Prime> -> true\n";
			outfile << "\t<Prime> -> true\n";
		}
		lexer(infile);
		print(outfile);
	}
	else if (lexeme == "false")
	{
		if (!_switch)
		{
			cout << "\t<Prime> -> false\n";
			outfile << "\t<Prime> -> false\n";
		}
		lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Primary syntax error\n";
		outfile << "Invalid token, separator, or boolean value\n";
		outfile << "<identifier>, <integer>, "
			<< "'(', 'true' or 'false' is expected"
			<< " after '-', '*' or '/'.\n";
		cerr << "Primary syntax error\n";
		cerr << "Invalid token, separator, or boolean value\n";
		cerr << "<identifier>, <integer>, "
			<< "'(', 'true' or 'false' is expected"
			<< " after '-', '*' or '/'.\n";
		system("Pause");
		exit(1);
	}
}

void Par::PrimaryPrime(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "[")
	{
		if (!_switch)
		{
			cout << "\t<Primary Prime> -> [<IDs>]\n";
			outfile << "\t<Primary Prime> -> [<IDs>]\n";
		}
		lexer(infile);
		print(outfile);
		IDs(infile, outfile);
		if (lexeme == "]")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Primary syntax error\n";
			outfile << "Invalid separator, ']' is expected"
				<< " after <IDs>.\n";
			cerr << "Primary syntax error\n";
			cerr << "Invalid separator, ']' is expected"
				<< " after <IDs>.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		if (!_switch)
		{
			cout << "\t<Primary Prime> -> " << "Epsilon" << endl;
			outfile << "\t<Primary Prime> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::Empty(ifstream& infile, ofstream& outfile)
{
	//Do nothing in this function
}

void Par::printError(ofstream& outfile)
{
	outfile << "Error at line " << lineNum << endl;
	cerr << "Error at line " << lineNum << endl;
	//Reset the line number if there is an syntax error. The program will terminate
	//right away. So it is necessary to reset this for the next run.
	lineNum = 1;
}

//Destructor
Par::~Par()
{
	memory_address = 10000;
	count_sym = 0;
	isFromRead = false;
	isFromDeclaration = false;
	prevLexeme = "";
	temp = "";
}