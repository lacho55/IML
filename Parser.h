#pragma once
#include<string>
#include "LList.h"
#include "Tag.h"

class Parser
{
private:
	LList<string> parserFile;
	LList<Tag> parserTags;

	/* ------- Private Methods ------- */
	bool readFile(const char*);

public:
	/* ------- Constructor ------ */
	Parser();

	/* ------ Translation ----- */
	void translate(const char*, const char*);

};

