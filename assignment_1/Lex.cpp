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

/*
     Function Classify
     Check string input to detect if the string has a separator, a letter, a digit, '#', '.'
     and return the number for that type
 */

int Lex::Classify(string s) {
	int len = s.length();

	//Iterating the array to check if the string has a operator or not
    //and return 1 if it is.
	for (int i = 0; i < len; i++)
	{
		if (isOperator(s[i]))
			return 1;
	}


    //Iterating the array to check if the string has separator or not
    //and return 2 if it is.
	for (int i = 0; i < len; i++)
	{
		if (isSeparator(s[i]))
			return 2;
	}

    //If the first char of the string is a letter or #, iterate the string and check if
    //the string has # or a letter return 3 , return 6 if not.
    
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
    
    
     //If the first char of the string is a digit,
     //iterate the string and check if a string has a point or not.
     //If the string has a point then return 4, else return 5 as an integer
    
	else if (isdigit(classify_ch))
	{
		//first, check for valid input for real or integer
		//only accept the string with number or dot(.) sign
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '.' || isdigit(s[i]));
			else
				return 6;
		}

		//second, check if there is a dot, then string could be a real number
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '.')
				return 4;
		}
        
		return 5;
	}
	else
		return 6; //invalid input

	//not all path control above return a value. That's why we need return random number here
	return 7;
}

/*
     Function char_to_column
     Convert char to column in finite machine
     Return the column number
     Return column 1 if it is a digit
     Return column 2 if it is a point
     Return column 3 if it is a letter
     Return column 4 if it is a #
     Return 5 if it is not all of above
*/
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
    //Create a table with 2 columns and 3 rows for transitions
    //First column and first row are labels.
    //Another column and row are states based on converting NFSM to DFSM
	/*	0	d
		1	2
		2	2
	*/
	int a[3][2] = { 0, 'd', 1, 2, 2, 2 };

	//Accepting state
	int f[1] = { 2 };

	//update the currentState to new transition
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);

		//update the current state
		state = a[state][col];
	}
    
    //If current state is equal to accepting state, return 1.
    //If not, return 0
	if (state == f[0])
		return 1;
	else
		return 0;
}

//Finite State Machine for real
int Lex::real_DFSM(string str)
{
	//starting state
	int state = 1;

    //Create a table with 3 columns and 5 rows for transitions
    //First column and first row are labels.
    //Other columns and rows are states based on converting NFSM to DFSM
	//DFSM table for real
	/*	0	d	.
		1	2	0
		2	2	3
		3	4	0
		4	4	0
	*/
	int a[5][3] = { 0, 'd', '.', 1, 2, 0, 2, 2, 3, 3, 4, 0, 4, 4, 0 };

    //Accepting state
	int f[1] = { 4 };

	//convert character to its column number in the table
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		int col = char_to_col(str[i]);
		state = a[state][col];
		if (state == 0)
			return 0;
	}
    
    //If current state is equal to accepting state, return 1.
    //If not, return 0
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

	//Create a table with 5 columns and 6 rows for transitions
    //First Column and first row are labels.
    //Other columns and rows are states based on converting NFSM to DFSM
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

    //accepting state
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

    //Check state if it is equal in one of these accepting states then return 1 else return 0
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

		ch = file.peek();

		if ((str[0] == ':' && ch == '=') || (str[0] == '/' && ch == '=')
			|| (str[0] == '=' && ch == '>') || (str[0] == '<' && ch == '='))
		{
			str += ch;
			file.get();
		}

		if (!(str[0] == '=') || str == ":=")
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
	
    /*
         If the type of the string is a separator,
    */
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
    
	/*
         If classify equals 4, get state status after running Real Finite Machine and set Lexeme
         Set Token 'Real' if running real finite machine successfuly, else 'invalid real'
     */
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

    /*
         If classify equals 5, get state status after running Integer Finite Machine and set Lexeme
         Set Token 'Integer' if running integer finite machine successfuly, else 'invalid integer'
     */
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

/*
     Function print
     Print out the token and lexeme
*/
void Lex::print() const
{
	cout << left << setw(20) << this->token << setw(20) << this->lexeme << endl;
}

/*
     Function setToken
     Set Token
*/
void Lex::setToken(const string newToken)
{
	token = newToken;
}

/*
     Function setLexeme
     Set Lexeme
*/
void Lex::setLexeme(const string newLexeme)
{
	lexeme = newLexeme;
}

/*
     Function getToken()
     Return a token
 */
string Lex::getToken() const
{
	return token;
}

/*
     Function getLexeme()
     Return a lexeme
*/
string Lex::getLexeme() const
{
	return lexeme;
}

Lex::~Lex() {}
