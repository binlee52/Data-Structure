#ifndef __USEFULFUNCTION_H__
#define __USEFULFUNCTION_H__

#include <string>

using namespace std;

// address structure that will be used as template  

enum Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
};

string monthToString(int m);
int stringToMonth(string str);
void print_help();

#endif // !__USEFULFUNCTION_H__
