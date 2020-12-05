#pragma once
#include<string>
#include"LList.h"
#include"Tag.h"

class Parser
{
private:
	LList<std::string> file;
	LList<Tag> parserTags;

public:
	/* ------- Constructor ------ */
	Parser();

	/* ------- File Reader ------ */
	void translate(const char*, const char*);
};

