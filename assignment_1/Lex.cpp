#include "Lex.hpp"

Lex::Lex()
{
    currentState = 0;
    input = 'c';
}

//Function returns the column number of the character in the table
int Lex::char_to_col(const char input) const
{
    if (isdigit(input))
        return 1;
    else if (input == '.')
        return 2;
}

//Finite State Machine for integer
int Lex::int_DFSM(int& currentState, const char input)
{
    //create table N for the transitions
    int a[3][2] = {0, 'd', 1, 2, 2, 2};

    //accepting states
    int f[1] = {2};
    
    //update the currentState to new transition
    currentState = a[currentState][1];
    
    if (currentState == f[0])
        return 1; //accepted
    else
        return 0; //rejected
}

//Finite State Machine for real
int Lex::real_DFSM(int& currentState, const char input)
{
    int a[5][3] = {0, 'd', '.', 1, 2, 0, 2, 2, 3, 3, 4, 0, 4, 4, 0};

    int f[1] = {4};

    //convert character to its column number in the table
    int col = char_to_col(input);
    currentState = a[currentState][col];
    
    if (currentState == f[0])
        return 1;
    else
        return 0;
}

string Lex::lexer(ifstream& file)
{
    string token;
    int currentState = 1; //starting state
    int state_status = 0; 
    bool found = false;
    char ch;
    int i = 0;
    while(!found)
    {
        ch = file.get();
        /* if input char terminates a token AND it is an accepting state then 
         * isolate the token/lexeme
         * decrement the CP if necessary*/ 
        if (!isdigit(ch) && state_status == 1)
        {
            file.unget();
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
            else //FSM-identifier and FSM-real need to be added here
                found = true;
        }
    }

    if (found)
        return token;
}

Lex::~Lex(){}
