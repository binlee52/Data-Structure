#pragma once;
#include <iostream>
#include <string>

#include <fstream>
#include <sstream>

using namespace std;

class Passenger;
class ReservePassenger;
class ReservePassengerList;
class StandByPassenger;
class ReservationSystem;
class CustomerList;
class Customer;

class Flight
{
private:
	int flight_number;	// ����� ��ȣ(4�ڸ��� ����)
	string from_city;	// ����� �����
	string to_city;		// ����� ������
	int capacity;		// �ִ� ž�� ����
	int passenger;		// ���� �� ��
	int standby;		// ��� �� ��
	bool full;			// ����Ⱑ ��á���� ����
	bool flag;			// Customer ��ü���� ����⿡ ���������� �����ߴ��� Ȯ���� �� flag 

	Flight* prev_flight;		// ���� ����� link
	Flight* next_flight;		// ���� ����� link

	ReservePassenger * reserve_list;	// ���� �� list
	StandByPassenger * standby_list;	// ��� �� list. ->head, ->tail�� front, rear�� ���� ����
public:
	Flight();
	Flight(int _flight_number, string _from_city, string _to_city, int _capacity);
	//~Flight();
	// �ο� ����, ���Ҵ� Flight Ŭ�������� �̷����.
	bool is_full();		// ������ �� á���� Ȯ��
	void reserve_flight(string _name, Flight* this_flight); // ����. reserve �ο� �߰�
	void stand_flight(string _name); // ���. standby �ο� �߰�
	string pop_standby(); // standby.pop() standby �ο� ����.
	void show_name(ofstream& out); // ���Ͽ� ��� ���
	void show_info(ofstream& out); // ���Ͽ� ��� ���
	friend class ReservationSystem;
	friend class Customer;
	friend class ReservePassenger;
};

class ReservationSystem
{
private:
	// ReservationSystem
	Flight* head_flight;	// dummy node
	Flight* tail_flight;	// dummy node

	// CustomerList
	Customer* head_customer; // dummy node
	Customer* tail_customer; // dummy node

	int flight_cnt; // ��ü ����� ��
	int customer_cnt; // ��ü �� ��

	void connect_link(Flight* prev, Flight* next);
	void connect_link(Flight* prev, Flight* curr, Flight* next);
	void connect_link(Passenger* prev, Passenger* next);
	void connect_link(Customer* prev, Customer* next);
	void connect_link(Customer* prev, Customer* curr, Customer* next);
public:
	ReservationSystem();
	~ReservationSystem();
	void insert_flight(int _flight_number, string _from_city, string _to_city, int _capacity); // ����� �߰�
	void delete_flight(int _flight_number); // ����� ����
	bool is_empty(); // ����Ⱑ ����ִ��� Ȯ��
	bool is_full(); // ����Ⱑ �� á���� Ȯ��
	bool is_empty_cumstomer(); // ���� �ִ��� Ȯ��
	void linkPasCus(Flight* _flight, string _name); // Passnger�� Customer ����
	void add_customer(string _name, Flight* _flight); // ���� �� �߰�
	void standby_customer(string _name, Flight* _flight); // ��� �� �߰�
	void reserve(string _name, int _flight_number); // ����
	void cancle(string _name, int _flight_number); // ���� ���
	void cancle_reserve(string _name, int _flight_number); // Ư�� ������� ���� ���
	void cancle_standby(string _name, int _flight_number); // Ư�� ������� ��� ���
	void cancle_all_reserve(string _name); // ��� ���� �� ��� ���
	void delete_flight_in_reserve(Customer* customerLink, int _flight_number); // �� ��忡�� ����� �� ����(reserve)
	void delete_flight_in_standby(Customer* customerLink, int _flight_number); // �� ��忡�� ����� �� ����(standby)
	void showAllFlightNumber(string c, ofstream& out); // ���Ͽ� ���
	void showAllCustomerInfo(ofstream& out); // ���Ͽ� ���
	void ShowCustomerInfo(string _name, ofstream& out); // ���Ͽ� ���
	void showFlightInfo(string s, int _flight_number, ofstream& out); // ���Ͽ� ���
};

class Passenger
{
private:
	string name; // �̸�

	Passenger* prev_passenger; // ���� ������� ���� ž�°�
	Passenger* next_passenger; // ���� ������� ���� ž�°�
	bool flag; // ���� ���� ����
	Flight* this_flight; // ������ ������� ������
	Customer* cus; // �� ��忡 ���� ������
public:
	Passenger(string _name);

	friend class ReservePassenger;
	friend class StandByPassenger;
	friend class Flight;
	friend class ReservationSystem;
};

class Customer
{
private:
	string name;  // �̸�

	Customer* prev_customer; // ���� ���� ���� ������
	Customer* next_customer; // ���� ���� ���� ������
	Flight* reserve_flight_head; // ������ flight list head
	Flight* reserve_flight_tail; // ������ flight list tail
	Flight* standby_flight_head; // ��� �� flight list head
	Flight* standby_flight_tail; // ��� �� flight list tail
	bool flag; // ����� ���� ����
public:
	Customer(string _name);
	void add_flight(Flight* _flight); // ���� ����� �߰�
	void add_standby_flight(Flight* _flight); // ��� ����� �߰�
	bool is_reserve(); // ���������� true, ���� �� ������ false
	bool is_standby(); // ��� ������ true, ��� ������ false
	void connect_link(Flight* prev, Flight* next);
	void connect_link(Flight* prev, Flight* curr, Flight* next);
	friend class ReservationSystem;
	friend class ReservePassenger;
};

class ReservePassenger
{
private:
	Passenger* head; // dummy node
	Passenger* tail; // dummy node
public:
	ReservePassenger();
	void add(string _name, Flight* this_flight); // ���� �� ����Ʈ�� ���ڷ� ���� �̸���� Passenger ��ü�� ������ �� �߰�
	void connect_link(Passenger* prev, Passenger* next);
	void connect_link(Passenger* prev, Passenger* curr, Passenger* next);
	bool is_empty(); // ���������Ʈ�� ����ִ��� Ȯ��
	friend class Flight;
	friend class ReservationSystem;
};

class StandByPassenger // �켱���� ť�� ����
{
private:
	Passenger* head;
	Passenger* tail;
public:
	StandByPassenger();
	void enque(string _name);
	string deque(); // ����ο� deque. standby �ο� ���� ����.
	void connect_link(Passenger* prev, Passenger* next);
	void connect_link(Passenger* prev, Passenger* curr, Passenger* next);
	bool is_full(); // ��������Ʈ�� ����ִ��� Ȯ��
	bool is_empty(); // ��������Ʈ�� �� á���� Ȯ��
	friend class Flight;
	friend class ReservationSystem;
};