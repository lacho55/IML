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
	bool isValidTag(const Tag&);
	bool isValidExpression(const LListIterator<std::string>&);

	std::string readOpeningTag(const LListIterator<std::string>&, size_t&);
	std::string readClosingTag(const LListIterator<std::string>&, size_t&);
	std::string readAttribute(const LListIterator<std::string>&, size_t&);

	double readNumber(const LListIterator<std::string>&, size_t&);

	std::string processExpression(const LListIterator<std::string>&);
	std::string parse(const LListIterator<std::string>&);

	bool readFile(const char*);

public:
	/* ------- Constructor ------ */
	Parser();

	/* ------ Translation ----- */
	void translate(const char*, const char*);

};
