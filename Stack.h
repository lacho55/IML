#pragma once

template <typename T>
struct stackNode {
	T data;
	stackNode<T>* previous;
};

template <typename T>
class Stack {
private:
	stackNode<T>* top;

	// copies a stack whose element on top is *toCopy
	void copy(stackNode<T>* toCopy);
	void eraseStack();

public:

	Stack();

	Stack(const Stack&);

	Stack& operator= (const Stack&);

	~Stack();

	void push(const T&);

	T pop();

	T& peek() const;

	bool empty() const;

	Stack<T>& operator+= (const T& newData);
};

template <typename T>
Stack<T>::Stack() : top(nullptr) {}

template <typename T>
bool Stack<T>::empty() const { return top == nullptr; }

template <typename T>
void Stack<T>::push(const T& newData) {
	stackNode<T>* newElement = new stackNode<T>;
	(*newElement).data = newData;
	newElement->previous = top;
	top = newElement;
}

template <typename T>
T Stack<T>::pop() {
	if (empty()) {
		std::cout << "Warning! The stack is already empty!\n";
		return T();
	}
	else {
		stackNode<T>* temporary = top;
		top = temporary->previous;

		T returnedData = temporary->data;
		delete temporary;
		return returnedData;
	}
}

template <typename T>
T& Stack<T>::peek() const {
	if (empty()) {
		std::cout << "Warning! The stack is already empty!\n";
		return T();
	}

	return top->data;
}

template <typename T>
void Stack<T>::eraseStack() {
	while (!empty())
		pop();
}

template <typename T>
Stack<T>::~Stack() {
	eraseStack();
}

template <typename T>
void Stack<T>::copy(stackNode<T>* toCopy) {

	// base case
	if (toCopy == nullptr)
		return;

	// first, we copy all elements pushed before *toCopy
	copy(toCopy->previous);

	// finally, we push the last element from the stack
	push(toCopy->data);
}

template <typename T>
Stack<T>& Stack<T>::operator= (const Stack<T>& ls) {
	if (this != &ls) {
		eraseStack();
		copy(ls.top);
	}
	return *this;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& ls) : top(nullptr) {
	copy(ls.top);
}

template <typename T>
Stack<T>& Stack<T>::operator+= (const T& newData) {
	push(newData);
	return *this;
}