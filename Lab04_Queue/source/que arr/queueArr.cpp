//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueArr.cpp
//
//  SOLUTION: Array implementation of the Queue ADT
//
//--------------------------------------------------------------------

#include <assert.h>
#include "queuearr.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int maxNumber)

// Creates an empty queue. Allocates enough memory for maxNumber
// elements (defaults to defMaxQueueSize).

: maxSize(maxNumber + 1),
front(maxSize - 1),
rear(maxSize - 1)
{
	// make circular queue
	// no value in front
	element = new QE[maxSize];
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	delete[] element;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	if (!full())
	{
		rear = (rear + 1) % maxSize;
		element[rear] = newElement;
	}
	else
		cout << "Full Queue" << endl;
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently added (front) element from a queue and
// returns it.

{
	// pre-lab (Array)
	if (!empty())
	{
		front = (front + 1) % maxSize;
		QE item = element[front];
		if (empty()) // deque 후에 putFront를 했을 때, 값이 하나 사라지는 오류 제거
			clear();
		return item;
	}
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	// pre-lab (Array)
	// init
	front = maxSize - 1;
	rear = maxSize - 1;
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	// pre-lab (Array)
	if (front == rear)
		return 1;
	return 0;
}

//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::full() const

// Returns 1 if a queue is full. Otherwise, returns 0.

{
	if (front == ((rear + 1) % maxSize))
		return 1;
	return 0;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Array implementation. Outputs the elements in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
	if (empty())
		cout << "Empty queue" << endl;
	else
	{	
		// only for testing and debugging
		//cout << "front value: " << element[(front + 1) % maxSize] << ", rear: " << element[(rear + maxSize)% maxSize] << endl;
		//for (int i = 0; i < maxSize - 1; i++)
		//	cout << "   " << i;
		//cout << endl;
		for (int i = ((front + 1) % maxSize); i <= (rear % maxSize); i++)
		{
			cout << "   " << element[i];
		}
		cout << endl;
	}
}
template < class QE >
void Queue<QE>::putFront(const QE &newDataItem){
	//In-Lab. 2
	if (!full())
	{
		// 앞에 값을 넣기 위해 queue의 value를 한칸씩 뒤로 이동ㄱㄱ
		for (int i = getLength(); i > 0; i--)
		{
			element[i] = element[i - 1];
		}
		element[(front + 1) % maxSize] = newDataItem;
		rear = (rear + 1) % maxSize;
	}
}

template < class QE >
QE Queue<QE>::getRear(){
	//In-Lab. 2
	if (!empty())
	{
		QE item = element[rear];
		rear = (rear - 1 + maxSize) % maxSize;
		return item;
	}
	else
		return NULL;
}

template < class QE >
int Queue<QE>::getLength(){
	//In-Lab. 3
	return (rear - front + maxSize) % maxSize;
}
