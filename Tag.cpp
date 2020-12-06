#pragma once
#include "Tag.h"


/* ------- Setters and Getters ------ */
const std::string Tag::getOperation() const {
	return operation;
}


const std::string Tag::getAttribute() const {
	return attribute;
}


bool Tag::getCheckForAttribute() const {
	return checkForAttribute;
}


void Tag::setOperation(const std::string newOperation) {
	operation = newOperation;
}


void Tag::setAttribute(const std::string newAttribute) {
	attribute = newAttribute;
}


void Tag::setCheckForAttribute(const bool newCheckForAttribute) {
	checkForAttribute = newCheckForAttribute;
}