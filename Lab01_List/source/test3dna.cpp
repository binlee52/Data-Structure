//--------------------------------------------------------------------
//	2020-03-19 in-lab
//  파일명: test3dna.cpp
//  작성자: 동국대학교 컴퓨터공학과 2016112122 이한빈
//--------------------------------------------------------------------

#include <iostream>
#include "listarr.h"
#include <cString>
using namespace std;

void countBases(List& dnaSequence, int& aCount, int& cCount, int& tCount, int& gCount);

int main(void)
{
	List dnaList(10);		  // Test list
	char dnaElement;         // List element
	char cmd;                 // Input command
	int aCount = 0, cCount = 0, tCount = 0, gCount = 0;

	cout << "DNA Sequence: ";

	do
	{
		cin >> cmd;
		if (cmd == '+')
			cin >> dnaElement;

		// 간결한 test 코드 작성을 위하여 + 이외의 command는 생략
		switch (cmd)
		{
		case '+':                                  // insert 
			dnaList.insert(dnaElement);
			break;
		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (!dnaList.isFull());
	cout << endl;
	countBases(dnaList, aCount = aCount, tCount = tCount, cCount = cCount, gCount = gCount);
	system("pause");
	return 0;
}


void countBases(List& dnaSequence, int& aCount, int& cCount, int& tCount, int& gCount)

// Input Parameters
// dnaSequence: contains the bases in a DNA sequence encoded using the characters A, C, T, G
// Output
//aCount, cCount, tCount, gCount: the number of times the corresponding base appears in DNA Sequence

{	
	aCount = 0, cCount = 0, tCount = 0, gCount = 0;
	dnaSequence.gotoBeginning();
	char dna;
	do {
		dna = toupper(dnaSequence.getCursor());
		if (dna == 'A')
			aCount++;
		else if (dna == 'T')
			tCount++;
		else if (dna == 'C')
			cCount++;
		else if (dna == 'G')
			gCount++;
		else
			break;
	} while (dnaSequence.gotoNext());
	cout << "result: " << endl;
	cout << "aCount=" << aCount << endl;
	cout << "cCount=" << cCount << endl;
	cout << "tCount=" << tCount << endl;
	cout << "gCount=" << gCount << endl;
}