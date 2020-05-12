#include "bstree.h"

template < class DT, class KF >
BSTreeNode<DT, KF>::BSTreeNode(const DT& rootData,
    BSTreeNode* leftPtr, BSTreeNode* rightPtr)
    : dataItem(rootData), left(leftPtr), right(rightPtr)
{}

template <class DT, class KF>
BSTree<DT, KF>::BSTree()
    : root(NULL)
{}

template <class DT, class KF>
BSTree<DT, KF>::~BSTree()
{
    clear();
}

template <class DT, class KF>
void BSTree<DT, KF>::insert(const DT& newDataItem) throw (bad_alloc)
{
    if (isFull())
        cout << "Full Memory!" << endl;
    else
        insertSub(root, newDataItem);
}

template <class DT, class KF>
void BSTree<DT, KF>::insertSub(BSTreeNode<DT, KF>*& p, const DT& newDataItem)
{
    if (p == NULL)
        p = new BSTreeNode<DT, KF>(newDataItem, NULL, NULL);
    else if ((p->dataItem).key() > newDataItem.key())      // Node의 값이 새로운 item의 값보다 클 때 
        insertSub(p->left, newDataItem);     
    else if ((p->dataItem).key() < newDataItem.key())      // Node의 값이 새로운 item의 값보다 작을 때
        insertSub(p->right, newDataItem);
    else        // Node의 값이 새로운 item의 값과 같을 때
        p->dataItem = newDataItem;
}

template <class DT, class KF>
bool BSTree<DT, KF>::retrieve(KF searchKey, DT& searchData) const
{
    if (isEmpty())
        return false;
    else
        return retrieveSub(root, searchKey, searchData);
}

template <class DT, class KF>
bool BSTree<DT, KF>::retrieveSub(BSTreeNode<DT, KF>* p, KF searchKey, DT& searchData) const
{
    if (p == NULL)
        return false;
    else if ((p->dataItem).key() > searchKey)      // Node의 값이 key 값보다 값보다 클 때 
        retrieveSub(p->left, searchKey, searchData);
    else if ((p->dataItem).key() < searchKey)      // Node의 값이 key 값보다 작을 때
        retrieveSub(p->right, searchKey, searchData);
    else        // Node의 값이 key 값과 같을 때
    {
        searchData = p->dataItem;
        return true;
    }
}

template <class DT, class KF>
bool BSTree<DT, KF>::remove(KF deleteKey)
{
    if (isEmpty())
    {
        cout << "Empty Tree" << endl;
        return false;
    }
    else
        return removeSub(root, deleteKey);
}

template <class DT, class KF>
bool BSTree<DT, KF>::removeSub(BSTreeNode<DT, KF>*& p, KF deleteKey)
{
    if (p == NULL)
        return false;
    else if ((p->dataItem).key() > deleteKey)        // 현재 Node의 key가 삭제할 노드의 key보다 클 때
        return removeSub(p->left, deleteKey);
    else if ((p->dataItem).key() < deleteKey)       // 현재 Node의 key가 삭제할 노드의 key보다 작을 때
        return removeSub(p->right, deleteKey);
    else
    {
        removeNode(p);
        return true;
    }
}


template <class DT, class KF>
void BSTree<DT, KF>::removeNode(BSTreeNode<DT, KF>*& p)
{
    BSTreeNode<DT, KF>* tempNode = p;
    if (p->left == NULL)        // 왼쪽 child가 없을 시 or child가 없을 시
    {
        p = p->right;
        delete tempNode;
    }
    else if (p->right == NULL)      // 오른쪽 child가 없을 시
    {
        p = p->left;
        delete tempNode;
    }
    else        // 양 쪽 child가 모두 존재 할 시
    {
        DT item;
        getPredecessor(p, item);        // 왼쪽 SubTree에서 가장 큰 값을 item에 저장
        p->dataItem = item;             // dataItem의 item을 predecessor로 수정
        removeSub(p->left, item.key());       // 왼쪽 SubTree에서 item 삭제
    }
}

template <class DT, class KF>
void BSTree<DT, KF>::getPredecessor(BSTreeNode<DT, KF>* p, DT& item)
{
    while (p->right != NULL)
        p = p->right;
    item = p->dataItem;
}

template <class DT, class KF>
void BSTree<DT, KF>::clear()
{
    if (!isEmpty())
    {
        clearSub(root);
        root = NULL;
    }
}

template <class DT, class KF>
void BSTree<DT, KF>::clearSub(BSTreeNode<DT, KF>* p)
{
    if (p->left != NULL)
        clearSub(p->left);
    if (p->right != NULL)
        clearSub(p->right);
    delete p;
}

template <class DT, class KF>
void BSTree<DT, KF>::writeKeys() const
{
    if (isEmpty())
        cout << "Empty Tree" << endl;
    else
    {
        writeKeysSub(root);
        cout << endl;
    }
}

template <class DT, class KF>
void BSTree<DT, KF>::writeKeysSub(BSTreeNode<DT, KF>* p) const
{
    if (p != NULL)
    {
        writeKeysSub(p->left);
        cout << (p->dataItem).key() << " ";
        writeKeysSub(p->right);
    }
}

template <class DT, class KF>
bool BSTree<DT, KF>::isEmpty() const
{
    return root == NULL;
}

template <class DT, class KF>
bool BSTree<DT, KF>::isFull() const
{
    BSTree<DT, KF>* temp = new BSTree();
    if (temp != NULL)
    {
        delete temp;
        return false;
    }
    return true;
}