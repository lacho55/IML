#include<iostream>
#include<fstream>
#include<sstream>
#include "Parser.h"
#include "LList.h"


/* -------- Constructor ------- */
Parser::Parser() {
	int numbersOfTags;
	std::string operation;
	bool checkAttribute;

	std::ifstream fileStream("Tags.txt", ios::in);
	
}



/*
cerr is the standard error stream which is used to output the errors. 
This is also an instance of the ostream class. 
As cerr is un-buffered so it is used when we need to display the error message immediately. 
It does not have any buffer to store the error message and display later.
*/