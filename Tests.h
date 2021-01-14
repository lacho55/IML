#pragma once
#include<iostream>
#include "IMLParser.h"
#include "Operation.h"

void testTranslation() {
	IMLparser parser;
	parser.translate("InputFile.txt", "OutputFile.txt");
}

void testMapOperations() {
	Operation list1("MAP-INC", "5.5");
	list1.addToList(5);
	list1.addToList(10);
	list1.addToList(15);
	list1.applyGivenOperation();
	LList<double> l = list1.getResAsList();
	l.print();

	Operation list2("MAP-MLT", "5");
	list2.addToList(1);
	list2.addToList(5);
	list2.addToList(10);
	list2.applyGivenOperation();
	std::cout << list2.getResAsString() << std::endl;
}

void testAggregateOperations() {
	Operation list1("AGG-SUM");
	list1.addToList(5);
	list1.addToList(10);
	list1.addToList(15);
	list1.applyGivenOperation();
	LList<double> l = list1.getResAsList();
	l.print();

	Operation list2("AGG-PRO");
	list2.addToList(2);
	list2.addToList(3);
	list2.addToList(4);
	list2.addToList(5);
	list2.applyGivenOperation();
	std::cout << list2.getResAsString() << std::endl;

	Operation list3("AGG-AVG");
	list3.addToList(2);
	list3.addToList(4);
	list3.addToList(6);
	list3.addToList(8);
	list3.applyGivenOperation();
	std::cout << list3.getResAsString() << std::endl;

	Operation list4("AGG-FST");
	list4.addToList(2);
	list4.addToList(4);
	list4.addToList(6);
	list4.addToList(8);
	list4.applyGivenOperation();
	std::cout << list4.getResAsString() << std::endl;

	Operation list5("AGG-LST");
	list5.addToList(2);
	list5.addToList(4);
	list5.addToList(6);
	list5.addToList(8);
	list5.applyGivenOperation();
	std::cout << list5.getResAsString() << std::endl;
}

void testSortingOperations() {
	Operation list1("SRT-REV");
	list1.addToList(5);
	list1.addToList(10);
	list1.addToList(15);
	list1.addToList(20);
	list1.applyGivenOperation();
	LList<double> l = list1.getResAsList();
	l.print();

	Operation list2("SRT-ORD", "ASC");
	list2.addToList(8);
	list2.addToList(3.3);
	list2.addToList(6.75);
	list2.addToList(4.2);
	list2.addToList(1);
	list2.applyGivenOperation();
	std::cout << list2.getResAsString() << std::endl;

	Operation list3("SRT-ORD", "DSC");
	list3.addToList(8);
	list3.addToList(3.3);
	list3.addToList(6.75);
	list3.addToList(4.2);
	list3.addToList(1);
	list3.applyGivenOperation();
	std::cout << list3.getResAsString() << std::endl;

	Operation list4("SRT-SLC", "3");
	list4.addToList(1);
	list4.addToList(2);
	list4.addToList(3);
	list4.addToList(4);
	list4.addToList(5);
	list4.applyGivenOperation();
	std::cout << list4.getResAsString() << std::endl;

	Operation list5("SRT-DST");
	list5.addToList(1);
	list5.addToList(5);
	list5.addToList(2);
	list5.addToList(2);
	list5.addToList(2);
	list5.addToList(5);
	list5.addToList(5);
	list5.addToList(5);
	list5.addToList(2);
	list5.addToList(3);
	list5.addToList(5);
	list5.applyGivenOperation();
	std::cout << list5.getResAsString() << std::endl;
}
