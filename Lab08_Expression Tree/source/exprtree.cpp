#include "exprtree.h"

ExprTree::ExprTree()
/** Constructor **/
	: root(NULL)
{}

ExprTree::~ExprTree()
/** Destructor **/
{
	clear();
}

void ExprTree::build()
/** Build tree from prefix expression **/
{
	// user input
	char* prefix = new char[20];
	cin >> prefix;
	buildSub(root, prefix);		// call recursive function
	while (!is_cal())		// if can't calculate prefix expression, get prefix expression from user again	
	{
		cout << "CAN'T CALCULATE!" << endl;
		clear();	// clear the tree made before
		cout << endl << "Enter an expression in prefix form : ";
		cin >> prefix;
		buildSub(root, prefix);		// call recursive function
	}
}

void ExprTree::buildSub(ExprTreeNode*& ptr, char*& szExpr)
/** Build tree from prefix expression recursively **/
{
	ExprTreeNode* t;
	while (*szExpr)
	{
		t = new ExprTreeNode(*szExpr, NULL, NULL);		// create new Tree Node
		ptr = t;		// set ptr as new Tree Node
		if (is_operator(ptr))	// if operator, it needs child nodes
		{
			buildSub(ptr->left, ++szExpr);		// left child
			buildSub(ptr->right, ++szExpr);		// right child
			return;
		}
		else    // if operand, it doesn't need child node
			return;
	}
}

void ExprTree::expression() const
/** Output expression in infix form **/
{
	expressionSub(root);	// call recursive function
}

void ExprTree::expressionSub(ExprTreeNode* ptr) const
/** Output expression in infix form recursively **/
{
	if (ptr != NULL && is_operator(ptr))
	{
		cout << '(';
		expressionSub(ptr->left);
		cout << ptr->dataItem;
		expressionSub(ptr->right);
		cout << ')';
	}
	else if (ptr != NULL && !is_operator(ptr))	// if operand, it doesn't need '(' or ')'
		cout << ptr->dataItem;
}

void ExprTree::clear()
/** Clear tree **/
{
	clearSub(root);		// clear tree recursively
	root = NULL;		// set root as NULL to make Tree empty cirtainly
}

void ExprTree::clearSub(ExprTreeNode*& ptr)
/** Clear the tree recursively **/
{
	if (ptr != NULL)
	{
		clearSub(ptr->left);	// clear left sub tree
		clearSub(ptr->right);	// clear right sub tree
		delete ptr;		// delete present Node
	}
}

bool ExprTree::is_operator(ExprTreeNode* ptr) const
/** check operator **/
{
	if ((ptr->dataItem == '+') || (ptr->dataItem == '-') || ptr->dataItem == '*' || ptr->dataItem == '/')
		return true;	// operator
	return false;	// operand
}

float ExprTree::evaluate() const
/** Evaluate expression **/
{
	return evaluateSub(root);	// evaluate expression recursively
}

float ExprTree::evaluateSub(ExprTreeNode* ptr) const
/** Evaluate expression recursively **/
{
	if (is_operator(ptr))	// operator
	{
		switch (ptr->dataItem)	// calculate
		{
		case '+':
			return evaluateSub(ptr->left) + evaluateSub(ptr->right);
		case '-':
			return evaluateSub(ptr->left) - evaluateSub(ptr->right);
		case '*':
			return evaluateSub(ptr->left) * evaluateSub(ptr->right);
		case '/':	
			return evaluateSub(ptr->left) / evaluateSub(ptr->right);
		}
	}
	else    // return operand as integer type
		return int(ptr->dataItem - '0');
}

bool ExprTree::is_cal() const
/** Check Calculatable **/
{
	return is_calSub(root);	// check calculatable recursively
}

bool ExprTree::is_calSub(ExprTreeNode* ptr) const
/** Check calculatable recursively **/
{
	if (ptr != NULL)
	{
		if (is_operator(ptr))		// operator는 2개의 child node를 반드시 갖고 있어야 함
		{
			if (ptr->left == NULL || ptr->right == NULL) // operator가 0, 1개의 child node를 갖는 경우
				return false;
			else // operator가 2개의 child node가 있을 경우
			{
				return is_calSub(ptr->left) && is_calSub(ptr->right);
			}
		}
		else    // operand는 leaf
			return true;
	}
}

void ExprTree::commute()
/** Commute all subexpr **/
{
	if (!is_empty())
		commuteSub(root);	// commute all tree node recursively
}

void ExprTree::commuteSub(ExprTreeNode*& ptr)
/** commute all tree node recursively **/
{
	if (ptr != NULL)
	{
		// left sub tree와 right sub tree를 변경
		ExprTreeNode* temp = ptr->right;
		ptr->right = ptr->left;
		ptr->left = temp;

		commuteSub(ptr->left);
		commuteSub(ptr->right);
	}
}

bool ExprTree::is_empty() const
/** check is tree empty **/
{
	return root == NULL;
}