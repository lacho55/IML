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


/* -------- Iterator -------- */
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




/* ------- Iterator -------*/
template<typename T>
class LListIterator {
private:
	Node<T>* ptr;

public:
	/* ------ Public Iterator Methods -------- */
	friend class LList<T>;
	LListIterator(Node<T>* newPtr = nullptr) : ptr(newPtr) {}
	LListIterator<T> next() const;
	LListIterator<T> prev() const;
	T& get() const;
	bool valid() const;
	bool operator==(const LListIterator<T>&) const;
	bool operator!=(const LListIterator<T>&) const;
	T& operator*() const;
	LListIterator<T> operator++(int);
	LListIterator<T>& operator++();
	operator bool() {
		return valid();
	}
};


/* -------- Public Iterator Methods ------- */
template<typename T>
LListIterator<T> LListIterator<T>::next() const {
	return LListIterator(ptr->next);
}


template<typename T>
T& LListIterator<T>::get() const {
	return ptr->data;
}


template<typename T>
bool LListIterator<T>::valid() const {
	return (ptr != nullptr);
}


template<typename T>
bool LListIterator<T>::operator==(const LListIterator<T>& iter) const{
	return (ptr == iter.ptr);
}


template<typename T>
bool LListIterator<T>::operator!=(const LListIterator<T>& iter) const {
	return !(*this == iter);
}


template<typename T>
T& LListIterator<T>::operator*() const {
	return get();
}


template<typename T>
LListIterator<T> LListIterator<T>::operator++(int) {
	LListIterator prevData = *this;
	*this = next();
	
	return prevData;
}


template<typename T>
LListIterator<T>& LListIterator<T>::operator++() {
	*this = next();
	
	return *this;
}