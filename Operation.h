#pragma once
#include "LList.h"
#include "tag.h"

class Operation {
private:
	LList<double> list;
	Tag operation; 
	bool operationDone; //It acts like a switch depending on operation's execution

	/* ------ Private Methods ------- */
	void applyMAP();
	void applyAGG();
	void applySRT();

public:
	/* ------- Public Methods and Constructors ------- */
	Operation();
	Operation(std::string operation, std::string attribute = "");

	void addToList(double data);
	void appendList(LList<double>&);
	void applyGivenOperation();


	LList<double> getResAsList();
	std::string getResAsString();
};


/* -------- External Functions ------- */
double add(double, double);
double mul(double, double);
