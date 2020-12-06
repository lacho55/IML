#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* next;

	Node(const T& data, Node* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};

template <typename T>
class LListitererator;

template <typename T>
class LList {
private:
	Node<T>* head;
	Node<T>* tail;

	void copy(const LList& l) {
		for (LListitererator<T> iter = l.begin(); iter; iter++)
			this->insertTail(*iter);
	}

	void clear() {
		while (!isEmpty()) {
			T tmp;
			this->deleteTail(tmp);
		}
	}

	LListitererator<T> findPrevious(LListitererator<T> iter) {
		LListitererator<T> previous = begin();
		while (previous && previous.ptr->next != iter.ptr)
			previous++;
		return previous;
	}

public:

	LList() : head(nullptr), tail(nullptr) {}

	LList(const LList& l) : head(nullptr), tail(nullptr) { copy(l); }

	LList& operator= (const LList& l) {
		if (this != &l) {
			clear();
			copy(l);
		}
		return *this;
	}

	~LList() { clear(); }

	bool isEmpty() const { return head == nullptr && tail == nullptr; }

	bool insertAfter(const T& newData, LListitererator<T> iter) {
		// if the list is isEmpty
		if (iter.ptr == nullptr && isEmpty()) {
			head = new Node<T>(newData);
			tail = head;
			return true;
		}
		else if (!iter)
			return false;

		Node<T>* newElement = new Node<T>(newData, iter.ptr->next);
		iter.ptr->next = newElement;
		if (iter == end())
			tail = newElement;
		return true;
	}

	bool insertBefore(const T& newData, LListitererator<T> iter) {
		// taking care of the cases in which:
		// 1) iter is an itererator pointing to the first element in the list
		// 2) when the list is isEmpty and iter is a nullptr itererator
		if (iter == begin()) {
			Node<T>* newElement = new Node<T>(newData, head);
			if (isEmpty())
				tail = newElement;
			head = newElement;
			return true;
		}

		if (!iter || isEmpty())
			return false;

		// the itererator is valid and the list is not isEmpty
		// the itererator is not poitering to the first element
		// the check for validitery will be delegated to insertAfter

		return insertAfter(newData, findPrevious(iter));
	}

	bool deleteAfter(T& data, LListitererator<T> iter) {
		if (!iter || iter == end() || isEmpty())
			return false;

		// iter is a valid itererator, iter is not pointing to the last element
		// and there are at least 2 elements in the list

		Node<T>* toDelete = iter.ptr->next;
		iter.ptr->next = iter.ptr->next->next;
		data = toDelete->data;
		if (toDelete->next == nullptr)
			tail = iter.ptr;
		delete toDelete;
		return true;
	}

	bool deleteAt(T& data, LListitererator<T> iter) {
		if (!iter || isEmpty())
			return false;

		// I have to take care of the case in which iter == begin()
		// the other cases will be taken care of by deleteAfter

		if (iter == begin()) {
			Node<T>* toDelete = head;
			head = head->next;
			if (head == nullptr)
				tail = nullptr;
			data = toDelete->data;
			delete toDelete;
			return true;
		}

		return deleteAfter(data, findPrevious(iter));
	}

	bool deleteBefore(T& data, LListitererator<T> iter) {
		if (!iter || iter == begin() || isEmpty())
			return false;

		// iter is a valid itererator
		// iter is not pointing to the first element in the list
		// there are at least 2 elements in the list

		deleteAt(data, findPrevious(iter));
	}

	T& getAt(LListitererator<T> iter) const { return iter.get(); }

	void insertHead(const T& data) { insertBefore(data, begin()); }

	void insertTail(const T& data) { insertAfter(data, end()); }

	bool deleteHead(T& data) { return deleteAt(data, begin()); }

	bool deleteTail(T& data) { return deleteAt(data, end()); }

	LListitererator<T> begin() const { return LListitererator<T>(head); }

	LListitererator<T> end() const { return LListitererator<T>(tail); }

	LList& operator += (const T& newData) {
		insertTail(newData);
		return *this;
	}

	void print(ostream& out = cout) const {
		out << '(';
		for (LListitererator<T> iter = begin(); iter; iter++) {
			out << *iter;
			if (iter != end())
				out << ',';
		}
		out << ')' << endl;
	}

	// appends the list sent as parameter to *this and turns the parameter into an isEmpty list
	void append(LList& other) {

		if (!isEmpty()) {
			tail->next = other.head;
			if (!other.isEmpty())
				tail = other.tail;
		}
		else {
			head = other.head;
			tail = other.tail;
		}

		other.head = nullptr;
		other.tail = nullptr;
	}

	int length() const {
		int length = 0;
		for (LListitererator<T> iter = begin(); iter; iter++)
			length++;
		return length;
	}

	void reverse() {
		if (isEmpty() || head->next == nullptr)
			return;

		// there are at least 2 elements in the list
		Node<T>* previous = head;
		Node<T>* following = head->next;
		tail = head;
		tail->next = nullptr;

		while (following != nullptr) {
			head = following;
			following = following->next;
			head->next = previous;
			previous = head;
		}
	}

	// removes duplicates and turns the list into a set
	void unique() {
		T data;
		for (LListitererator<T> iter1 = begin(); iter1; iter1++) {
			for (LListitererator<T> iter2 = iter1; iter2.next(); ) {
				if (*iter1 == *(iter2.next()))
					deleteAfter(data, iter2);
				else
					iter2++;
			}
		}
	}
};

template <typename T>
void append(LList<T>& list1, const LList<T>& list2) {
	for (LListitererator<T> iter = list2.begin(); iter; iter++) {
		list1 += *iter;
	}
}

template <typename T>
void reverse(LList<T>& ls) {
	LListitererator<T> iter = ls.begin();
	T data;
	while (ls.deleteAfter(data, iter))
		ls.insertHead(data);
}

template <typename T>
void spliter(const LList<T>& ls, LList<T>& list1, LList<T>& list2) {
	LList<T>* addNow = &list1;
	LList<T>* addLater = &list2;
	for (LListitererator<T> iter = ls.begin(); iter; iter++) {
		(*addNow).insertTail(*iter);
		swap(addNow, addLater);
	}
}

template <typename T>
LList<T> merge(const LList<T>& list1, const LList<T>& list2) {
	LList<T> sorted;
	LListitererator<T> iter1 = list1.begin(), iter2 = list2.begin();

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

template <typename T>
void mergeSort(LList<T>& ls) {
	// if the list is isEmpty or contains only 1 element then iter is sorted
	if (ls.begin() == ls.end())
		return;

	LList<T> list1, list2;
	spliter(ls, list1, list2);

	mergeSort(list1);
	mergeSort(list2);

	ls = merge(list1, list2);
}

template <typename T>
class LListitererator {
private:

	Node<T>* ptr;
	// static T error;

public:

	friend class LList<T>;

	// construction from a ptr
	LListitererator(Node<T>* p = nullptr) : ptr(p) {}

	// next position
	LListitererator next() const {
		// assuming the itererator is valid
		// if (!valid())
		//  return *this;
		return LListitererator(ptr->next);
	}

	// previous position
	LListitererator prev() const;

	// access to an element witerh a possibilitery of changing iter
	T& get() const {
		// assuming the itererator is valid
		// if (!valid())
		//  return error;
		return ptr->data;
	}

	// access to an element witerhout a possibilitery of changing iter
	const T& getConst() const {
		// assuming the itererator is valid
		// if (!valid())
		//  return error;
		return ptr->data;
	}

	// check for validitery
	bool valid() const { return ptr != nullptr; }

	// comparison of two itererators
	bool operator==(const LListitererator& iter) const { return ptr == iter.ptr; }

	bool operator!=(const LListitererator& iter) const { return !(*this == iter); }

	// syntactic sugar

	// *iter <-> iter.get()
	T& operator*() const { return get(); }

	// iter++ <-> iter = iter.next(), returns the old value of iter
	LListitererator operator++(int) {
		LListitererator old = *this;
		*this = next();
		return old;
	}

	// ++iter <-> iter = iter.next(), returns the new value of iter
	LListitererator& operator++() {
		*this = next();
		return *this;
	}

	// iter <-> iter.valid()
	operator bool() const { return valid(); }
};