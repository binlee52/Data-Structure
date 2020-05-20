#include <algorithm>
#include "OrganizationTree.h"
#include "useful.h"

OrganizationTreeNode::OrganizationTreeNode(const string& rootData,
    OrganizationTreeNode* leftPtr, OrganizationTreeNode* rightPtr)
    : dataItem(rootData), left(leftPtr), right(rightPtr)
{}

OrganizationTree::OrganizationTree()
    : root(NULL)
{}

OrganizationTree::~OrganizationTree()
{
    clear();
}

void OrganizationTree::insert(const string& newDataitem)
{
    if (isEmpty())
        insertSub(root, newDataitem);
    else
        cout << "Fail to Insert!" << endl;
}

void OrganizationTree::insert(const string& searchData, const string& newDataItem)
{
    OrganizationTreeNode* searchNode = new OrganizationTreeNode("", NULL, NULL);
    if (isFull())
        cout << "Full Memory!" << endl;
    else if (retrieve(searchData, searchNode))    // search data and insert
        insertSub(searchNode->left, newDataItem);
    else // if searchData is not in Tree
    {
        delete searchNode;
        cout << searchData << " is not in Organization Tree." << endl;
    }
}

void OrganizationTree::insertSub(OrganizationTreeNode*& p, const string& newDataItem)
{
    if (p == NULL)      // base case
        p = new OrganizationTreeNode(newDataItem, NULL, NULL);
    else                // general case
        insertSub(p->right, newDataItem);
}

bool OrganizationTree::retrieve(const string& searchData, OrganizationTreeNode*& found) const
{
    if (isEmpty())      // if empty
        return false;
    else
    {
        retrieveSub(root, searchData, found);   // search data while traveling all nodes in tree
        if (found->dataItem == searchData)      // if searchData is in tree
            return true;
        else                                    // if searchData is not in tree
            return false;
    }
        
}

void OrganizationTree::retrieveSub(OrganizationTreeNode* p, const string& searchData,
    OrganizationTreeNode*& found) const
{
    if (p != NULL)
    {
        if (p->dataItem == searchData)
            found = p;
        retrieveSub(p->left, searchData, found);    // search from child recursively
        retrieveSub(p->right, searchData, found);   // search from sibling recursively
    }
}

bool OrganizationTree::remove(const string& deleteData)
{
    if (isEmpty())      // if tree is empty
    {
        cout << "Empty Tree" << endl;
        return false;
    }
    else    // if tree is not empty
    {
        bool found = false;     // check deleteData is in tree
        removeSub(root, deleteData, found);     // try to delete item while traveling all nodes in tree
        return found;
    }
}

void OrganizationTree::removeSub(OrganizationTreeNode*& p, const string& deleteData, bool& found)
{
    if (p == NULL)
        return;
    else if (p->dataItem == deleteData) // delete item
    {
        found = true;
        removeNode(p); // 우선순위가 가장 높은 Node로 삭제되는 Node를 대체
    }
    else
    {
        removeSub(p->left, deleteData, found);
        removeSub(p->right, deleteData, found);
    }
}

void OrganizationTree::removeNode(OrganizationTreeNode*& p)
{
    OrganizationTreeNode* temp = p;
    if (p->left == NULL)    // if no child
    {
        p = p->right;
        delete temp;
    }
    else
    {
        string item = p->left->dataItem;    
        p->dataItem = item;                 // 우선 순위가 가장 높은 node 승진
        bool found = false;
        removeSub(p->left, item, found);    // recursively delete
    }
}

void OrganizationTree::clear()
{
    if (!isEmpty())
    {
        clearSub(root);
        root = NULL;
    }
}

void OrganizationTree::clearSub(OrganizationTreeNode* p)
{
    /**delete all node while use post order traveling**/
    if (p->left != NULL)
        clearSub(p->left);
    if (p->right != NULL)
        clearSub(p->right);
    delete p;
}

void OrganizationTree::show() const
{
    if (!isEmpty())
    {
        cout << endl;
        int cnt = 0;
        showSub(root, cnt);
        cout << "-------------------------------" << endl;
    }
    else
        cout << "Empty Tree" << endl;
}

void OrganizationTree::showSub(OrganizationTreeNode* p, int count) const
{
    if (p != NULL)
    {
        for (int i = 0; i < count; i++)
            cout << '+';
        cout << p->dataItem << endl;
        showSub(p->left, count + 1);
        showSub(p->right, count);
    }
}

bool OrganizationTree::isEmpty() const
{
    return root == NULL;
}

bool OrganizationTree::isFull() const
{
    OrganizationTreeNode* temp = new OrganizationTreeNode("", NULL, NULL);
    if (temp != NULL)
    {
        delete temp;
        return false;
    }
    return true;
}

void printHelp()
{
    cout << "The first line of the input contains only the name of the person who is initially the CEO." << endl;
    cout << "The first line will be followed by one or more additional lines" << endl;
    cout << "The format of each of these lines will be determined by one of the following three rules of syntax:" << endl;
    cout << "    ■ [Existing member] hires [new member]" << endl;
    cout << "    ■ Fire [existing member]" << endl;
    cout << "    ■ Print" << endl;
    cout << "    ■ Quit" << endl;
}

void runOT()
{
    OrganizationTree ot;
    string input;
    cout << endl << " >> ";
    cin >> input;
    vector<string> x;
    ot.insert(input);
    cin.ignore();
    while (true)
    {
        cout << " >> ";
        getline(cin, input);
        x = split(input, ' ');

        if (x.size() == 3)
        {
            transform(x[1].begin(), x[1].end(), x[1].begin(), ::toupper); // 대문자로 command 변환
            if (x[1] == "HIRES")
                ot.insert(x[0], x[2]);
        }
        else
        {
            transform(x[0].begin(), x[0].end(), x[0].begin(), ::toupper); // 대문자로 command 변환
            if (x.size() == 1 && x[0] == "QUIT")
                exit(1);
            else if (x.size() == 1 && x[0] == "PRINT")
                ot.show();
            else if (x.size() == 2 && x[0] == "FIRE")
                ot.remove(x[1]);
            else
                cout << "Wrong Command!" << endl;
        }
    }
}

int main(void)
{
    printHelp();
    runOT();

    return 0;
}

