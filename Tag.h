#pragma once
#include<string>


class Tag
{
private:
	std::string operation;
	std::string attribute;
	bool checkForAttribute;

public:
	/* ------- Constructor ------- */
	Tag(std::string, std::string, bool);

	/* ------- Setters and Getters ----- */
	const std::string getOperation() const;
	const std::string getAttribute() const;
	bool getCheckForAttribute() const;

	void setOperation(const std::string newOperation);
	void setAttribute(const std::string newAttribute);
	void setCheckForAttribute(const bool newCheckForAttribute);
	
};

