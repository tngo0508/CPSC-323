#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex.h"

using namespace std;

int main() {
	ifstream file;
	file.open("test_case.txt");

	//Make sure file is opened
	if (!file.is_open())
	{
		cerr << "Failed to open the file";
		exit(1);
	}

	
	LexToken a;
	Lex check;
	char c;
	while (file.get(c))
	{
		a = check.lexer(file, c);
		cout << "Token " << a.token << " " << a.lexeme << endl;
	}

	file.close();
	system("pause");
	return 0;
}
