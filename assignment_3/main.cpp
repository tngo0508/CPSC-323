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
		cout << "Enter a file name .txt (or 'exit' to quit): ";
		cin >> filename;

		if (!(filename == "exit"))
		{
			inFile.open(filename.c_str());

			//Make sure file is opened
			if (!inFile.is_open())
			{
				cerr << "Failed to open the file.\n";
				cerr << "Please enter correct file.\n";
				system("pause");
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
			cout << endl;

			outFile << "\n\nOUTPUT:\n";
			outFile << endl;

			Par check;

			inFile.clear();
			inFile.seekg(0);
			check.RAT17F(inFile, outFile);
			check.printSym();
			check.printInstr();
			inFile.close();

			check.~Par();
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