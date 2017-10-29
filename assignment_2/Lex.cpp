#include "Lex.h"

//constructor
Lex::Lex()
{
	input = 'c';
}

//Function check separator
bool Lex::isSeparator(const char input) const
{
	int separator[10] = { '(',')', '{', '}', '%', '@', ',', '[', ']', ';' };
	for (int i = 0; i < 10; i++) {
		if (separator[i] == input) {
			return 1;
		}
	}
	return 0;
}
//Function check Operator
bool Lex::isOperator(const char input) const
{
	int operators[8] = { '+', '-', '/', '*', '<','>',':', '=' };
	for (int i = 0; i < 8; i++) {
		if (operators[i] == input) {
			return 1;
		}
	}
	return 0;
}

//Function check keyword
bool Lex::checkKeyword(string identifier) const
{
	string keywords[12] = { "while", "if", "fi", "else", "return",
		"read", "write", "integer", "true", "false", "boolean", "floating" };
	for (int i = 0; i < 12; i++) {
		if (keywords[i] == identifier) {
			return 1;
		}
	}
	return 0;
}

int Lex::Classify(string s) {
	int len = s.length();

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
	char classify_ch = s[0];
	if (isalpha(classify_ch) || classify_ch == '#')
	{
		for (int i = 0; i < len; i++)
		{
			//if char is either # or letter, keep checking the string sequence
			//else return 6 which is invalid input
			if (s[i] == '#' || isalpha(s[i]));
			else
				return 6; //invalid input
		}
		return 3; 
	}
	else if (isdigit(classify_ch))
	{
		//first, check for valid input for floating or integer
		//only accept the string with number or dot(.) sign
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '.' || isdigit(s[i]));
			else
				return 6;
		}

		//second, check if there is a dot, then string could be a floating number
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '.')
				return 4;
		}

		//detect is integer
		return 5;
	}
	else
		return 6; //invalid input

	//not all path control above return a value. That's why we need return random number here
	return 7;
}

//Function returns the column number of the character in the table
int Lex::char_to_col(const char input) const
{
	if (isdigit(input))
		return 1;
	else if (input == '.')
		return 2;
	else if (isalpha(input))
		return 3;
	else if (input == '#')
		return 4;
	else
		return 5;
}

//Finite State Machine for integer
int Lex::int_DFSM(const string str)
{
	//starting state
	int state = 1;

	//create table N for the transitions or DFSM table for integer
	/*	0	d
		1	2
		2	2
	*/
	int a[3][2] = { 0, 'd', 1, 2, 2, 2 };

	//accepting states
	int f[1] = { 2 };

	//update the currentState to new transition
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		//convert the char to column number in table
		int col = char_to_col(str[i]);

		//update the current state
		state = a[state][col];
	}
	if (state == f[0])
		return 1;
	else
		return 0;
}

//Finite State Machine for floating
int Lex::floating_DFSM(string str)
{
	//starting state
	int state = 1;

	//DFSM table for floating
	/*	0	d	.
		1	2	0
		2	2	3
		3	4	0
		4	4	0
	*/
	int a[5][3] = { 0, 'd', '.', 1, 2, 0, 2, 2, 3, 3, 4, 0, 4, 4, 0 };

	int f[1] = { 4 };

	//convert character to its column number in the table
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);
		state = a[state][col];

		//if state = 0, then it is a failing state. Reject immediately
		if (state == 0) 
			return 0;
	}
	if (state == f[0])
		return 1;
	else
		return 0;
}

//Finite State Machine for identifier
int Lex::identifier_DFSM(string str)
{
	//starting state
	int state = 1;

	//transition table
	//failing state = 0
	/*	0	d	.	l	#
		1	0	0	2	0
		2	0	0	3	4
		3	0	0	3	4
		4	0	0	5	0
		5	0	0	3	4
	*/
	int a[6][5] = { 0, 'd', '.', 'l', '#', 1, 0, 0, 2, 0, 2, 0, 0, 3, 4, 3, 0, 0,
		3, 4, 4, 0, 0, 5, 0, 5, 0, 0, 3, 4 };

	int f[4] = { 2, 3, 4, 5 };

	//convert character to its column number in the table
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);
		state = a[state][col];
		if (state == 0)
			return 0;
	}

	for (int i = 0; i < 4; i++)
	{
		if (state == f[i])
			return 1;
	}
	return 0;
}

void Lex::lexer(ifstream& file)
{
	string str; //string stores the lexeme
	int state_status = 0;
	bool found = false;
	char ch = 'c';

	//get the character and add it into a string until see space, separator, or
	//operator
	while (!found)
	{
		ch = file.get();

		//check if current character is a separator, operator, whitespace, or eof
		//if yes, put the flag to exit the loop
		if (this->isSeparator(ch) || this->isOperator(ch) || isspace(ch) || ch == -1)
		{
			found = true;
		}

		/*if string is not empty and current character is either operator or separator
		decrease the current location in stream by one character
		else if current character is neither whitespace nor eof
		stores the char into string*/
		if (!str.empty() && (this->isOperator(ch) || this->isSeparator(ch)))
			file.unget();
		else if (!isspace(ch) && !(ch == -1))
			str += ch;

		//if the string is empty and current is not eof, get back to the loop
		//used to skip the whitespaces
		if (str.empty() && !(ch == -1))
			found = false;
	}

	//handle the file.txt with extra whitespaces at the end of the file
	if (str.empty() && ch == -1)
	{
		this->setLexeme("EOF");
		this->setToken("EOF");
		return;
	}

	int classify = Classify(str);

	//check token using FSM for identifier
	if (classify == 3) {

		//use FSM-identifier to check if token is accepted or not
		state_status = identifier_DFSM(str);

		this->setLexeme(str);
		if (state_status == 1)
		{
			if (checkKeyword(str))
				this->setToken("keyword");
			else
				this->setToken("identifier");
		}
		else
		{
			this->setToken("invalid identifier");
		}
	}
	//check for operator
	else if (classify == 1)
	{
		str = ch;

		//return the next char without extracting it from input sequence
		ch = file.peek();

		/*check for valid operators: /=, :=, <=, >=
		if current char and next char is a valid operator
		add next char to string and move to the next location char
		to keep track of the checking*/
		if ((str[0] == ':' && ch == '=') || (str[0] == '/' && ch == '=')
			|| (str[0] == '=' && ch == '>') || (str[0] == '<' && ch == '='))
		{
			str += ch;
			file.get();
		}

		//reject invalid operators if neccessary
		if (isOperator(str[0]) || str == ":=" || str == "/=" || str == "<=" 
			|| str == ">=")
		{
			this->setToken("operator");
			this->setLexeme(str);
		}
		else
		{
			this->setToken("invalid operator");
			this->setLexeme(str);
		}
	}
	//check for separator
	else if (classify == 2) {
		str = ch;
		ch = file.peek();
		if (str[0] == '%' && ch == '%')
		{
			str += ch;
			file.get();
		}

		if (!(str[0] == '%') || str == "%%")
		{
			this->setLexeme(str);
			this->setToken("separator");
		}
		else
		{
			this->setLexeme(str);
			this->setToken("invalid separator");
		}
	}
	//check token using FSM for floating
	else if (classify == 4) {
		state_status = floating_DFSM(str);
		this->setLexeme(str);
		if (state_status == 1)
		{
			this->setToken("floating");
		}
		else {
			this->setToken("invalid floating");
		}
	}
	//check token using FSM for floating
	else if (classify == 5)
	{
		state_status = int_DFSM(str);
		this->setLexeme(str);

		if (state_status == 1)
		{
			this->setToken("integer");
		}
		else
			this->setToken("invalid integer");
	}
	else
	{
		this->setLexeme(str);
		this->setToken("invalid input");
	}
}

void Lex::print() const
{
	cout << "Token: " << left << setw(20) << this->token 
		<< "Lexeme: " << setw(20) << this->lexeme << endl;
}

void Lex::setToken(const string newToken)
{
	token = newToken;
}

void Lex::setLexeme(const string newLexeme)
{
	lexeme = newLexeme;
}

string Lex::getToken() const
{
	return token;
}

string Lex::getLexeme() const
{
	return lexeme;
}

//destructor
Lex::~Lex() {}
