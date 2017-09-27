#!bin/bash
#Author: 	Thomas Ngo
#Email:		tngo0508@csu.fullerton.edu	
#Course: 	CPSC323
#Project #:	RAT17F
#File name:	project.sh

echo script file for Project3 begin
rm *.o
rm *.out

g++ -g -c -std=c++11 main.cpp Lex.h Lex.cpp
g++ *.o -o a.out
echo finished.
