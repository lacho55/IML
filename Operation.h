#pragma once
#include "LList.h"
#include "Tag.h"

class Operation
{
private:
	LList<double> list;
	Tag operation;
	bool operationDone;

public:
	/* ------- Public Methods and Constructors ------- */
	Operation();
	Operation(std::string newOperation, std::string newAttribute = "");

	void addToList(double);
	void appendList(LList<double>&);

};


/* -------- External Functions ------- */
double add(double, double);
double mul(double, double);
