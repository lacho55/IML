#pragma once
#include<iostream>
#include<fstream>

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
	void copy(const LList<T>&);
	void clear();
	LListIterator<T> findPrevious(LListIterator<T>);

public:
	/* ------- Public Methods ------- */
	LList();
	LList(const LList<T>&);
	LList<T>& operator=(const LList<T>&);
	~LList();
	bool empty() const;
	bool insertAfter(const T&, LListIterator<T>);
	bool insertBefore(const T&, LListIterator<T>);
	bool deleteAfter(T&, LListIterator<T>);
	bool deleteAt(T&, LListIterator<T>);
	bool deleteBefore(T&, LListIterator<T>);
	T& getAt(LListIterator<T>) const;
	void insertBegin(const T&);
	void insertTail(const T&);
	bool deleteBegin(T&);
	bool deleteTail(T&);
	LList<T>& operator+=(const T&);
	void print(std::ostream& out = cout) const {
		out << '(';
		for (LListIterator<T> iter = begin(); iter; ++iter) {
			out << *iter;
			if (iter != end()) {
				out << ',';
			}
		}
		out << ')';
	}
	void append(LList<T>&);
	int length() const;
	void reverse();
	void unique();
	void append(LList<T>&, const LList<T>&);
	void reverse(LList<T>&);
	void split(const LList<T>&, LList<T>&, LList<T>&);
	LList<T> merge(const LList<T>&, const LList<T>&);
	void mergeSort(LList<T>&);
	

	LListIterator<T> begin() const;
	LListIterator<T> end() const;


};


/* ------ Private Methods --------- */
template<typename T>
void LList<T>::copy(const LList<T>& other) {
	for (LListIterator<T> iter = other.begin(); iter; iter++) {
		insertTail(*iter);
	}
}


template<typename T>
void LList<T>::clear() {
	while (!empty()) {
		T tmp;
		deleteTail(tmp);
	}
}


template<typename T>
LListIterator<T> LList<T>::findPrevious(LListIterator<T> iter) {
	LListIterator<T> prev = begin();

	while (prev && prev.ptr->next != iter.ptr) {
		prev++;
	}

	return prev;
}


/* ------- Public Methods --------- */
template<typename T>
LList<T>::LList() : head(nullptr), tail(nullptr) {}


template<typename T>
LList<T>::LList(const LList<T>& other) {
	head = nullptr;
	tail = nullptr;

	copy(other);
}


template<typename T>
LList<T>& LList<T>::operator=(const LList<T>& other) {
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}


template<typename T>
LList<T>::~LList() {
	clear();
}


template<typename T>
bool LList<T>::empty() const {
	return (head == nullptr && tail == nullptr);
}


template<typename T>
bool LList<T>::insertAfter(const T& newElem, LListIterator<T> iter) {

	//checks if the given list is empty or not
	if (iter.ptr == nullptr && empty()) {
		head = new Node<T>(newElem);
		tail = head;

		return true;
	}
	else if(!iter){
		return false;
	}

	Node<T>* toAdd = new Node<T>(newElem, iter.ptr->next);
	iter.ptr->next = toAdd;
	
	if (list == end()) {
		tail = toAdd;
	}

	return true;
}


template<typename T>
bool LList<T>::insertBefore(const T& newElem, LListIterator<T> iter) {
	//checks if the iterator is pointing to the first element of the given list
	if (iter == begin()) {
		Node<T>* toAdd = new Node<T>(newElem, head);
		
		//checks if the given list is empty and when it is a nullpointer iterator
		if (empty()) {
			tail = toAdd;
		}
		head = toAdd;
		return true;
	}

	if (!iter || empty()) {
		return false;
	}

	//Executing this when iterator is valid and our list is not empty.
	//Also the iterator is not pointing to the first element.

	return insertAfter(newElem, findPrevious(iter));
}


template<typename T>
bool LList<T>::deleteAfter(T& toDel, LListIterator<T> iter) {
	if (!iter || iter == end() || empty()) {
		return false;
	}

	//when the iterator is valid -> is not pointing to the last element
	//and there are at least two elements in the given list

	Node<T>* tmpDel = iter.ptr->next;
	it.ptr->next = it.ptr->next->next;
	toDel = tmpDel;

	if (tmpDel->next == nullptr) {
		tail = iter.ptr;
	}

	delete tmpDel;

	return true;
}


template<typename T>
bool LList<T>::deleteAt(T& toDel, LListIterator<T> iter) {
	if (!iter || empty()) {
		return false;
	}

	if (it == begin()) {
		Node<T>* tmpDel = head;
		head = head->next;

		if (head == nullptr) {
			tail = nullptr;
		}

		toDel = tmpDel->data;
		delete tmpDel;
		return true;
	}

	return deleteAfter(x, findPrevious(iter));
}


template<typename T>
bool LList<T>::deleteBefore(T& toDel, LListIterator<T> iter) {
	if (!iter || iter == begin() || empty) {
		return false;
	}

	//It is a valid iterator
	//Is is not pointing to the first element in the list
	//There are at least two elements in the list

	deleteAt(toDel, findPrevious(iter));
}


template<typename T>
T& LList<T>::getAt(LListIterator<T> iter) const {
	return (iter.get());
}


template<typename T>
void LList<T>::insertBegin(const T& newElem) {
	insertBefore(newElem, begin());
}


template<typename T>
void LList<T>::insertTail(const T& newElem) {
	insertAfter(newElem, end());
}


template<typename T>
bool LList<T>::deleteBegin(T& toDel) {
	return deleteAt(toDel, begin());
}


template<typename T>
bool LList<T>::deleteTail(T& toDel) {
	return deleteAt(toDel, end());
}


template<typename T>
LList<T>& LList<T>::operator+=(const T& newData) {
	insertTail(newData);
	return *this;
}


template<typename T>
void LList<T>::append(LList<T>& other) {
	if (!empty()) {
		tail->next = other.head;
		if (!ther.empty()) {
			tail = other.tail;
		}
	}
	else {
		head = other.head;
		tail = other.tail;
	}

	other.head = nullptr;
	other.tail = nullptr;
}


template<typename T>
int LList<T>::length() const {
	int length = 0;
	for (LListIterator<T> iter = begin(); iter; ++iter) {
		length++;
	}

	return length;
}


template<typename T>
void LList<T>::reverse() {
	if (empty() || head->next == nullptr) {
		return;
	}

	Node<T>* prev = head;
	Node<T>* nextElem = head->next;
	tail = head;
	tail->next = nullptr;

	while (nextElem != nullptr) {
		head = nextElem;
		nextElem = nextElem->next;
		head->next = prev;
		prev = head;
	}
}


template<typename T>
void LList<T>::unique() { //A methods for removing duplicates and turning the list into a set
	T helper;

	for (LListIterator<T> firstIter = begin(); firstIter; ++firstIter) {
		for (LListIterator<T> secondIter = firstIter; secondIter.next(); ) {
			if (*firstIter == *(secondIter.next())) {
				deleteAfter(helper, secondIter);
			}
			else {
				secondIter++;
			}
		}
	}
}


template<typename T>
void LList<T>::append(LList<T>& list1, const LList<T>& list2) {
	for (LListIterator<T> iter = list2.begin(); iter; ++iter) {
		list1 += *iter;
	}
}


template<typename T>
void LList<T>::reverse(LList<T>& list) {
	LListIterator<T> iter = list.begin();

	T helper;

	while (list.deleteAfter(helper, iter)) {
		list.insertBegin(helper);
	}
}


template<typename T>
void LList<T>::split(const LList<T>& list, LList<T>& list1, LList<T>& list2) {
	LList<T>* addFirst = &list1;
	LLisT<T>* addLast = &list2;

	for (LListIterator<T> iter = list.begin(); iter; ++iter) {
		(*addFirst).insertTail(*iter);
		swap(addFirst, addLast);
	}
}


template<typename T>
LList<T> LList<T>::merge(const LList<T>& list1, const LList<T>& list2) {
	LList<T> sorted;
	LListIterator<T> iter1 = list1.begin();
	LListIterator<T> iter2 = list2.begin();

	while (iter1 && iter2) {
		if (*iter1 <= *iter2) {
			sorted += *iter1;
			iter1++;
		}
		else {
			sorted += *iter2;
			iter2++;
		}
	}

	while (iter1) {
		sorted += *iter1;
		iter1++;
	}
	while (iter2) {
		sorted += *iter2;
		iter2++;
	}

	return sorted;
}


template<typename T>
void LList<T>::mergeSort(LList<T>& list) {
	if (list.begin() == list.end()) {
		return;
	}

	LList<T> list1;
	LList<T> list2;

	split(list, list1, list2);

	mergeSort(list1);
	mergeSort(lsit2);

	list = merge(list1, list2);
}


template<typename T>
LListIterator<T> LList<T>::begin() const {
	return LListIterator<T>(head);
}


template<typename T>
LListIterator<T> LList<T>::end() const {
	return LListIterator<T>(tail);
}


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