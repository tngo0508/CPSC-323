#include "lexer.h"

//convert character to column
int char_to_col()
{
    
}

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
    for (int i = 1; i <= size; i++ )
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
    int a[5][3] = {0, 'd', '.', 1, 12, 0, 12, 12, 3, 3, 34, 0, 34, 34, 0};

    //accepting states
    int f[0] = {34};

    int col = 1;
    int state = 1; //starting state
    
    int size = arg.size();
    for (int i = 1; i <= size; i++ )
    {
        col = char_to_col(a[i])
        state = a[state,col];
    }
    if (state == f[0])
        return 1; //accepted
    else 
        return 0; //rejected
}
