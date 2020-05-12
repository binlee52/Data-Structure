#include "listrec.h"

template <class DT>
ListNode<DT>::ListNode(const DT& elem, ListNode<DT>* nextPtr)
	: dataItem(elem), next(nextPtr)
{}

template <class DT>
List<DT>::List(int ignored)
	: head(0), cursor(0)
{}

template <class DT>
List<DT>::~List()
{
	clear();
}

template <class DT>
void List<DT>::clear()
{
	ListNode<DT>* temp;
	while (head == 0)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	head = 0;
	cursor = 0;
}

template <class DT>
void List<DT>::write() const
{
	cout << "List: ";
	writeSub(head);
	cout << endl;
}

template <class DT>
void List<DT>::writeSub(ListNode<DT>* p) const
{
	if (p != 0)
	{
		cout << p->dataItem;
		writeSub(p->next);
	}
}

template <class DT>
void List<DT>::insertEnd(const DT& newDataItem)
// Inserts newDataItem at the end of a list.
// Moves the cursor to newDataItem.
{
	insertEndSub(head, newDataItem);
}

template <class DT>
void List<DT>::insertEndSub(ListNode<DT>*& p, const DT& newDataItem)
// Recursive partner of the insertEnd() function.
// Processes the sublist that begins with the node pointed to by p.
{
	if (p != 0) // general
		insertEndSub(p->next, newDataItem);
	else // base
	{
		p = new ListNode<DT>(newDataItem, 0);
		cursor = p;
	}
}

template <class DT>
void List<DT>::writeMirror() const
{
	cout << "Mirror: ";
	writeMirrorSub(head);
	cout << endl;
}

template <class DT>
void List<DT>::writeMirrorSub(ListNode<DT>* p) const
{
	if (p != 0) // general
	{
		cout << p->dataItem;
		writeMirrorSub(p->next);
		cout << p->dataItem;
	}
	// do nothing in base
}

template <class DT>
void List<DT>::reverse()
{
	reverseSub(0, head);
}

template <class DT>
void List<DT>::reverseSub(ListNode<DT>* p, ListNode<DT>* nextP)
{
	if (nextP != 0) // general
	{
		reverseSub(nextP, nextP->next);
		nextP->next = p;
	}
	else  // base
		head = p;
}

template <class DT>
void List<DT>::deleteEnd()
{
	deleteEndSub(head);
	cursor = head;
}

template <class DT>
void List<DT>::deleteEndSub(ListNode<DT>*& p)
{
	if (p->next != 0) // general
		deleteEndSub(p->next);
	else // base
	{
		delete p;
		p = 0;
	}
}

template <class DT>
int List<DT>::getLength() const
{
	return getLengthSub(head);
}

template <class DT>
int List<DT>::getLengthSub(ListNode<DT>* p) const
{
	int result;

	if (p == 0) // base
		result = 0;
	else // general
		result = (getLengthSub(p->next) + 1);

	return result;
}

template <class DT>
void List<DT>::showStructure() const
{
	showStructureSub(head);
	cout << endl;
}

template <class DT>
void List<DT>::showStructureSub(const ListNode<DT>* p) const
{
	if (p != 0)
	{
		cout << p->dataItem; // print
		if (p->next != 0)
		{
			cout << "|";
			showStructureSub(p->next); // recursive
		}
	}
}

template <class DT>
void List<DT>::insert(const DT& newElement)      // Insert after cursor
{
	ListNode<DT>* newItem = new ListNode<DT>(newElement, 0);

	if (head == 0)
		head = newItem;
	else 
	{
		newItem->next = cursor->next;
		cursor->next = newItem;
	}
	cursor = newItem;
}

template <class DT>
void List<DT>::iterReverse()
{
	ListNode<DT>* next;
	ListNode<DT>* curr;

	curr = head->next; // temporary save item
	head->next = 0; // set head.next = NULL
	while (curr != 0) 
	{
		next = curr->next;
		curr->next = head; 
		head = curr; // change head
		curr = next; // goto next step
	}
}

template <class DT>
void List<DT>::stackWriteMirror() const            // In-lab Exercise 1
{
	Stack<DT> stack;
	ListNode<DT>* p = head;
	cout << "StackMirror : ";
	while (p != 0)
	{
		cout << p->dataItem; // output data
		stack.push(p->dataItem); // push data into Stack
		p = p->next;
	}
	while (!stack.empty())
		cout << stack.pop(); // pop item from stack and print
	cout << endl;
}