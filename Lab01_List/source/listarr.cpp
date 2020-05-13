//--------------------------------------------------------------------
//	2020-03-19 pre-lab, in-lab 
//  파일명: listarr.cpp
//  작성자: 동국대학교 컴퓨터공학과 2016112122 이한빈
//--------------------------------------------------------------------


#include "listarr.h"

using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).

	: maxSize(maxNumber),
	size(0),
	cursor(-1)
{
	// pre-lab
	dataItems = new DataType[maxSize];
}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems;
}

//--------------------------------------------------------------------

void List::insert(const DataType& newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	if (isFull())
	{
		cout << "Full List!" << endl << endl;
	}
	else if (isEmpty())	
	{
		dataItems[++cursor] = newDataItem;
		size++;
	}
	else
	{
		for (int i = size - 1; i > cursor; i--) {
			dataItems[i] = dataItems[i - 1];
		}
		dataItems[++cursor] = newDataItem;
		size++;
	}
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.

{
	if (!isEmpty())
	{
		for (int i = cursor; i < size; i++)
		{
			dataItems[i] = dataItems[i + 1];
		}
		// if the deleted data was at the end of the list
		if (size - 1 == cursor)
			cursor--;
		size--;
	}
}

//--------------------------------------------------------------------

void List::replace(const DataType& newDataItem)
throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.

{
	// Requires that the list is not empty
	// pre-lab
	if (!isEmpty())
	{
		dataItems[cursor] = newDataItem;
	}
}

//--------------------------------------------------------------------

void List::clear()

// Removes all the data items from a list.

{	
	// remove data in list
	for (int i = 0; i < maxSize; i++)
	{
		dataItems[i] = NULL;
	}
	// initialize size and location of cursor
	size = 0;
	cursor = -1;
}

//--------------------------------------------------------------------

bool List::isEmpty() const

// Returns 1 if a list is empty. Otherwise, returns 0.

{
	if (size == 0)
		return 1;
	else
		return 0;
}

//--------------------------------------------------------------------

bool List::isFull() const

// Returns 1 if a list is full. Otherwise, returns 0.

{
	if (size == maxSize)
		return 1;
	else
		return 0;
}

//--------------------------------------------------------------------

int List::gotoBeginning() throw (logic_error)

// Moves the cursor to the beginning of the list.

{
	// pre-lab ??
	if (!isEmpty())
	{
		cursor = 0;
		return 1;
	}
	return 0;
}



//--------------------------------------------------------------------

int List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	if (!isEmpty())
	{
		cursor = size - 1;
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.

{
	if (!isEmpty() && cursor < size - 1)
	{
		cursor++;
		return true;
	}
	else
		return false;
}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	if (!isEmpty() && cursor != 0)
	{
		cursor--;
		return true;
	}
	else
		return false;
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)

// Returns the item marked by the cursor.

{
	// pre-lab
	return dataItems[cursor];
}

//--------------------------------------------------------------------

void List::showStructure() const

// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
	// pre-lab
	if (isEmpty())
	{
		cout << "Empty list" << endl << endl;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			cout << dataItems[i] << "  ";
		}
	}
}

