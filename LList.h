#pragma once
#include <iostream>


template <typename T>
struct LListElement {
	T data;
	LListElement* next;

	LListElement(const T& data, LListElement* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};

template <typename T>
class LListIterator;

template <typename T>
class LList {
private:
	LListElement<T>* front;
	LListElement<T>* back;

	void copy(const LList& l) {
		for (LListIterator<T> it = l.begin(); it; it++)
			this->insertEnd(*it);
	}

	void clear() {
		while (!empty()) {
			T temporary;
			this->deleteEnd(temporary);
		}
	}

	LListIterator<T> findPrevious(LListIterator<T> it) {
		LListIterator<T> previous = begin();
		while (previous && previous.pointer->next != it.pointer)
			previous++;
		return previous;
	}

public:

	LList() : front(nullptr), back(nullptr) {}

	LList(const LList& l) : front(nullptr), back(nullptr) { copy(l); }

	LList& operator= (const LList& l) {
		if (this != &l) {
			clear();
			copy(l);
		}
		return *this;
	}

	~LList() { clear(); }

	bool empty() const { return front == nullptr && back == nullptr; }

	bool insertAfter(const T& newData, LListIterator<T> it) {
		// if the list is empty
		if (it.pointer == nullptr && empty()) {
			front = new LListElement<T>(newData);
			back = front;
			return true;
		}
		else if (!it)
			return false;

		LListElement<T>* newElement = new LListElement<T>(newData, it.pointer->next);
		it.pointer->next = newElement;
		if (it == end())
			back = newElement;
		return true;
	}

	bool insertBefore(const T& newData, LListIterator<T> it) {
		// taking care of the cases in which:
		// 1) it is an iterator pointing to the first element in the list
		// 2) when the list is empty and it is a nullpointer iterator
		if (it == begin()) {
			LListElement<T>* newElement = new LListElement<T>(newData, front);
			if (empty())
				back = newElement;
			front = newElement;
			return true;
		}

		if (!it || empty())
			return false;

		// the iterator is valid and the list is not empty
		// the iterator is not poiting to the first element
		// the check for validity will be delegated to insertAfter

		return insertAfter(newData, findPrevious(it));
	}

	bool deleteAfter(T& x, LListIterator<T> it) {
		if (!it || it == end() || empty())
			return false;

		// it is a valid iterator, it is not pointing to the last element
		// and there are at least 2 elements in the list

		LListElement<T>* toDelete = it.pointer->next;
		it.pointer->next = it.pointer->next->next;
		x = toDelete->data;
		if (toDelete->next == nullptr)
			back = it.pointer;
		delete toDelete;
		return true;
	}

	bool deleteAt(T& x, LListIterator<T> it) {
		if (!it || empty())
			return false;

		// I have to take care of the case in which it == begin()
		// the other cases will be taken care of by deleteAfter

		if (it == begin()) {
			LListElement<T>* toDelete = front;
			front = front->next;
			if (front == nullptr)
				back = nullptr;
			x = toDelete->data;
			delete toDelete;
			return true;
		}

		return deleteAfter(x, findPrevious(it));
	}

	bool deleteBefore(T& x, LListIterator<T> it) {
		if (!it || it == begin() || empty())
			return false;

		// it is a valid iterator
		// it is not pointing to the first element in the list
		// there are at least 2 elements in the list

		deleteAt(x, findPrevious(it));
	}

	T& getAt(LListIterator<T> it) const { return it.get(); }

	void insertBegin(const T& x) { insertBefore(x, begin()); }

	void insertEnd(const T& x) { insertAfter(x, end()); }

	bool deleteBegin(T& x) { return deleteAt(x, begin()); }

	bool deleteEnd(T& x) { return deleteAt(x, end()); }

	LListIterator<T> begin() const { return LListIterator<T>(front); }

	LListIterator<T> end() const { return LListIterator<T>(back); }

	LList& operator += (const T& newData) {
		insertEnd(newData);
		return *this;
	}

	void print(std::ostream& out = std::cout) const {
		out << '(';
		for (LListIterator<T> it = begin(); it; it++) {
			out << *it;
			if (it != end())
				out << ',';
		}
		out << ')' << std::endl;
	}

	// appends the list sent as parameter to *this and turns the parameter into an empty list
	void append(LList& other) {

		if (!empty()) {
			back->next = other.front;
			if (!other.empty())
				back = other.back;
		}
		else {
			front = other.front;
			back = other.back;
		}

		other.front = nullptr;
		other.back = nullptr;
	}

	int length() const {
		int length = 0;
		for (LListIterator<T> it = begin(); it; it++)
			length++;
		return length;
	}

	void reverse() {
		if (empty() || front->next == nullptr)
			return;

		// there are at least 2 elements in the list
		LListElement<T>* previous = front;
		LListElement<T>* following = front->next;
		back = front;
		back->next = nullptr;

		while (following != nullptr) {
			front = following;
			following = following->next;
			front->next = previous;
			previous = front;
		}
	}

	// removes duplicates and turns the list into a set
	void unique() {
		T x;
		for (LListIterator<T> it1 = begin(); it1; it1++) {
			for (LListIterator<T> it2 = it1; it2.next(); ) {
				if (*it1 == *(it2.next()))
					deleteAfter(x, it2);
				else
					it2++;
			}
		}
	}
};

template <typename T>
void append(LList<T>& ls1, const LList<T>& ls2) {
	for (LListIterator<T> it = ls2.begin(); it; it++) {
		ls1 += *it;
	}
}

template <typename T>
void reverse(LList<T>& ls) {
	LListIterator<T> it = ls.begin();
	T x;
	while (ls.deleteAfter(x, it))
		ls.insertBegin(x);
}

template <typename T>
void split(const LList<T>& ls, LList<T>& ls1, LList<T>& ls2) {
	LList<T>* addNow = &ls1;
	LList<T>* addLater = &ls2;
	for (LListIterator<T> it = ls.begin(); it; it++) {
		(*addNow).insertEnd(*it);
		std::swap(addNow, addLater);
	}
}

template <typename T>
LList<T> merge(const LList<T>& ls1, const LList<T>& ls2) {
	LList<T> sorted;
	LListIterator<T> it1 = ls1.begin(), it2 = ls2.begin();

	while (it1 && it2) {
		if (*it1 <= *it2) {
			sorted += *it1;
			it1++;
		}
		else {
			sorted += *it2;
			it2++;
		}
	}

	while (it1) {
		sorted += *it1;
		it1++;
	}
	while (it2) {
		sorted += *it2;
		it2++;
	}
	return sorted;
}

template <typename T>
void mergeSort(LList<T>& ls) {
	// if the list is empty or contains only 1 element then it is sorted
	if (ls.begin() == ls.end())
		return;

	LList<T> ls1, ls2;
	split(ls, ls1, ls2);

	mergeSort(ls1);
	mergeSort(ls2);

	ls = merge(ls1, ls2);
}

template <typename T>
class LListIterator {
private:

	LListElement<T>* pointer;
	// static T error;

public:

	friend class LList<T>;

	// construction from a pointer
	LListIterator(LListElement<T>* p = nullptr) : pointer(p) {}

	// next position
	LListIterator next() const {
		// assuming the iterator is valid
		// if (!valid())
		//  return *this;
		return LListIterator(pointer->next);
	}

	// previous position
	LListIterator prev() const;

	// access to an element with a possibility of changing it
	T& get() const {
		// assuming the iterator is valid
		// if (!valid())
		//  return error;
		return pointer->data;
	}

	// access to an element without a possibility of changing it
	const T& getConst() const {
		// assuming the iterator is valid
		// if (!valid())
		//  return error;
		return pointer->data;
	}

	// check for validity
	bool valid() const { return pointer != nullptr; }

	// comparison of two iterators
	bool operator==(const LListIterator& it) const { return pointer == it.pointer; }

	bool operator!=(const LListIterator& it) const { return !(*this == it);  }

	// syntactic sugar

	// *it <-> it.get()
	T& operator*() const { return get(); }

	// it++ <-> it = it.next(), returns the old value of it
	LListIterator operator++(int) {
		LListIterator old = *this;
		*this = next();
		return old;
	}

	// ++it <-> it = it.next(), returns the new value of it
	LListIterator& operator++() {
		*this = next();
		return *this;
	}

	// it <-> it.valid()
	operator bool() const { return valid(); }
};