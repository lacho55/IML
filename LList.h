#pragma once
#include<iostream>


template<typename T>
struct Node {
	T data;
	Node<T>* next;

	Node(const T& newData, Node<T>* newNext = nullptr) {
		data = newData;
		next = newNext;
	}
};


template<typename>
class LListIterator;

template<typename T>
class LList{
private:
	LList<T>* head;
	LList<T>* tail;

	/* ------- Private Methods -------- */
	void copy(const LList&);

public:
	/* ------- Public Methods ------- */
	LList();
	LList(const LList&);

};


/* ------ Private Methods --------- */
template<typename T>
void LList<T>::copy(const LList<T>& other) {
	for (LListIterator<T> iter = other.begin(); iter; iter++) {
		insertEnd(*iter);
	}
}


/* ------- Public Methods --------- */
template<typename T>
LList<T>::LList() : head(nullptr), tail(nullptr) {}