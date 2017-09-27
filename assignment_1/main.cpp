#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex.h"

using namespace std;

int main() {
	ifstream file;
    string filename;

    cout << "enter file name\n";
    cin >> filename;
    
	file.open(filename.c_str());

	//Make sure file is opened
	if (!file.is_open())
	{
		cerr << "Failed to open the file";
		exit(1);
	}

	cout << left << setw(20) << "Token" << setw(20) << "Lexeme" << endl;
	cout << endl;
	Lex check;

	while (!file.eof())
	{
		check.lexer(file);
		check.print();
	}

	file.close();
    
	cout << endl;
	//system("Pause");
	return 0;
}
