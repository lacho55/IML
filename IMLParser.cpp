#include "IMLParser.h"
#include "Operation.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <sstream>


/* ------- Private Methods ------- */
//A method for checking wether a tag is valid or not
bool IMLparser::isValidTag(const Tag& givenTag) {

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
bool IMLparser::isValidExpression(const LListIterator<std::string>& iter) {

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
				Tag openingTag(operation, attribute, true);

				if (!isValidTag(openingTag)) {
					return false;
				}
	
				storage.push(openingTag);
				//Increasing it only just to get after closing quoatation mark
				//i will also be incremented once at the end of the iteration(attribute ="")
				i++;
			}
			else {
				//Assuming the tag does not have any attributes
				Tag openingTag(operation);

				if (!isValidTag(openingTag)) {
					return false;
				}
					
				storage.push(openingTag);
			}
		}

		//Getting to the closing tags
		if ((*iter)[i] == '<' && (*iter)[i + 1] == '/') {

			if (storage.empty()) {
				return false;
			}
				
			operation = readClosingTag(iter, i);
			Tag closeTag(operation);
			Tag corresponding = storage.pop();

			if (closeTag.getOperation() != corresponding.getOperation()) {
				return false;
			}
		}
	}
	return storage.empty();
}


//A method that reads current operation and its type
std::string IMLparser::readOpeningTag(const LListIterator<std::string>& iter, size_t& rowIndex) {
	
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


std::string IMLparser::readClosingTag(const LListIterator<std::string>& iter, size_t& rowIndex) {

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
std::string IMLparser::readAttribute(const LListIterator<std::string>& iter, size_t& rowIndex) {

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
double IMLparser::readNumber(const LListIterator<std::string>& iter, size_t& rowIndex) {
	
	std::stringstream sData;
	double number;

	while ((*iter)[rowIndex] != ' ' && (*iter)[rowIndex] != '<') {
		sData << (*iter)[rowIndex];
		rowIndex++;
	}

	sData >> number;

	// i can be positioned on an interval or on a '<'
	// if it is positioned on '<' there will be a big problem
	// because at the end of the loop i will be incremented once
	// and the following tag won't be read
	if ((*iter)[rowIndex] == '<')
		rowIndex--;

	return number;
}


//A method for checking wether the given expression from the intput file
//is valid or not and of course returns the text that has to be written.
std::string IMLparser::processExpression(const LListIterator<std::string>& iter) {

	std::string processedLine;

	if (!isValidExpression(iter)) {
		processedLine = "The input line is invalid and cannot be translated!";
	}	
	else {
		processedLine = parse(iter);
	}

	return processedLine;
}


std::string IMLparser::parse(const LListIterator<std::string>& iter) {

	Stack<Operation> storage;
	std::string operation;
	std::string attribute;
	double num;

	for (size_t i = 0; i < (*iter).length(); i++) {

		//checks for opening tags
		if ((*iter)[i] == '<' && (*iter)[i + 1] != '/') {

			//taking the type of operation
			operation = readOpeningTag(iter, i);

			//So now, lets check for any attributes
			if ((*iter)[i] != '>') {

				attribute = readAttribute(iter, i);
				Operation list(operation, attribute);
				storage.push(list);
				i++;
				//Again, we dont need to get after the '>', only after the closing quoatation mark
				// i will be incremented once at the end of the iteration
			}
			else {
				//Taking care of the case when we don't have any attributes
				Operation list(operation);
				storage.push(list);
			}
		}

		//Next step is reding the numeric data from the line
		if ((*iter)[i] == '-' || '0' <= (*iter)[i] && (*iter)[i] <= '9') {
			num = readNumber(iter, i);
			storage.peek().addToList(num);
		}

		//Lets take care of the closing tags
		if ((*iter)[i] == '<' && (*iter)[i+1] == '/') {
			//If the expression is valid the operation that will be
			//executed will be on the top of the storage

			// we are reading the operation in order to move i on '>'
			operation = readClosingTag(iter, i);
			Operation currOperation = storage.pop();
			currOperation.applyGivenOperation();


			if (storage.empty()) {
				return currOperation.getResAsString();
			}	
			else {
				storage.peek().appendList(currOperation.getResAsList());
			}
		}
	}
}


//It reads all the data from the input file and stores it to the computer's memory
bool IMLparser::readFile(const char* inputFile) {

	std::ifstream fileStream(inputFile, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Error! Sorry but we cannot open the file for reading!\n";
		return false;
	}
	
	std::string row;

	while (getline(fileStream, row)) {
		parserFile.insertEnd(row);
	}

	fileStream.close();
	return true;
}


/* ------ Constructor ------- */
IMLparser::IMLparser() {
	int allTags;
	std::string operation;
	bool checkForAttribute;

	//I find it out easier to just put all the given tags in a .txt file so more can be added lately
	std::ifstream fileStream("Tags.txt", std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "An error occured when trying to open the file containing IML tags for reading!\n";
		/*
		cerr is the standard error stream which is used to output the errors.
		This is also an instance of the ostream class.
		As cerr is un-buffered so it is used when we need to display the error message immediately.
		It does not have any buffer to store the error message and display later.
		*/
	}	
	else {
		fileStream >> allTags;
		for (int i = 0; i < allTags; i++) {
			fileStream >> operation >> checkForAttribute;
			parserTags.insertEnd(Tag(operation, "", checkForAttribute));
		}
		fileStream.close();
	}
}

/* ------ Translation ----- */
//Reads all the data from the input file and writes the
//proccessed data of the valid tags in the output file.
void IMLparser::translate(const char* inputFile, const char* outputFile) {
	if (!readFile(inputFile)) {
		return;
	}
		

	std::string outputRow;
	std::ofstream fileStream(outputFile, std::ios::out | std::ios::trunc);

	if (!fileStream.is_open()) {
		std::cerr << "Error! Sorry, but something went wrong when trying to open the file for writing\n";
		return;
	}

	for (LListIterator<std::string> it = parserFile.begin(); it; ++it) {
		outputRow = processExpression(it);
		fileStream << outputRow << '\n';
	}

	fileStream.close();
}