#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Lex.h"
#include "Par.h"

using namespace std;

int main() {
	ifstream inFile;
	ofstream outFile("output.txt");
	string filename;
	string line;

	do {
		cout << "Enter a file name .txt (or exit to quit): ";
		cin >> filename;

		if (!(filename == "exit"))
		{
			inFile.open(filename.c_str());

			//Make sure file is opened
			if (!inFile.is_open())
			{
				cerr << "Failed to open the file\n";
				exit(1);
			}
			else
			{
				cout << "SOURCE CODE:\n\n";
				outFile << "SOURCE CODE:\n\n";
				while (getline(inFile, line))
				{
					cout << line << endl;
					outFile << line << endl;
				}
			}

			cout << "\n\nOUTPUT:\n";
			cout << left << setw(20) << "Token" << setw(20) << "Lexeme" << endl;
			cout << endl;


			outFile << "\n\nOUTPUT:\n";
			outFile << left << setw(20) << "Token" << setw(20) << "Lexeme" << endl;
			outFile << endl;

			Par check;
			string token, lexeme;

			inFile.clear();
			inFile.seekg(0);
			//start to do the lexical analysis
	//        while (!inFile.eof())
	//        {
	//            check.lexer(inFile);

				////if there is a whitespace at eof, skip printing
				//if (!(check.getLexeme() == "EOF"))
				//{
				//	check.print();
				//	token = check.getToken();
				//	lexeme = check.getLexeme();
				//	outFile << left << setw(20) << token << setw(20) << lexeme 
				//		<< endl;
				//}
	//        }
			check.RAT17F(inFile);
			/*while (!inFile.eof())
			{
				check.RAT17F(inFile);

				if there is a whitespace at eof, skip printing
				if (!(check.getLexeme() == "EOF"))
				{
					check.print();
					token = check.getToken();
					lexeme = check.getLexeme();
					outFile << left << setw(20) << token << setw(20) << lexeme
						<< endl;
				}
			}*/

			inFile.close();
			cout << endl;
			outFile << endl;
		}

	} while (!(filename == "exit"));

	outFile.close();
	cout << endl;
	//comment out system("Pause") if you are trying execute file on Linux OS
	//otherwise, uncomment it if on Windows OS
	system("Pause");
	return 0;
}
