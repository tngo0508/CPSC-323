#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <ctype.h>

using namespace std;

//Finite State Machine for integer
int int_DFSM(int& currentState, char input)
{
    //create table N for the transitions
    int a[3][2] = {0, 'd', 1, 2, 2, 2};

    //accepting states
    int f[1] = {2};
    
    currentState = a[currentState][1];

    if (currentState == f[0])
        return 1;
    else
        return 0;
}

string lexer(ofstream file)
{
    string token;
    int currentState = 1; //starting state
    int state_status = 0; 
    bool found = false;
    char ch;
    while(!found)
    {
        file.get(ch);
        if (found == true)
            //isolate the token/lexeme
            //decrement the CP if necessary
        else
        {
            token += ch;
            if (isdigit(ch))
            {
                state_status = int_DFSM(currentState, input)
                if (state_status == 0)
                    found = true;
            }
        }
    }

    if (found)
        return token;
}

#endif
