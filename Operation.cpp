#include "Operation.h"
#include <string>
#include <sstream>

/* --------- Public Methods and Constructors ---------*/
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
	list.insertTail(newData);
}


//Appends the new list at the end of the current list
void Operation::appendList(LList<double>& other) {
	list.append(other);
}


void Operation::applyGivenOperation() {

	if (operationDone) {
		return;
	}

	//taking only the type of the operation without anything other
	std::string oprTobeGiven = (operation.getOperation()).substr(0, 3);

	if (oprTobeGiven == "MAP") {
		//apply map operation
	}
	if (oprTobeGiven == "AGG") {
		//apply agg operation
	}
	if (oprTobeGiven == "STR") {
		//apply SRT
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

	for (LListIterator<double> iter = list.begin(); iter; ++iter) {

		outputStream << *iter;

		if (iter != list.end()) {
			outputStream << " ";
		}
	}

	finalRes = outputStream.str();

	return finalRes;
}


/* --------- External Functions ------- */
double add(double num1, double num2) {
	return (num1 + num2);
}


double mul(double num1, double num2) {
	return (num1 * num2);
}