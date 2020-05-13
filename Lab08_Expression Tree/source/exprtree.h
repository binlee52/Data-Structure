#pragma once
//--------------------------------------------------------------------
//
//  Laboratory 12                                        exprtree.hs
//
//  (Shell) Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive partners of the
//  public member functions
//
//--------------------------------------------------------------------
#include <stdexcept>
#include <iostream>

using namespace std;

class ExprTree;           // Forward declaration of the ExprTree class

class ExprTreeNode        // Facilitator class for the ExprTree class
{
  private:

    // Constructor
    ExprTreeNode ( char rootData,
                   ExprTreeNode *leftPtr, ExprTreeNode *rightPtr ) : dataItem(rootData), left(leftPtr), right(rightPtr) {}

    // Data members
    char dataItem;          // Expression tree data item
    ExprTreeNode *left,     // Pointer to the left child
                 *right;    // Pointer to the right child

  friend class ExprTree;
};

//--------------------------------------------------------------------

class ExprTree
{
  public:

    // Constructor
    ExprTree ();

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ()               // Build tree from prefix expression
        throw ( bad_alloc );
    void expression () const;   // Output expression in infix form
    float evaluate () const     // Evaluate expression
        throw ( logic_error );
    void clear ();              // Clear tree
    bool is_cal() const;        // check calculatable

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

    // In-lab operations
    void commute ();                          // Commute all subexpr.

  private:
    // Recursive partners of the public member functions -- insert
    // prototypes of these functions here.

    // Data member
    ExprTreeNode *root;   // Pointer to the root node

    void buildSub(ExprTreeNode*& ptr, char*& szExpr);
    void expressionSub(ExprTreeNode* ptr) const;
    void clearSub(ExprTreeNode*& ptr);
    void showSub(ExprTreeNode* p, int level) const;
    float evaluateSub(ExprTreeNode* ptr) const;
    bool is_operator(ExprTreeNode* ptr) const;  // check operator
    bool is_calSub(ExprTreeNode* ptr) const;
    bool is_empty() const;  // cheack is tree empty
    void commuteSub(ExprTreeNode*& ptr);
};
