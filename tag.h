#pragma once


class Tag {
private: 
	std::string operation;
	std::string attribute;
	bool checkForAttribute;

public:
	/* ------- Constructor ------- */
	Tag(std::string newOperation = "", std::string newAttribute = "", bool newExpectsAttribute = false) {
		this->operation = newOperation;
		this->attribute = newAttribute;
		this->checkForAttribute = newExpectsAttribute;
	}

	/* ------- Setters and Getters ----- */
	std::string getOperation() const { return operation; }
	std::string getAttribute() const { return attribute; }
	bool getCheckForAttribute() const { return checkForAttribute; }

	void setOperation(std::string newOperation) { operation = newOperation; }
	void setAttribute(std::string newAttribute) { attribute = newAttribute; }
	void setCheckForAttribute(bool newCheckForAttribute) { checkForAttribute = newCheckForAttribute; }
};
