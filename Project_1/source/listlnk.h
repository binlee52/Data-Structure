#ifndef __LISTLNK_H__
#define __LISTLNK_H__

#include <new>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

template <class DT>
class List;

typedef struct address
{
	string name;
	string phone;
	string birth;
} address;


template < class DT >
class ListNode                // Facilitator class for the List class
{
private:
	// Data members
	DT dataItem;      // List data item
	ListNode* next;   // Pointer to the next list node
	int month; // birth's month
	string _;
	friend class List<DT>;

public:
	// Constructor
	ListNode(const DT& nodeData, ListNode* nextPtr = NULL);

	void showItem() const;
	void showBirth() const;
};


template < class DT >
class List
{
private:

	// Data members
	ListNode<DT>* head,     // Pointer to the beginning of the list
		* cursor;   // Cursor pointer
	int month_list[12] = { 0, }; 
	int cnt; // node�� ����
public:

	// Constructor
	List();

	// List manipulation operations
	void fileIn(); // file �� �Է¹޾� ���Ḯ��Ʈ ����
	void fileOut(); // ���Ḯ��Ʈ�� file�� ���
	void insert(const DT& newData); // address type�� ����Ͽ� Node ����
	void add(); // ���ο� Node �߰�
	void remove(); // Node ����
	bool isEmpty() const; 
	void show() const;
	void showListInformation() const; // ���Ḯ��Ʈ�� ���� ���
	void showMonthInformation() const; // Ư�� month�� �¾ �ι��� ���� ���
};


#endif // ! __LISTLNK_H_