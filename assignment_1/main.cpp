#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "lexer.h"

using namespace std;

int main() {
    ofstream file;
    file.open("test_case.txt");
    
    //Make sure file is opened
    if (!file.is_open())
    {
        cerr << "Failed to open the file";
        exit(1);
    }
    
    while (!file.eof())
    {
        //call function lexer
        //print(token, lexeme)
    }

    file.close();
	return 0;
}
