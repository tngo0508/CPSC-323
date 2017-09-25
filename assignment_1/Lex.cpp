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
    else if (isalpha(input))
        return 3;
    else
        return 4;
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

//Finite State Machine for identifier
int Lex::id_DFSM(int& currentState, const char ipnut)
{
    int a[6][5] = {0, 'd', '.', 'l', '#', 1, 0, 0, 2, 0, 2, 0, 0, 3, 4, 3, 0, 0,
        3, 4, 4, 0, 0, 5, 0, 5, 0, 0, 3, 4};

    int f[4] = {2, 3, 4, 5};

    //convert character to its column number in the table
    int col = char_to_col(input);
    currentState = a[currentState][col];

    for (int i = 0; i < 4; i++)
    {
        if (currentState == f[i])
            return 1;
    }
    return 0;
}

string Lex::lexer(ifstream& file)
{
    string token;
    int currentState = 1; //starting state
    int state_status = 0; 
    bool found = false;
    char ch;
    
    ch = file.get();

    if (isalpha(ch) || ch == '#')
    {
        while (!found)
        {
            if (!(isalpha(ch) || ch == '#') && state_status == 1)
            {
                found = true;
                file.unget();
            }
            else
            {
                state_status = id_DFSM(currentState, ch);
                token += ch;
                ch = file.get();
            }
        }

        if (found)
            return token;
    }
}

Lex::~Lex(){}
