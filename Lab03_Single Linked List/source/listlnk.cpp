//  파일명: listlnk.cpp
//  작성자: 동국대학교 컴퓨터공학과 2016112122 이한빈

#include "listlnk.h"

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

template<class DT>
List<DT>::List(int ignored)
{
	head = NULL;
	cursor = NULL;
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
	// 할당된 모든 node 제거
	while (head != NULL)
		remove();
	delete cursor;
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
	if (!isFull())
	{
		if (isEmpty())
		{
			ListNode<DT> * newNode = new ListNode<DT>(newData, head);
			head = newNode;
			cursor = head;
		}
		else
		{
			ListNode<DT> * newNode = new ListNode<DT>(newData, cursor->next);
			cursor->next = newNode;
			cursor = cursor->next;
		}
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
	if (!isEmpty())
	{
		if (cursor != head)
		{
			ListNode<DT>* temp = cursor;
			gotoPrior(); // 1단계 앞으로 이동
			cursor->next = cursor->next->next; // 제거할 node를 건너뛰고 연결

			//cursor 값 변경
			if (cursor->next == NULL)
				cursor = head;
			else
				cursor = cursor->next;
		}
		else
		{
			head = head->next;
			cursor = cursor->next;
		}
	}
}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
	if (!isEmpty())
	{
		cursor->dataItem = newData;
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
	ListNode<DT>* tempPtr;
	while (head != NULL)
	{
		tempPtr = head;
		head = head->next;
		delete tempPtr;
	}
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
	if (head == NULL)
		return true;
	return false;
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
	ListNode<DT>* temp = new ListNode<DT>(NULL, NULL); // memory가 꽉차면 만들어지지 않을 것
	if (temp == NULL) // 메모리가 꽉 찼을시
		return true;
	delete temp;
	return false;
}

//------------------------------------------------

template<class DT>
void List<DT>::gotoBeginning()
{
	if (!isEmpty())
		cursor = head;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
	if (!isEmpty())
	{
		while (cursor->next != NULL)
			cursor = cursor->next;
	}
}

//------------------------------------------------

template<class DT>
bool List<DT>::gotoNext()
{
	if (!isEmpty() && cursor->next != NULL)
	{
		cursor = cursor->next;
		return true;
	}
	return false;
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
	if (!isEmpty() && (cursor != head))
	{
		DT temp = cursor->dataItem;
		cursor = head;
		while (cursor->next->dataItem != temp)
		{
			cursor = cursor->next;
		}
		return true;
	}
	return false;
}

//------------------------------------------------


template<class DT>
DT List<DT>::getCursor() const
{
	DT item = cursor->dataItem;		
	return item;
}
 
//------------------------------------------------

template<class DT>
void List<DT>::showStructure() const
{
	if (!isEmpty())
	{
		ListNode<DT>* index = head;
		while (index != NULL)
		{
			cout << index->dataItem << " ";
			index = index->next;
		}
		cout << endl;
		index = head;
		while (index != NULL)
		{
			if (index == cursor)		
				cout << "↑ ";		
			else
				cout << "  ";
			index = index->next;
		}
		cout << endl;
	}
}

//------------------------------------------------
// In-lab operations
template<class DT>
void List<DT>::moveToBeginning()	// Move to beginning
{
	if (!isEmpty())
	{
		DT tempItem = getCursor();
		remove();
		ListNode<DT>* tempNode = new ListNode<DT>(tempItem, head);
		head = tempNode;
		cursor = head;
	}
}

template<class DT>
void List<DT>::insertBefore(const DT& newElement) // Insert before cursor
{
	if (!isFull())
	{
		ListNode<DT>* temp = cursor;
		if (isEmpty())
		{
			insert(newElement);
		}
		else if (gotoPrior())
		{
			insert(newElement);
			cursor->next = temp;
		}
		else
		{
			head  = new ListNode<DT>(newElement, cursor);
			cursor = head;
		}	
	}
}

