#pragma once
//--------------------------------------------------------------------
//
//  Laboratory 11                                          bstree.hs
//
//  (Shell) Class declarations for the linked implementation of the
//  Binary Search Tree ADT -- including the recursive partners of
//  the public member functions
//
//--------------------------------------------------------------------

#include <iostream>

using namespace std;

template < class DT, class KF >   // Forward dec. of the BSTree class
class BSTree;

template < class DT, class KF >
class BSTreeNode                  // Facilitator for the BSTree class
{
  private:

    // Constructor
    BSTreeNode ( const DT &rootData,
                 BSTreeNode *leftPtr, BSTreeNode *rightPtr );

    // Data members
    DT dataItem;         // Binary search tree data item
    BSTreeNode *left,    // Pointer to the left child
               *right;   // Pointer to the right child

  friend class BSTree<DT,KF>;
};

//--------------------------------------------------------------------

template < class DT, class KF >    // DT : tree data item
class BSTree                       // KF : key field
{
  public:

    // Constructor
    BSTree ();

    // Destructor
    ~BSTree ();

    // Binary search tree manipulation operations
    void insert ( const DT &newDataItem )         // Insert data item
        throw ( bad_alloc );
    bool retrieve ( KF searchKey, DT &searchData ) const;
                                                  // Retrieve data item
    bool remove ( KF deleteKey );                  // Remove data item
    void writeKeys () const;                      // Output keys
    void clear ();                                // Clear tree

    // Binary search tree status operations
    bool isEmpty () const;                           // Tree is empty
    bool isFull () const;                            // Tree is full

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

  private:

    // Recursive partners of the public member functions -- insert
    // prototypes of these functions here.
    void showSub ( BSTreeNode<DT,KF> *p, int level ) const;
    void insertSub(BSTreeNode<DT, KF>*& p, const DT& newDataItem);
    bool retrieveSub(BSTreeNode<DT, KF>* p, KF searchKey, DT& searchData) const;
    bool removeSub(BSTreeNode<DT, KF>*& p, KF deleteKey);
    void removeNode(BSTreeNode<DT, KF>*& p);
    void getPredecessor(BSTreeNode<DT, KF>* p, DT& item);
    void clearSub(BSTreeNode<DT, KF>* p);
    void writeKeysSub(BSTreeNode<DT, KF>* p) const;
    // Data member
    BSTreeNode<DT,KF> *root;   // Pointer to the root node
};
