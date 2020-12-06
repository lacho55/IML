#include "Parser.h"
#include<iostream>
#include<fstream>
#include<sstream>


/* ------- Private Methods -------- */
//It reads all the data from the input file and stores it to the computer's memory
bool Parser::readFile(const char* inputFile) {

	std::ifstream fileStream(inputFile, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Error! Sorry but we cannot open the file for reading!\n";
		return false;
	}

	std::string row;

	while (getline(fileStream, row)) {
		parserFile.insertTail(row);
	}

	fileStream.close();

	return true;
}


/* ------ Constructor ------- */
Parser::Parser() {
	int allTags;
	string operation;
	bool checkForAttribute;

	//I find it out easier to just put all the given tags in a .txt file so more can be added lately
	std::ifstream fileStream("Tags.txt", std::ios::in);

	if (!fileStream.is_open()) {
		/*
		cerr is the standard error stream which is used to output the errors. 
		This is also an instance of the ostream class. 
		As cerr is un-buffered so it is used when we need to display the error message immediately. 
		It does not have any buffer to store the error message and display later.
		*/
		std::cerr << "Error! An error occured when trying to open the IML tags file!\n";
	}
	else {
		fileStream >> allTags;

		for (int i = 0; i < allTags; i++) {
			fileStream >> operation >> checkForAttribute;
			parserTags.insertTail(Tag(operation, "", checkForAttribute));
		}
		fileStream.close();
	}
}


/* ------- Translation -------- */
//Reads all the data from the input file and writes the
//proccessed data of the valid tags in the output file.
void Parser::translate(const char* inputFile, const char* outputFile) {
	
}
