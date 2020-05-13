//--------------------------------------------------------------------
//
//  Laboratory 10                                          listrec.h
//
//  Class declarations for a partial linked list implementation of
//  the List ADT with additional recursive linked list functions
//
//--------------------------------------------------------------------

#include <iostream>
#include "stacklnk.cpp"
using namespace std;

template < class DT > class ListNode;
template < class DT > class List;


template < class DT >
class ListNode                 // Facilitator class for the List class
{
private:

	// Constructor
	ListNode(const DT &elem, ListNode *nextPtr);

	// Data members
	DT dataItem;        // List element
	ListNode *next;    // Pointer to the next element

	friend class List<DT>;
};

//--------------------------------------------------------------------

template < class DT >
class List
{
public:

	// Constructor
	List(int ignored = 0);

	// Destructor
	~List();

	//List manipulation functions
	void insert(const DT &newElement);      // Insert after cursor
	void clear();                             // Clear list

	// Output the list structure -- used in testing/debugging
	void showStructure() const;

	// Prelab functions
	void write() const;                       // Output list elements
	void insertEnd(const DT &newElement);   // Insert at end
	void writeMirror() const;                 // Mirror view of list
	void reverse();                           // Reverse list
	void deleteEnd();                         // Delete from end
	int getLength() const;                       // Length of list

	// In-lab functions
	void iterReverse();                       // In-lab Exercise 1
	void stackWriteMirror() const;            // In-lab Exercise 1

private:

	// Recursive partners of the Prelab functions
	void writeSub(ListNode<DT> *p) const;
	void insertEndSub(ListNode<DT> *&p, const DT &newElement);
	void writeMirrorSub(ListNode<DT> *p) const;
	void reverseSub(ListNode<DT> *p, ListNode<DT> *nextP);
	void deleteEndSub(ListNode<DT> *&p);
	int getLengthSub(ListNode<DT> *p) const;
	void showStructureSub(const ListNode<DT>* p) const;

private:

	// Data members
	ListNode<DT> *head,     // Pointer to the beginning of the list
					*cursor;   // Cursor pointer
};

