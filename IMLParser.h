#pragma once
#include <string>
#include "LList.h"
#include "tag.h"


class IMLparser {
private:
	LList<std::string> parserFile;
	LList<Tag> parserTags;

	/* ------- Private Methods ------- */
	bool isValidTag(const Tag& tag);
	bool isValidExpression (const LListIterator<std::string>&);

	std::string readOpeningTag(const LListIterator<std::string>&, size_t&);
	std::string readClosingTag(const LListIterator<std::string>&, size_t&);
	std::string readAttribute(const LListIterator<std::string>&, size_t&);

	double readNumber(const LListIterator<std::string>&, size_t&);

	std::string processExpression(const LListIterator<std::string>&);
	std::string parse(const LListIterator<std::string>&);

	bool readFile(const char*);

public:
	/* ------- Constructor ------ */
	IMLparser();

	/* ------ Translation ----- */
	void translate(const char*, const char*);

};
