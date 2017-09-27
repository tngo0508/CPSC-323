#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex1.h"

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

	Lex check;
	while (!file.eof())
	{
		check.lexer(file);
		check.print();
	}

	cout << endl;
	system("Pause");
	return 0;
}