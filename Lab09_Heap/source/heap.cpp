
#include "heap.h"

template <class DT>
Heap<DT>::Heap(int maxNumber) throw (bad_alloc)
/**
Requirements: None
Results: Constructor. Creates an empty heap. 
  Allocates enough memory for a heap containing maxNumber data items.
**/
	: maxSize(maxNumber), size(0)
{
	dataItems = new DT[maxSize];
}

template <class DT>
Heap<DT>::~Heap()
/**
Requirements: None
Results: Destructor. Deallocates (frees) the memory used to store a heap.
**/
{
	clear();
}

template <class DT>
void Heap<DT>::insert(const DT& newDataItem) throw (logic_error)
/**
Requirements: Heap is not full.
Results: Inserts newDataItem into a heap. Inserts this data item as the bottom rightmost data 
  item in the heap and moves it upward until the properties that define a heap are restored.
**/
{
	if (!isFull())
	{
		dataItems[size] = newDataItem; // insert
		Reheapup(0, size++);
	}
	else
		cout << "Full Heap" << endl;
}

template <class DT>
void Heap<DT>::Reheapup(int root, int bottom)
/**
Requirements: tree is not empty.
Results: make heap recursively
**/
{
	int parent;

	if (bottom > root) // not empty
	{
		parent = (bottom - 1) / 2;
		if (dataItems[parent].pty() < dataItems[bottom].pty())
		{
			Swap(dataItems[parent], dataItems[bottom]);
			Reheapup(root, parent);
		}
	}
}

template <class DT>
DT Heap<DT>::removeMax() throw (logic_error)
/**
Requirements: Heap is not empty.
Results: Removes the data item with the highest priority (the root) from a heap and returns it.
  Replaces the root data item with the bottom rightmost data item and moves this data
  item downward until the properties that define a heap are restored.

**/
{
	if (!isEmpty())
	{
		Swap(dataItems[0], dataItems[--size]);
		Reheapdown(0, size - 1);
		return dataItems[size];
	}
}

template <class DT>
void Heap<DT>::Reheapdown(int root, int bottom)
/**
Requirements: left child is part of the heap.
Results: make heap recursively
**/
{
	int leftchild = 2 * root + 1;
	int rightchild = 2 * root + 2;
	int maxchild;
	if (leftchild <= bottom)	// left child is part of the heap
	{
		if (leftchild == bottom)	// if only one child
			maxchild = leftchild; 
		else		// if two child
		{
			if (dataItems[leftchild].pty() < dataItems[rightchild].pty())
				maxchild = rightchild;
			else
				maxchild = leftchild;
		}
		if (dataItems[root].pty() < dataItems[maxchild].pty())	// compare max child with parent
		{
			Swap(dataItems[root], dataItems[maxchild]);
			Reheapdown(maxchild, bottom);
		}		
	}
}

template <class DT>
void Heap<DT>::Swap(DT& x, DT& y)
/**
Requirements: None.
Results: exchange x and y
**/
{
	DT temp = x;
	x = y;
	y = temp;
}

template <class DT>
bool Heap<DT>::isEmpty() const
/**
Requirements: None.
Results: if heap is empty, return true. else return false.
**/
{
	return size == 0;
}

template <class DT>
bool Heap<DT>::isFull() const
/**
Requirements: None.
Results: if heap is full, return true. else return false.
**/
{
	return size == maxSize;
}

template <class DT>
/**
Requirements: None.
Results: clear heap.
**/
void Heap<DT>::clear()
{
	size = 0;
}