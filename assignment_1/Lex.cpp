#include "Lex.h"
#include <regex>

Lex::Lex()
{
	input = 'c';
	//token = new string[6] {identifier, real, integer, keyword, separator, operator};
	//lexeme = new string[];
}

//Function check separator
bool Lex::isSeparator(char input)
{
	int separator[6] = { '(',')', '{', '}', '%', '@' };
	for (int i = 0; i < 6; i++) {
		if (separator[i] == input) {
			return 1;
		}
	}
	return 0;
}
//Function check Operator
bool Lex::isOperator(char input)
{
	int operators[10] = { '+', '-', '/', '*', '<','>','=',':','!', '=' };
	for (int i = 0; i < 10; i++) {
		if (operators[i] == input) {
			return 1;
		}
	}
	return 0;
}

//Function check keyword
bool Lex::checkKeyword(string identifier)
{
	string keywords[12] = { "while", "if", "int", "fi", "else", "return",
		"read", "write", "integer", "for", "string", "boolean" };
	for (int i = 0; i < 12; i++) {
		if (keywords[i] == identifier) {
			return 1;
		}
	}
	return 0;
}

//Function returns the column number of the character in the table
int Lex::char_to_col(const char input) const
{
	if (isdigit(input))
		return 1;			//INT_NUM STATE
	else if (input == '.')	
		return 2;			//PERIOD STATE
	else if (isalpha(input))
		return 3;			//ID_STATE
	else if (input == '#')
		return 4;			//POWER_STATE
	else
		return -1;			//FAIL_STATE
}

//Finite State Machine for integer
int Lex::int_DFSM(const string str)
{
	//starting state
	int state = 1;

	//create table N for the transitions
	int a[3][2] = { 0, 'd',
					1, 2, 
					2, 2 };

	//accepting states
	int f[1] = { 2 };

	//update the currentState to new transition
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);
		if (col > 1)
			return 0;
		state = a[state][col];
	}
	if (state == f[0])
		return 1;
	else
		return 0;
}

//Finite State Machine for real
int Lex::real_DFSM(string str)
{
	int state = 1;
	int stateDot;
	// Regex : d+.d+ Floating number
	int a[5][3] = { 0, 'd', '.',
					1, 2, 0,
					2, 2, 3,
					3, 4, 0,
					4, 4, 0 };

	int f[1] = { 4 };

	//convert character to its column number in the table
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		int col = char_to_col(str[i]);
		if (col > 2) //col =1 (digit) or col = 2 (.)
			return 0;
	 	state = a[state][col];

	}
		
	if (state == f[0])
		return 1;
	return 0;
}

//Finite State Machine for identifier
int Lex::identifier_DFSM(string str)
{
	int state = 1;
	int a[6][5] = { 0, 'd', '.', 'l', '#', 
					1, 0, 0, 2, 0, 
					2, 0, 0, 3, 4,
					3, 0, 0, 3, 4,
					4, 0, 0, 5, 0, 
					5, 0, 0, 3, 4 };

	int f[4] = { 2, 3, 4, 5 };

	//convert character to its column number in the table
	int size = str.length();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);
		state = a[state][col];
	}

	for (int i = 0; i < 4; i++)
	{
		if (state == f[i])
			return 1;
	}
	return 0;
}

//0: keyword
//1: operator
//2: seperator
//3: identifier
//4: real
//5: integer
int Lex::Classify(string s)
{
	int len = s.length();
	/*regex identifer("[[:alpha:]]([[:alpha:]] | #[[:alpha:]]");*/
	//detect is keyword or not
	if (checkKeyword(s))
		return 0;

	//detect is operator or not
	for (int i = 0; i < len; i++)
	{
		if (isOperator(s[i]))
			return 1;
	}

	
	//detect is seperator or not
	for (int i = 0; i < len; i++)
	{
		if (isSeparator(s[i]))
			return 2;
	}

	//detect is identifier or not
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '#' || isalpha(s[i]))
			return 3;
	}

	//detect is real or not
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '.')
			return 4;
	}

	//detect is integer
	return 5;
}

LexToken Lex::lexer(ifstream& file)
{
	string str;
	LexToken a;
	int state_status = 0;
	bool found = false;
	char c = 'c';


	while (!found)
	
	{
		c = file.get();
		/*if (isOperator(c))
		{

			str += c;
			found = true;
		}
		else if (isSeparator(c))
		{

			str += c;
			found = true;
		}
		else if (c == 32 || c == '\0')
		{
			found = true;
			file.unget();
		}
		else
			str += c;*/
		if (isSeparator(c) || isOperator(c) || c == 32 || c == '\n' || c == -1)
		{
			found = true;
		}
		if (!str.empty() && (isOperator(c) || isSeparator(c)))
		{
			file.unget();
		}
		else if (!(c == 32)) {
			str += c;
		}
		if (str.empty())
			found = false;
		
	}

	/*if (str == "")
	{
		a.token = "empty string";
		return a;
	
	}*/

	int classify = Classify(str);
	
	if (classify == 1)
	{
		a.lexeme = c;
		a.token = "operator";
	}
	else if (classify == 2) {
		a.lexeme = c;
		a.token = "Separtor";
	}
	else if (classify == 4) {
		state_status = real_DFSM(str);
		if (state_status == 1)
		{
			a.lexeme = str;
			a.token = "real";
		}
		else
			cerr << "invalid real";
	}
	else if (classify == 5)
	{
		state_status = int_DFSM(str);
		if (state_status == 1)
		{
			a.lexeme = str;
			a.token = "integer";
		}
		else
			cerr << "invalid integer";	
	}
	else {
		state_status = identifier_DFSM(str);
		if (state_status == 1)
		{
			a.lexeme = str;
			if (classify == 0)
				a.token = "keyword";
			else
				a.token = "identifier";
		}
		else
			cerr << "invalid identifier";
	}

	/*if (isalpha(str[0]))
	{
		state_status = identifier_DFSM(str);
		if (state_status == 1)
		{
			a.lexeme = str;
			if (checkKeyword(str) == true)
				a.token = "keyword";
			else
				a.token = "identifier";
		}
		else
			cerr << "invalid identifier";
	}*/
	/*else if (isOperator(c)) {
		
	}
	else if (isSeparator(c)) {
		
	}*/

	/*else if (isdigit(str[0]))
	{
	     state_status = real_DFSM(str);
	     if (state_status == 1)
	     {
	         a.lexeme = str;
	         a.token = "real";
	     }
	     else
	         cerr << "invalid real";
	 }*/
	/* else
	 {
	     state_status = int_DFSM(str);
	     if (state_status == 1)
	     {
	         this->setLexeme(str);
	         this->setToken("integer");
	     }
	     else
	         cerr << "invalid real";
	 }*/
	return a;
}
//
//void Lex::print() const
//{
//	LexToken a;
//	cout << "token" << "        " << "lexeme";
//	cout << a.token << " " << a.lexeme;
//}
//
//void Lex::setToken(const string newtoken)
//{
//	LexToken a;
//	a.token = newtoken;
//}
//
//void Lex::setLexeme(const string newLexeme)
//{
//	LexToken a;
//	a.lexeme = newLexeme;
//}

Lex::~Lex()
{
	// delete [] lexeme;
	// lexeme = NULL;
	// delete [] token;
	// token = NULL;
}