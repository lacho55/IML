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
	Operation(std::string, std::string);
};

