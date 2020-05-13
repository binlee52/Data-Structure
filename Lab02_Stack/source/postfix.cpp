//--------------------------------------------------------------------
//
//  Laboratory 5                                           test5.cpp
//
//  Test program for the operations in the Stack ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include "stackarr.cpp"
using namespace std;

//--------------------------------------------------------------------

int main(void)
{
	Stack<float> testStack(10);
	char cmd;                     // Input command
	float x, y;
	cout << "Postfix expression: ";
	do
	{
		cmd = cin.get();	// 개행문자 \n을 입력받기 위해
		if ('0' <= cmd && cmd <= '9')	// 숫자를 입력받은 경우
		{
			testStack.push(cmd - 48);
		}
		else
		{
			switch (cmd)
			{
			case '+':						// add 
				y = testStack.pop();
				x = testStack.pop();
				testStack.push(x+y);
				break;
			case '-':                       // min          
				y = testStack.pop();
				x = testStack.pop();
				testStack.push(x-y);
				break;
			case '*':                       // mul
				y = testStack.pop();
				x = testStack.pop();
				testStack.push(x*y);
				break;
			case '/':						// div
				y = testStack.pop();
				x = testStack.pop();
				testStack.push(x/y);
				break; case 'C': case 'c':                // clear
					cout << "Clear the stack" << endl;
					testStack.clear();
					break;

				case 'E': case 'e':                       // empty
					if (testStack.empty())
						cout << "Stack is empty" << endl;
					else
						cout << "Stack is NOT empty" << endl;
					break;

				case 'F': case 'f':                       // full
					if (testStack.full())
						cout << "Stack is full" << endl;
					else
						cout << "Stack is NOT full" << endl;
					break;

				case 'Q': case 'q':                   // Quit test program
					break;
				case '\n':	// 개행문자가 나오면 결과 출력
					cout << "Result: ";
					testStack.showStructure();
					testStack.clear();	// stack 초기화
					cout << endl << "Postfix Expression: ";
					break;

				default:                               // Invalid command
					cout << "Inactive or invalid command" << endl;
			}
		}		
	} while (1);
	return 0;
}
