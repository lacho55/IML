#include "Operation.h"


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


/* --------- External Functions ------- */
double add(double num1, double num2) {
	return (num1 + num2);
}


double mul(double num1, double num2) {
	return (num1 * num2);
}