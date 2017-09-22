#include "Lex.h"

Lex::Lex()
{
    currentState = 0;
    input = 'c';
}

//Finite State Machine for integer
int Lex::int_DFSM(int& currentState, char input)
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

string Lex::lexer(string str)
{
    string token;
    int currentState = 1; //starting state
    int state_status = 0; 
    bool found = false;
    char ch;
    int i = 0;
    while(!found)
    {
        ch = str.at(i);
        if (found == true)
        {
            //isolate the token/lexeme
            //decrement the CP if necessary
            i--;
            return token;
        }
        else
        {
            if (isdigit(ch))
            {
                state_status = int_DFSM(currentState, ch);
                if (state_status == 1)
                    token += ch;
                else
                    found = true;
            }
            else
                found = true;
        }
        i++;
    }

    if (found)
        return token;
}

Lex::~Lex(){}
