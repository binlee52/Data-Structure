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
	int cnt; // node의 개수
public:

	// Constructor
	List();

	// List manipulation operations
	void fileIn(); // file 을 입력받아 연결리스트 생성
	void fileOut(); // 연결리스트를 file로 출력
	void insert(const DT& newData); // address type을 사용하여 Node 생성
	void add(); // 새로운 Node 추가
	void remove(); // Node 삭제
	bool isEmpty() const; 
	void show() const;
	void showListInformation() const; // 연결리스트의 개요 출력
	void showMonthInformation() const; // 특정 month에 태어난 인물의 정보 출력
};


#endif // ! __LISTLNK_H_