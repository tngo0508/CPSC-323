#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex.hpp"

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
    string token;
    while (!file.eof())
    {
        // check.lexer(file);
        cout << check.lexer(file) << " ";
    }

    file.close();
	return 0;
}

