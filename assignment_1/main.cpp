#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex.h"

using namespace std;

int main() {
    string statement;
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
        file >> statement;
        cout << statement;
        cout << check.lexer(statement);
    }

    file.close();
	return 0;
}

