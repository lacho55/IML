#pragma once
#include<iostream>


template<class T>
struct Node {
	T data;
	Node<T>* prev;
};


template<class T>
class Stack {
private:
	Node<T>* top;

	/* ------- Private Methods ------ */
	void copy(Node<T>*);
	void eraseStack();
	
public:
	/* ------- Public Methods ------- */
	Stack();
	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
	~Stack();
	
	void push(const T&);
	bool empty() const;
	T pop();
	T& peek() const;
	Stack<T>& operator+=(const T&);
};


/* -------- Pivate Methods ------- */
template<typename T>
void Stack<T>::copy(Node<T>* other) {
	if (other == nullptr) {
		return;
	}

	//Copying all elements pushed before *other
	copy(other->pev);

	//Lastly we push our last element from the stack
	push(other->data);
}


template<typename T>
void Stack<T>::eraseStack() {
	while (!empty()) {
		pop();
	}
}


/* -------- Public Methods -------*/
template<typename T>
Stack<T>::Stack() {
	top = nullptr;
}


template<typename T>
void Stack<T>::push(const T& newElem) {
	Node<T>* toAdd = new Node<T>;
	(*toAdd).data = newElem;
	toAdd->prev = top;
	top = toAdd;
}


template<typename T>
bool Stack<T>::empty() const {
	return (top == nullptr);
}


template<typename T>
T Stack<T>::pop() {

	if (empty()) {
		std::cout << "Sorry but the stack is already empty!" << std::endl;
		return T();
	}
	else {
		Node<T>* tmp = top;
		top = tmp->prev;

		T finalData = tmp->data;
		delete tmp;
		return finalData;
	}
}


template<typename T>
T& Stack<T>::peek() const {
	if (empty()) {
		std::cout << "Sorry but the stack is already empty!" << std::endl;
		return T();
	}

	return top->data;
}