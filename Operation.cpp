#include "Operation.h"
#include <string>
#include <sstream>

/* ------ Private Methods ------- */
void Operation::applyMAP() {

	//Taking the exact type of MAP operation wether it is INC or MLT
	std::string typeOfMap = (operation.getOperation()).substr(4, 3);

	//writing it that way because we have only two types of functions
	//and both of them will take two doule parameters and return double value
	double(*func)(double, double);

	typeOfMap == "INC" ? func = add : func = mul;

	//Just to store the needed parameter of the given function
	std::stringstream paramReader;
	paramReader << operation.getAttribute();

	double param;
	paramReader >> param;

	//Incrementing or multiplying all elements of the list 
	for (LListIterator<double> iter = list.begin(); iter; iter++) {
		*iter = func(*iter, param);
	}

}


//Aggregation operation
void Operation::applyAGG() {

	//Getting the type of the aggregate operation
	std::string typeOfAGG = operation.getOperation().substr(4, 3);
	double helper;

	if (typeOfAGG == "FST") {
		while (list.begin() != list.end())
			list.deleteEnd(helper);
		return;
	}

	if (typeOfAGG == "LST") {
		while (list.begin() != list.end())
			list.deleteBegin(helper);
		return;
	}

	// the operation is sum, product and average 
	double(*func)(double, double);

	LList<double> finalResult;

	if (typeOfAGG == "PRO") {
		func = mul;
		helper = 1;
	}
	else {
		func = add;
		helper = 0;
	}

	for (LListIterator<double> iter = list.begin(); iter; iter++)
		helper = func(helper, *iter);

	if (typeOfAGG == "AVG") {
		helper /= list.length();
	}

	finalResult.insertEnd(helper);
	list = finalResult;
}


//Sorting operation
void Operation::applySRT() {

	std::string typeOfSRT = operation.getOperation().substr(4, 3);

	if (typeOfSRT == "DST") {
		list.unique();
		return;
	}

	if (typeOfSRT == "ORD") {
		mergeSort(list);
	}

	if (typeOfSRT == "REV" || operation.getAttribute() == "DSC")
		list.reverse();

	if (typeOfSRT != "SLC")
		return;

	std::stringstream reader;
	double helper;
	int index;

	reader << operation.getAttribute();
	reader >> index;

	for (int i = 0; i < index; i++)
		list.deleteBegin(helper);
}


/* ------- Public Methods and Constructors ------- */
Operation::Operation() {
	operationDone = false;
}


Operation::Operation(std::string newOperation, std::string newAttribute) {

	operationDone = false;
	operation.setOperation(newOperation);

	//Checks if there is an attribute
	if (newAttribute.length() > 0) {
		operation.setAttribute(newAttribute);
		operation.setCheckForAttribute(true);
	}
}


//Adds new element at the end of the list of number
void Operation::addToList(double newData) { 
	list.insertEnd(newData);
}


//Appends the new list at the end of the current list
void Operation::appendList(LList<double>& other) {
	list.append(other);
}


//A method that applies its given operation from the three types
void Operation::applyGivenOperation() {

	if (operationDone) {
		return;
	}
	
	//taking only the type of the operation without anything other
	std::string oprTobeGiven = (operation.getOperation()).substr(0, 3);
	if (oprTobeGiven == "MAP") {
		applyMAP();
	}
	if (oprTobeGiven == "AGG") {
		applyAGG();
	}
	if (oprTobeGiven == "SRT") {
		applySRT();
	}

	operationDone = true;
}


//Returns the final list
LList<double> Operation::getResAsList() {
	return list;
}


//Returns the resulting list as a whole string
std::string Operation::getResAsString() {

	std::string finalRes;
	std::stringstream outputStream;

	for (LListIterator<double> iter = list.begin(); iter; iter++) {

		outputStream << *iter;

		if (iter != list.end()) {
			outputStream << " ";
		}
	}

	finalRes = outputStream.str();
	return finalRes;
}


/* -------- External Functions ------- */
double add(double num1, double num2) {
	return num1 + num2;
}

double mul(double num1, double num2) {
	return num1 * num2;
}