#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>

using namespace std;

//Finite State Machine for integer
int int_DFSM(string arg)
{
    //create table N for the transitions
    int a[3][2] = {0, 'd', 1, 12, 12, 12};

    //accepting states
    int f[0] = {12};

    int col = 1;
    int state = 1; //starting state
    
    int size = arg.size();
    for (int i = 0; i < size; i++ )
    {
        state = a[state,col];
    }
    if (state == f[0])
        return 1; //accepted
    else 
        return 0; //rejected
}

//Finite State Machine for real
int real_DFSM(string arg)
{
    //create table N for the transitions
    int a[5][3] = {0, 'd', '.', 1, 12, 3, 34};

    //accepting states
    int f[0] = {34};

    int col = 1;
    int state = 1; //starting state
    
    int size = arg.size();
    for (int i = 0; i < size; i++ )
    {
        state = a[state,col];
    }
    if (state == f[0])
        return 1; //accepted
    else 
        return 0; //rejected
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
