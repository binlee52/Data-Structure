#include <assert.h>
#include "stackLnk.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------

template < class ST >
StackNode<ST>::StackNode(const ST& elem, StackNode<ST>* nextPtr)
// Creates a queue node containing element elem and next pointer
// nextPtr.

	: element(elem),
	next(nextPtr)
{}

//--------------------------------------------------------------------

template < class ST >
Stack<ST>::Stack()

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.

	: top(NULL)
{}

//--------------------------------------------------------------------

template < class ST >
Stack<ST>:: ~Stack()

// Frees the memory used by a queue.

{
	// pre-lab (Linked)
	clear();
}

//--------------------------------------------------------------------

template < class ST >
void Stack<ST>::push(const ST& newElement)

// Inserts newElement at the rear of a queue.

{
	// pre-lab (Linked)
	if (!full())
	{
		StackNode<ST>* newItem = new StackNode<ST>(newElement, top);
		top = newItem;
	}
}

//--------------------------------------------------------------------

template < class ST >
ST Stack<ST>::pop()

// Removes the least recently (front) element from a queue and
// returns it.

{
	// pre-lab (Linked)
	if (!empty())
	{
		ST item = top->element;
		StackNode<ST>* temp = top;
		top = top->next;
		delete temp;
		return item;
	}
	return NULL;
}

//--------------------------------------------------------------------

template < class ST >
void Stack<ST>::clear()

// Removes all the elements from a queue.

{
	// pre-lab (Linked)
	while (!empty())
		pop();
}


//--------------------------------------------------------------------

template < class ST >
bool Stack<ST>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Linked)
	if (top == NULL)
		return true;
	return false;
}

template < class ST >
bool Stack<ST>::full() const

// Returns 1 if a queue is full. Otherwise, returns 0.

{
	// pre-lab (Linked)
	StackNode<ST>* temp = new StackNode<ST>(NULL, NULL);
	if (!temp)
		return true;
	return false;
}

//--------------------------------------------------------------------

template < class ST >
void Stack<ST>::showStructure() const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
	// pre-lab (Linked)
	if (empty())
		cout << "Empty Stack" << endl;
	else
	{
		StackNode<ST>* index = top;
		while (index != NULL)
		{
			cout << index->element << "   ";
			index = index->next;
		}
	}
}