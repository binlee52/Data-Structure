#include "usefulFunction.h"
#include "listlnk.h" // template class 는 헤더와 cpp 파일을 나누는 것을 지원하지 않음

int main(void)

{
	print_help();
	List<address> addressBook;
	char cmd;

	do
	{
		cout << endl << "Command: ";
		cin >> cmd;

		switch (cmd)
		{
		case 'R': case 'r':
			addressBook.fileIn();
			addressBook.showListInformation();
			break;
		case '+':
			addressBook.add();
			addressBook.showListInformation();
			break;
		case '-':
			addressBook.remove();
			addressBook.showListInformation();
			break;
		case 'W': case 'w':
			addressBook.fileOut();
			break;
		case 'M': case 'm':
			addressBook.showMonthInformation();
			break;
		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q' && cmd != 'q');
}