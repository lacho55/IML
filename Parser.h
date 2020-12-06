#pragma once
#include<string>
#include "LList.h"
#include "Tag.h"

class Parser
{
private:
	LList<std::string> parserFile;
	LList<Tag> parserTags;

	/* ------- Private Methods ------- */
	bool isValidExpression(const LListIterator<std::string>&);
	std::string readOpeningTag(const LListIterator<std::string>&, size_t&);
	std::string processExpression(const LListIterator<std::string>&);
	bool readFile(const char*);

public:
	/* ------- Constructor ------ */
	Parser();

	/* ------ Translation ----- */
	void translate(const char*, const char*);

};
