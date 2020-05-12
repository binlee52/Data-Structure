//--------------------------------------------------------------------
//
//  Laboratory 11                                         show11.cpp
//
//  Linked implementation of the showStructure operation for the
//  Binary Search Tree ADT
//
//--------------------------------------------------------------------

#include "bstree.h"

template < class DT, class KF >
void BSTree<DT,KF>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showSub(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT, class KF >
void BSTree<DT,KF>:: showSub ( BSTreeNode<DT,KF> *p,
                               int level             ) const

// Recursive partner of the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showSub(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.key();  // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showSub(p->left,level+1);          // Output left subtree
    }
}
