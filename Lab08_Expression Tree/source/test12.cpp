//--------------------------------------------------------------------
//
//  Laboratory 12                                         test12.cpp
//
//  Test program for the operations in the Expression Tree ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <new>
#include "exprtree.h"

using namespace std;

void main()
{
    ExprTree testExpression;  // Test expression

    while (true) {
        cout << endl << "Enter an expression in prefix form : ";

        testExpression.build();
        testExpression.showStructure();
        testExpression.expression();
        cout << " = " << testExpression.evaluate() << endl;

        // Test the commute operation.  (In-lab Exercise 3)
        testExpression.commute();
        cout << endl << "Fully commuted tree: " << endl;
        testExpression.showStructure();
        testExpression.expression();
        cout << " = " << testExpression.evaluate() << endl;

        cout << endl << "Clear the tree" << endl;
        testExpression.clear();
        testExpression.showStructure();
    }
}