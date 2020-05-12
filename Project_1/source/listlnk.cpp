#include "listlnk.h"
#include "usefulFunction.h"
#include <fstream>


template < class DT >
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr) // 주의
	: dataItem(nodeData), next(nextPtr)
{
	_ = dataItem.birth.substr(0, _.find("/"));
	month = atoi(_.c_str());
}

template < class DT >
void ListNode<DT>::showItem() const
{
	cout << dataItem.name << endl;
	cout << dataItem.phone << endl;
	cout << dataItem.birth << endl;
}

template < class DT >
void ListNode<DT>::showBirth() const
{
	cout << monthToString(month) << endl;
}


template < class DT >
List<DT>::List()
	: head(NULL), cursor(NULL), cnt(0)
{};


template < class DT >
void List<DT>::insert(const DT& newData)

{
	if (isEmpty())
	{
		ListNode<DT>* newNode = new ListNode<DT>(newData, head);
		month_list[(newNode->month - 1)]++;
		head = newNode;
		cursor = head;
	}
	else
	{
		ListNode<DT>* newNode = new ListNode<DT>(newData, cursor->next);
		month_list[(newNode->month - 1)]++;
		cursor->next = newNode;
		cursor = cursor->next;
	}
	cnt++;
}

template <class DT>
void List<DT>::fileIn()
{
	cout << "Enter the name of the file: ";
	string path;
	cin.ignore(); // buffer 삭제
	getline(cin, path);
	path = path + ".txt";

	int arr_size = 1024;
	char* array = new char[arr_size];
	int position = 0;

	// file open
	ifstream fin(path.data());

	// 파일이 성공적으로 열렸을시
	if (fin.is_open())
	{
		string line;
		string temp[4];
		int index = 0;
		while (getline(fin, line))
		{
			temp[index] = line;
			if (index == 2)
			{
				address x;
				x.name = temp[0];
				x.phone = temp[1];
				x.birth = temp[2];
				insert(x);
			}
			if (index == 3)
				index = 0;
			else
				index++;
		}

		fin.close();
	}
	else
	{
		cout << "Fail" << endl;
	}
}

template <class DT>
void List<DT>::fileOut()
{
	cout << "Enter the name of the file: ";
	string path;
	cin.ignore();
	getline(cin, path);
	string temp = path;
	path = path + ".txt"; // file type까지 입력받지 않으므로

	//file 출력
	ofstream out(path);
	if (!isEmpty())
	{
		ListNode<DT>* p = head;
		while (p != NULL)
		{
			out << p->dataItem.name << endl;
			out << p->dataItem.phone << endl;
			out << p->dataItem.birth << endl;
			out << endl;
			p = p->next;
		}
		cout << "The list is written into " << temp << endl;
	}
}

template <class DT>
void List<DT>::remove()
{
	string delname;
	cout << "Remove an entry: " << endl;
	cout << "Name: ";
	cin.ignore();
	getline(cin, delname);

	if (!isEmpty())
	{
		ListNode<DT>* p = head;
		ListNode<DT>* prev = head;
		while (p != NULL)
		{
			if (p->dataItem.name == delname)
			{	
				month_list[p->month - 1]--;
				if (p == head) // 첫번째 node일시
					head = p->next;
				else // 첫 노드가 아닐시
					prev->next = p->next;
				break;
			}
			prev = p;
			p = p->next;
		}
		cnt--;
	}
}

template <class DT>
void List<DT>::add()
{
	address newAddress;
	string a, b, c;

	cin.ignore();
	cout << "Add an entry:" << endl;
	cout << "Name: ";
	getline(cin, a);
	newAddress.name = a;

	cout << "Phone: ";
	getline(cin, b);
	newAddress.phone = b;

	cout << "Birthday: ";
	getline(cin, c);
	newAddress.birth = c;

	insert(newAddress);
}

template < class DT >
bool List<DT>::isEmpty() const
{
	if (head == NULL)
		return true;
	return false;
}

template < class DT >
void List<DT>::show() const
{
	if (!isEmpty())
	{
		ListNode<DT>* p = head;
		while (p != NULL)
		{
			p->showItem();
			cout << endl;
			p = p->next;
		}
	}
}

template < class DT >
void List<DT>::showListInformation() const
{
	cout << "   Total number of entries in the list: " << cnt << endl;
	cout << "Number of birthdays in" << endl;
	for (int i = 0; i < 12; i++)
	{
		if (month_list[i] > 0) // 태어난 인원이 1명 이상 있는 달의 정보를 출력
			cout << "      " << monthToString(i + 1) << ": " << month_list[i] << endl;
	}
}

template <class DT>
void List<DT>::showMonthInformation() const
{
	string m;
	cout << "Enter the selected month: ";
	cin.ignore();
	getline(cin, m);
	int n = stringToMonth(m);
	if (n < 1 || n > 12)
		cout << "Unknown Input Value" << endl;
	else
	{
		cout << "Total number of birthdays in " << m << ": " << month_list[n - 1] << endl;
		ListNode<DT>* p = head;
		while (p != NULL)
		{
			if (p->month == n)
			{
				p->showItem();
				cout << endl;
			}
			p = p->next;
		}		
	}
}

// template은 원래 .h, .cpp 분할을 지원하지 않음. 사용할 데이터 타입을 미리 작성해줘야 함.
template class ListNode<address>;
template class List<address>;
