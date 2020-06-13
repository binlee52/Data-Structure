#include <assert.h>
#include "queueLnk.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------

template < class QE >
QueueNode<QE>::QueueNode(const QE& elem, QueueNode<QE>* nextPtr)

// Creates a queue node containing element elem and next pointer
// nextPtr.

	: element(elem),
	next(nextPtr)
{}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue()

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.

	: front(NULL),
	rear(NULL)
{}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	// pre-lab (Linked)
	clear();
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE& newElement)

// Inserts newElement at the rear of a queue.

{
	// pre-lab (Linked)
	if (!full())
	{
		QueueNode<QE>* newItem = new QueueNode<QE>(newElement, NULL);
		if (empty())
		{
			rear = newItem;
			front = rear;
		}
		else
		{
			rear->next = newItem;
			rear = rear->next;
		}
	}
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently (front) element from a queue and
// returns it.

{
	// pre-lab (Linked)
	if (!empty())
	{
		QE item = front->element;
		QueueNode<QE>* temp = front;
		front = front->next;
		delete temp;
		if (front == NULL) // if queue is empty
		{
			rear = NULL;
		}
		return item;
	}
	return NULL;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	// pre-lab (Linked)
	while (!empty())
		dequeue();
}


//--------------------------------------------------------------------

template < class QE >
bool Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Linked)
	if (rear == NULL)
		return true;
	return false;
}

template < class QE >
bool Queue<QE>::full() const

// Returns 1 if a queue is full. Otherwise, returns 0.

{
	// pre-lab (Linked)
	QueueNode<QE>* temp = new QueueNode<QE>(NULL, NULL);
	if (!temp)
		return true;
	return false;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
	// pre-lab (Linked)
	if (empty())
		cout << "Empty Queue" << endl;
	else
	{
		QueueNode<QE>* index = front;
		while (index != NULL)
		{
			cout << index->element << "   ";
			index = index->next;
		}
	}
}