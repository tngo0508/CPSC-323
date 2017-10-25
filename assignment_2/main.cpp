#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex.h"
#include "parser.h"

using namespace std;

int main() {
	ifstream file;
	ofstream outFile("output.txt");
    string filename;
	string line;
	string token;
	string lexeme;

	do {
		cout << "Enter a file name .txt (or exit to quit): ";
		cin >> filename;

        if (!(filename == "exit"))
        {
            file.open(filename.c_str());

            //Make sure file is opened
            if (!file.is_open())
            {
                cerr << "Failed to open the file\n";
                exit(1);
            }
			else
			{
				cout << "SOURCE CODE:\n\n";
				//outFile << "SOURCE CODE:\n\n";
				while (getline(file, line))
				{
					cout << line << endl;
					//outFile << line << endl;
				}
			}

			cout << "\n\nOUTPUT:\n";
            cout << left << setw(20) << "Token" << setw(20) << "Lexeme" << endl;
            cout << endl;

			
			/*outFile << "\n\nOUTPUT:\n";
			outFile << left << setw(20) << "Token" << setw(20) << "Lexeme" << endl;
			outFile << endl;*/

			parser a;

			file.clear();
			file.seekg(0);
			//start to do the lexical analysis
            while (!file.eof())
            {
				token = a.getToken();
				lexeme = a.getLexeme();
            }

            file.close();
			cout << endl;
			outFile << endl;
        }
        
    } while (!(filename == "exit"));

	//outFile.close();
    cout << endl;
	//comment out system("Pause") if you are trying execute file on Linux OS
	//otherwise, uncomment it if on Windows OS
    system("Pause");
    return 0;
}
