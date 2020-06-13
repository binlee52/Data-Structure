#pragma once

template < class ST >
class Stack;

template < class ST >
class StackNode;

template < class ST >
class Stack
{
public:

	// Constructor
	Stack();

	// Destructor
	~Stack();

	// Stack manipulation operations
	void push(const ST& newElement);    // Enqueue element
	ST pop();                            // Dequeue element
	void clear();                            // Clear queue

	// Stack status operations
	bool empty() const;                       // Stack is empty
	bool full() const;                        // Stack is full

	// Output the queue structure -- used in testing/debugging
	void showStructure() const;

private:

	// Data members
	StackNode<ST>* top;    // Pointer to the top element
	friend class Maze;
};

template < class ST >
class StackNode               // Facilitator class for the Stack class
{
private:

	// Constructor
	StackNode(const ST& elem, StackNode* nextPtr);

	// Data members
	ST element;          // Stack element
	StackNode* next;     // Pointer to the next element

	friend class Stack<ST>;
};

