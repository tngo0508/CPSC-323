#include "Lex.h"

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
			if (s[i] == '#' || isalpha(s[i]));
			else
				return 6;
		}
		return 3;
	}
	else if (isdigit(classify_ch))
	{
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '.')
				return 4;
		}

		//detect is integer
		return 5;
	}
	else
		return 6;

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

	//create table N for the transitions
	int a[3][2] = { 0, 'd', 1, 2, 2, 2 };

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
	int a[5][3] = { 0, 'd', '.', 1, 2, 0, 2, 2, 3, 3, 4, 0, 4, 4, 0 };

	int f[1] = { 4 };

	//convert character to its column number in the table
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);
		if (col > 2)
			return 0;
		state = a[state][col];
	}
	if (state == f[0])
		return 1;
	else
		return 0;
}

//Finite State Machine for identifier
int Lex::identifier_DFSM(string str)
{
	int state = 1;
	int a[6][5] = { 0, 'd', '.', 'l', '#', 1, 0, 0, 2, 0, 2, 0, 0, 3, 4, 3, 0, 0,
		3, 4, 4, 0, 0, 5, 0, 5, 0, 0, 3, 4 };

	int f[4] = { 2, 3, 4, 5 };

	//convert character to its column number in the table
	int size = str.size();
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

void Lex::lexer(ifstream& file)
{
	string str;
	int state_status = 0;
	bool found = false;
	char ch = 'c';

	//get the character and add it into a string until see space, separator, or operator
	while (!found)
	{
		ch = file.get();

		if (this->isSeparator(ch) || this->isOperator(ch) || isspace(ch) || ch == -1)
		{
			found = true;
		}
		if (!str.empty() && (this->isOperator(ch) || this->isSeparator(ch)))
		{
			file.unget();
		}
		else if (!isspace(ch) && !(ch == -1))
			str += ch;

		if (str.empty() && !(ch == -1))
			found = false;
	}

	//handle the file.txt with another whitespace at the end
	if (str.empty() && ch == -1)
	{
		this->setLexeme("EOF");
		this->setToken("EOF");
		return;
	}

	int classify = Classify(str);

	//check token using FSM for identifier
	if (classify == 3) {
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

		//check if the next character is another operator or not
		//ch = file.get();
		ch = file.peek();

		if ((str[0] == ':' && ch == '=') || (str[0] == '/' && ch == '=')
			|| (str[0] == '=' && ch == '>') || (str[0] == '<' && ch == '='))
			str += ch;
		/*else
			file.unget();*/
		this->setToken("operator");
		this->setLexeme(str);
	}
	//check for separator
	else if (classify == 2) {
		str = ch;
		//ch = file.get();
		ch = file.peek();
		if (str[0] == '%' && ch == '%')
			str += ch;
		/*else
			file.unget();*/
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
	//check token using FSM for real
	else if (classify == 4) {
		state_status = real_DFSM(str);
		this->setLexeme(str);
		if (state_status == 1)
		{
			this->setToken("real");
		}
		else {
			this->setToken("invalid real");
		}
	}
	//check token using FSM for real
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
	cout << left << setw(20) << this->token << setw(20) << this->lexeme << endl;
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

Lex::~Lex() {}
