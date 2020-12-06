#pragma once
#include "Parser.h"
#include "Stack.h"
#include<iostream>
#include<fstream>
#include<sstream>


/* ------- Private Methods -------- */
//A method for checking wether all the tags are nested correctly
//and makes sure that all of them are from the IML
bool Parser::isValidExpression(const LListIterator<std::string>& iter) {
	
	Stack<Tag> storage;
	std::string operation;
	std::string attribute;

	//Going through the row
	for (size_t i = 0; i < (*iter).length(); i++) {

		//Checks if there is a new tag
		if ((*iter)[i] == '<' && (*iter)[i + 1] != '/') {

			operation = readOpeningTag(iter, i);

			//Before continuing we have to make sure wether there is an attribute or not
			if ((*iter)[i] != '>') {
				//to do read Attribute;
			}

		}

	}
}


//A method that reads current operation and its type
std::string Parser::readOpeningTag(const LListIterator<std::string>& iter, size_t& rowIndex) {

	//Creating a variable to store the given operation
	//Also we increase rowIndex to move forward after the < bracket
	std::string operationToReturn;
	rowIndex++;

	while ((*iter)[rowIndex] != ' ' && (*iter)[rowIndex] != '>') {
		operationToReturn += (*iter)[rowIndex];
		rowIndex++;
	}

	return operationToReturn;
}


//A method for checking wether the given expression from the intput file
//is valid or not and of course returns the text that has to be written.
std::string Parser::processExpression(const LListIterator<std::string>& iter) {

	std::string processedLine;

	
	return processedLine;
}


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
	
	if (!readFile(inputFile)) {
		return;
	}

	std:string outputRow;
	std::ofstream fileStream(outputFile, std::ios::out | std::ios::trunc);

	if (!fileStream.is_open()) {
		std::cerr << "Error! Sorry, but something went wrong when trying to open the file for writing\n";
		return;
	}

	for (LListIterator<std::string> iter = parserFile.begin(); iter; ++iter) {
		//// To do .... processing
		fileStream << outputRow << '\n';
	}

	fileStream.close();
}
