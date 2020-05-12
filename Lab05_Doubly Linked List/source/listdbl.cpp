#include "listdbl.h"
#include <iostream>
using namespace std;

template <class DT>
ListNode<DT>::ListNode(const DT& data, ListNode<DT>* priorPtr, ListNode<DT>* nextPtr)
    : dataItem(data), prior(priorPtr), next(nextPtr)
{}

template <class DT>
List<DT>::List(int ignored)
{
    head = NULL;
    cursor = head;
}

template <class DT>
List<DT>::~List()
{
    // pass
}

template <class DT>
void List<DT>::insert(const DT &newDataItem)
{
    if (!isFull())
    {
        ListNode<DT>* newNode = new ListNode<DT>(newDataItem, NULL, NULL);
        if (isEmpty()) // List�� ���������
        {
            head = newNode;
            cursor = newNode;
        }
        else
        {
            newNode->prior = cursor;
            if (cursor->next != NULL) // cursor�� ����Ű�� Node�� List�� ������ Node�� �ƴҽ�
            {                  
                newNode->next = cursor->next;
                newNode->next->prior = newNode;                
            }           
            newNode->prior->next = newNode;
            cursor = newNode;
        }
    }
}

template <class DT>
void List<DT>::remove()
{
    if (!isEmpty())
    {
        ListNode<DT>* temp = cursor;       
        if (cursor == head)     // List�� ù�� ° Node�� ��
        {
            head = cursor->next;
            gotoBeginning();
        }
        else
        {
            cursor->prior->next = cursor->next;            
            if (cursor->next == NULL)       // List�� ������ Node�� ��
                gotoPrior();        // ADT������ �� ó�� Node�� �̵��϶�� ������
                //gotoBeginning()   // eclass�� test case������ �ٷ� ���� Node�� cursor�� �̵��Ͽ� �̿� ����
            else
            {
                cursor->next->prior = cursor->prior;
                gotoNext();
            }
        }
        delete temp;
    }
}

template <class DT>
void List<DT>::replace(const DT& newDataItem)
{
    if (!isEmpty())
    {
        cursor->dataItem = newDataItem;
    }
}

template <class DT>
void List<DT>::clear()
{
    gotoBeginning();
    while (head != NULL)
        remove();
}


template <class DT>
bool List<DT>::isEmpty() const
{
    if (head == NULL)
        return true;
    return false;
}

template <class DT>
bool List<DT>::isFull() const
{
    ListNode<DT>* _ = new ListNode<DT>(NULL, NULL, NULL);
    if (_ == NULL) // Node�� ���̻� �������� ������ memory�� ���� ��
        return true;
    return false;
}

template <class DT>
void List<DT>::gotoBeginning()
{
    if(!isEmpty())
        cursor = head;
}

template <class DT>
void List<DT>::gotoEnd()
{
    if (!isEmpty())
    {
        while (cursor->next != NULL)
            gotoNext();
    }
}

template <class DT>
bool List<DT>::gotoNext()
{
    if (!isEmpty() && (cursor->next != NULL))
    {
        cursor = cursor->next;
        return true;
    }
    return false;        
}

template <class DT>
bool List<DT>::gotoPrior()
{
    if (!isEmpty() && (cursor != head))
    {
        cursor = cursor->prior;
        return true;
    }
    return false;        
}

template <class DT>
DT List<DT>::getCursor() const
{
    return cursor->dataItem;
}

template < class DT>
void List<DT>::showStructure() const

// Outputs the data elements in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    ListNode<DT>* p;   // Iterates through the list

    if (head == 0)
        cout << "Empty list" << endl;
    else
    {
        p = head;
        while (p != NULL)
        {
            if (p == cursor)
                cout << "[" << p->dataItem << "] ";
            else
                cout << p->dataItem << " ";
            p = p->next;
        }
        cout << endl;
    }
}

// cursor�� ����Ű�� ���� ��ȭ�� ������ϴ���, cursor�� ����Ű�� �ּҰ� ��ȭ�� ����� �ϴ���
// �� �� ���� cursor ���� ��ȭ�� ���� ����.
template <class DT>
void List<DT>::reverse()   
{
    ListNode<DT>* p = head;
    ListNode<DT>* q = cursor;
    while (q->next != NULL)
        q = q->next;
    
    while (p != q)
    {
        DT temp = p->dataItem;
        p->dataItem = q->dataItem;
        q->dataItem = temp;
        p = p->next;
        q = q->prior;
    }
}