#include "usefulFunction.h"
#include <iostream>
#include <algorithm> // transform
#include <cctype> // toupper

// int로 입력받은 월을 string type으로 만들어서 반환
string monthToString(int m)
{
	string s;
	switch (m)
	{
	case 1:
		s = "January";
		break;
	case 2:
		s = "February";
		break;
	case 3:
		s = "March";
		break;
	case 4:
		s = "April";
		break;
	case 5:
		s = "May";
		break;
	case 6:
		s = "June";
		break;
	case 7:
		s = "July";
		break;
	case 8:
		s = "August";
		break;
	case 9:
		s = "September";
		break;
	case 10:
		s = "October";
		break;
	case 11:
		s = "November";
		break;
	case 12:
		s = "December";
		break;
	default:
		cout << "Unknown Value" << endl;
		break;
	}
	return s;
}


// string으로 입력받은 '월'을 숫자로 반환
int stringToMonth(string str)
{	
	transform(str.begin(), str.end(), str.begin(), toupper);
	if (str == "JANUARY")
		return 1;
	else if (str == "FEBRUARY")
		return 2;
	else if (str == "MARCH")
		return 3;
	else if (str == "APRIL")
		return 4;
	else if (str == "MAY")
		return 5;
	else if (str == "JUNE")
		return 6;
	else if (str == "JULY")
		return 7;
	else if (str == "AUGHUST")
		return 8;
	else if (str == "SEPTEMBER")
		return 9;
	else if (str == "OCTOBER")
		return 10;
	else if (str == "NOVEMBER")
		return 11;
	else if (str == "DECEMBER")
		return 12;
	else
	{
		return 0;
	}
}

// Command
void print_help()
{
	cout << "Commands:" << endl;
	cout << "   R: read from a file" << endl;
	cout << "   +:  add a new entry" << endl;
	cout << "   -:   remove an entry" << endl;
	cout << "   W: write to a file" << endl;
	cout << "   M: select a month" << endl;
	cout << "   Q   : Quit the test program" << endl;
	cout << endl;
}