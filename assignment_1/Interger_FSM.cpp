#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>

using namespace std;

int DFSM(string arg)
{
    int a[2][1] = {12, 12};
    int f[0] = {12};
    int col = 0;
    int state = 0; //starting state
    
    int size = arg.size();
    for (int i = 0; i < size; i++ )
    {
        col = 0;
        state = a[0,col];
    }
    if (state == f[0])
        return 1;
    else 
        return 0;

}

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
