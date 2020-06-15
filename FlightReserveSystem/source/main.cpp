#include "flight.h"
#include "useful.h"


using namespace std;

int main(void)
{
	ReservationSystem f;
	string temp[100]; 
	vector<string> x;
	cout << ".txt를 제외한 파일명을 입력하시오. " << endl;
	string* order = fileIn(temp);
	ofstream out = fileOut();
	cout << endl << "----------Action List---------" << endl;
	update(f, x, order, out);
	cout << endl << "-------Upload Successful------" << endl;
	out.close();
	system("pause");
}