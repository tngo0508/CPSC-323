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
	return 0;
}
