#pragma once
#include "flight.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

/**
Function: split<Out>
Parameter: const string&, char, Out
Return: None

Description: string을 분할
**/
template <typename Out>
void split(const string& s, char delim, Out result)
{
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
		*(result++) = item;
}

/**
Function: split<Out>
Parameter: const string&, char, Out
Return: None

Description: string을 분할
**/
vector<string> split(const string& s, const char delim)
{
	vector<string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}

/**
Function: fileIn
Parameter: string []
Return: string*

Description: user에게 txt 파일을 입력 받아 프로그램에서 file open 한다.
이후 입력 받은 문자열을 string 배열로 반환한다.
**/
string* fileIn(string temp[])
{
	cout << "Enter the name of the Input file: ";
	string path;
	getline(cin, path);
	path = path + ".txt";

	// file open
	ifstream fin(path.data());
	while (!fin.is_open())
	{
		cout << "Fail to Open Input file." << endl;
		cout << "Enter the name of the Input file, again! >> ";
		getline(cin, path);
		path = path + ".txt";
		fin.open(path);
	}

	// 파일이 성공적으로 열렸을시
	if (fin.is_open())
	{
		string line;
		int index = 0;
		while (getline(fin, line))
		{
			temp[index] = line;
			index++;
		}
		fin.close();
	}
	else
		cout << "Fail to open Input file." << endl;
	return temp;
}


/**
Function: update
Parameter: ReservationSystem&, vecotr<string>, string*, ofstream&
Return: None

Description: 파일 입력을 통해 입력 받은 문장을 반복하여 비행기예약시스템을 진행한다.
**/
void update(ReservationSystem& f, vector<string> x, string* order, ofstream& out)
{
	for (int i = 0; i < order->length(); i++)
	{
		if (order[i] == "")
			break;
		x = split(order[i], ' ');
		std::transform(x[0].begin(), x[0].end(), x[0].begin(), ::toupper);
		if (x[0] == "IF")
			f.insert_flight(atoi(x[1].c_str()), x[2], x[3], atoi(x[4].c_str()));
		else if (x[0] == "PA")
			f.showAllFlightNumber(x[0], out);
		else if (x[0] == "RP")
			f.reserve(x[1], atoi(x[2].c_str()));
		else if (x[0] == "PF")
			f.showAllFlightNumber(x[0], out);
		else if (x[0] == "PR")
			f.showFlightInfo(x[0], atoi(x[1].c_str()), out);
		else if (x[0] == "PP")
			f.ShowCustomerInfo(x[1], out);
		else if (x[0] == "CP")
			f.cancle(x[1], atoi(x[2].c_str()));
		else if (x[0] == "DF")
			f.delete_flight(atoi(x[1].c_str()));
	}
}

/**
Function: fileOut
Parameter: None
Return: None

Description: 파일을 출력하기 위한 경로를 입력 받는다.
**/
ofstream fileOut()
{
	cout << "Enter the name of the Output file: ";
	string path;
	getline(cin, path);
	path = path + ".txt";
	ofstream out(path);
	while (!out.is_open())
	{
		cout << "Fail to Open Output file." << endl;
		cout << "Enter the name of the Output file, again! >> ";
		getline(cin, path);
		path = path + ".txt";
		out.open(path);
	}
	return out;
}