#pragma once
#include <iostream>
#include <string>

using namespace std;

class OrganizationTree;

class OrganizationTreeNode
{
private:
	// Constructor
	OrganizationTreeNode(const string& rootData,
		OrganizationTreeNode* leftPtr, OrganizationTreeNode* rightPtr);

	// Data members
	string dataItem;
	OrganizationTreeNode* left;
	OrganizationTreeNode* right;

	friend class OrganizationTree;
};


class OrganizationTree
{
private:
	// data member
	OrganizationTreeNode* root;		// Pointer to the root Node
	
	// sub member function
	void insertSub(OrganizationTreeNode*& p, const string& newDataItem);
	void retrieveSub(OrganizationTreeNode* p, const string& searchData, 
		OrganizationTreeNode*& found) const;
	void removeSub(OrganizationTreeNode*& p, const string& deleteData, bool& found);
	void removeNode(OrganizationTreeNode*& p);
	void clearSub(OrganizationTreeNode* p);
	void showSub(OrganizationTreeNode* p, int count) const;

public:

	// Constructor
	OrganizationTree();

	// Destructor
	~OrganizationTree();

	// Organiazation Tree manipulation operations
	void insert(const string& newDataItem);		// insert if empty
	void insert(const string& searchData, const string& newDataItem);		// Insert data item
	bool retrieve(const string& searchData, OrganizationTreeNode*& found) const;		// Retrieve data Item
	bool remove(const string& deleteData);		// Remove data item
	void clear();
	void show() const;

	bool isEmpty() const;	// is tree empty
	bool isFull() const;	// is tree full?
};