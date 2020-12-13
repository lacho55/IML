#pragma once
#include "Parser.h"
#include "Stack.h"
#include<iostream>
#include<fstream>
#include<sstream>


/* ------- Private Methods -------- */
//A method for checking wether a tag is valid or not
bool Parser::isValidTag(const Tag& givenTag) {

	for (LListIterator<Tag> iter = parserTags.begin(); iter; ++iter) {

		if (givenTag.getOperation() == (*iter).getOperation()
			&& givenTag.getCheckForAttribute() == (*iter).getCheckForAttribute()) {
			return true;
		}
	}

	return false;
}

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
				attribute = readAttribute(iter, i);
				Tag openTag(operation, attribute, true);
				
				if (!isValidTag(openTag)) {
					return false;
				}

				storage.push(openTag);
				//Increasing it only just to get after closing quoatation mark
				//i will also be incremented once at the end of the iteration(attribute ="")
				i++;
			}
			else {
				//Assuming the tag does not have any attributes
				Tag openTag(operation);
				if (!isValidTag(openTag)) {
					return false;
				}

				storage.push(openTag);
			}
		}

		//Getting to the closing tags
		if ((*iter)[i] == '<' && (*iter)[i + 1] == '/') {
			if (storage.empty()) {
				return false;
			}

			operation = readClosingTag(iter, i);
			Tag closeTag(operation);
			Tag toCompareTag = storage.pop();

			if (closeTag.getOperation() != toCompareTag.getOperation()) {
				return false;
			}
		}

	}

	return (storage.empty());
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


std::string Parser::readClosingTag(const LListIterator<std::string>& iter, size_t& rowIndex) {
	
	std::string operationToReturn;
	rowIndex++; // In order to get after <
	rowIndex++; // In order to get after /

	while ((*iter)[rowIndex] != '>') {
		operationToReturn += (*iter)[rowIndex];
		rowIndex++;
	}

	return operationToReturn;
}


//A method for reading tag's attributes
std::string Parser::readAttribute(const LListIterator<std::string>& iter, size_t& rowIndex) {
	
	std::string attributeToReturn;
	rowIndex++;//just to skip the interval
	rowIndex++;//in order to get to the first quotation mark

	while ((*iter)[rowIndex] != '\"') {
		attributeToReturn += (*iter)[rowIndex];
		rowIndex++;
	}

	return attributeToReturn;
}


//A method for reading number data from the file
double Parser::readNumber(const LListIterator<std::string>& iter, size_t& rowIndex) {

	double number;
	std::stringstream sData;

	while ((*iter)[rowIndex] != ' ' && (*iter)[rowIndex] != '<') {
		sData << (*iter)[rowIndex];
		rowIndex++;
	}

	sData >> number;

	// i can be positioned on an interval or on a '<'
	// if it is positioned on '<' there will be a big problem
	// because at the end of the loop i will be incremented once
	// and the following tag won't be read
	if ((*iter)[rowIndex] == '<') {
		rowIndex++;
	}

	return number;
}


//A method for checking wether the given expression from the intput file
//is valid or not and of course returns the text that has to be written.
std::string Parser::processExpression(const LListIterator<std::string>& iter) {

	std::string processedLine;

	if (!isValidExpression(iter)) {
		processedLine = "The line from the input file is invalid!";
	}
	else {
		processedLine = parse(iter);
	}
	
	return processedLine;
}


std::string Parser::parse(const LListIterator<std::string>& iter) {
	
	// to do
	std::string da;

	return da;
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

	std::string outputRow;
	std::ofstream fileStream(outputFile, std::ios::out | std::ios::trunc);

	if (!fileStream.is_open()) {
		std::cerr << "Error! Sorry, but something went wrong when trying to open the file for writing\n";
		return;
	}

	for (LListIterator<std::string> iter = parserFile.begin(); iter; ++iter) {
		outputRow = processExpression(iter);
		fileStream << outputRow << '\n';
	}

	fileStream.close();
}
