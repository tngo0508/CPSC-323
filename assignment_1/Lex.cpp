#include "Lex.h"

Lex::Lex()
{
	input = 'c';
}

//Function check separator
bool Lex::isSeparator(const char input) const
{
	int separator[10] = { '(',')', '{', '}', '%', '@', ',', '[', ']', ';'};
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
		return 1;
	else if (input == '.')
		return 2;
	else if (isalpha(input))
		return 3;
	else
		return 4;
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

		//if (this->isSeparator(ch) || this->isOperator(ch) || ch == 32 || ch == '\n' || ch == -1)
		if (this->isSeparator(ch) || this->isOperator(ch) || isspace(ch) || ch == -1)
		{
			found = true;
		}
		if (!str.empty() && (this->isOperator(ch) || this->isSeparator(ch)))
		{
			file.unget();
		}
		//else if (!(ch == 32))
		else if (!isspace(ch))
			str += ch;
		if (str.empty())
			found = false;
	}

	if (this->isOperator(str[0]))
	{
		str = ch;
		//check if the next character is another operator or not
		ch = file.get();
		if (this->isOperator(ch))
			str += ch;
		else
			file.unget();
		this->setToken("operator");
		this->setLexeme(str);
	}
	else if (this->isSeparator(str[0]))
	{
		this->setToken("separator");
		this->setLexeme(str);
	}
	else //look for appropriate FSM to check lexeme
	{
		int size = str.size();
		bool identifier_checking = false;
		for (int i = 0; i < size; i++)
		{
			if (!(str[i] == '#' || isalpha(str[i])))
				identifier_checking = true;
		}
		if (!identifier_checking)
		{
			state_status = identifier_DFSM(str);
			this->setLexeme(str);
			if (state_status == 1)
			{
				//this->setLexeme(str);
				if (this->checkKeyword(str) == true)
					this->setToken("keyword");
				else
					this->setToken("identifier");
			}
			else
			{
				this->setToken("invalid identifier");
				//cerr << "invalid identifier\n";
			}
		}
		else
		{
			if (identifier_checking)
			{
				this->setLexeme(str);
				this->setToken("invalid identifier");
			}
			else
			{
				bool real_checking = false;
				for (int i = 0; i < size; i++)
				{
					if (!(str[i] == '.' || isdigit(str[i])))
						real_checking = true;
				}
			}
		}
		/*else if (isdigit(str[0]) || str[0])
		{
			state_status = real_DFSM(str);
			if (state_status == 1)
			{
				this->setLexeme(str);
				this->setToken("real");
			}
			else
				cerr << "invalid real";
		}
		else
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
	}
}

void Lex::print() const
{
	// cout << "token" << "        " << "lexeme";
	cout << this->token << " " << this->lexeme << endl;
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