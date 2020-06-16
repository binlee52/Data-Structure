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
	int flight_number;	// 비행기 번호(4자리의 숫자)
	string from_city;	// 비행기 출발지
	string to_city;		// 비행기 도착지
	int capacity;		// 최대 탑승 고객수
	int passenger;		// 예약 고객 수
	int standby;		// 대기 고객 수
	bool full;			// 비행기가 꽉찼는지 여부
	bool flag;			// Customer 객체에서 비행기에 성공적으로 예약했는지 확인할 때 flag 

	Flight* prev_flight;		// 이전 비행기 link
	Flight* next_flight;		// 다음 비행기 link

	ReservePassenger * reserve_list;	// 예약 고객 list
	StandByPassenger * standby_list;	// 대기 고객 list. ->head, ->tail로 front, rear에 접근 가능
public:
	Flight();
	Flight(int _flight_number, string _from_city, string _to_city, int _capacity);
	//~Flight();
	// 인원 증가, 감소는 Flight 클래스에서 이루어짐.
	bool is_full();		// 예약이 꽉 찼는지 확인
	void reserve_flight(string _name, Flight* this_flight); // 예약. reserve 인원 추가
	void stand_flight(string _name); // 대기. standby 인원 추가
	string pop_standby(); // standby.pop() standby 인원 감소.
	void show_name(ofstream& out); // 파일에 결과 출력
	void show_info(ofstream& out); // 파일에 결과 출력
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

	int flight_cnt; // 전체 비행기 수
	int customer_cnt; // 전체 고객 수

	void connect_link(Flight* prev, Flight* next);
	void connect_link(Flight* prev, Flight* curr, Flight* next);
	void connect_link(Passenger* prev, Passenger* next);
	void connect_link(Customer* prev, Customer* next);
	void connect_link(Customer* prev, Customer* curr, Customer* next);
public:
	ReservationSystem();
	~ReservationSystem();
	void insert_flight(int _flight_number, string _from_city, string _to_city, int _capacity); // 비행기 추가
	void delete_flight(int _flight_number); // 비행기 삭제
	bool is_empty(); // 비행기가 비어있는지 확인
	bool is_full(); // 비행기가 꽉 찼는지 확인
	bool is_empty_cumstomer(); // 고객이 있는지 확인
	void linkPasCus(Flight* _flight, string _name); // Passnger와 Customer 연결
	void add_customer(string _name, Flight* _flight); // 예약 고객 추가
	void standby_customer(string _name, Flight* _flight); // 대기 고객 추가
	void reserve(string _name, int _flight_number); // 예약
	void cancle(string _name, int _flight_number); // 예약 취소
	void cancle_reserve(string _name, int _flight_number); // 특정 비행기편 예약 취소
	void cancle_standby(string _name, int _flight_number); // 특정 비행기편 대기 취소
	void cancle_all_reserve(string _name); // 모든 예약 및 대기 취소
	void delete_flight_in_reserve(Customer* customerLink, int _flight_number); // 고객 노드에서 비행기 편 삭제(reserve)
	void delete_flight_in_standby(Customer* customerLink, int _flight_number); // 고객 노드에서 비행기 편 삭제(standby)
	void showAllFlightNumber(string c, ofstream& out); // 파일에 출력
	void showAllCustomerInfo(ofstream& out); // 파일에 출력
	void ShowCustomerInfo(string _name, ofstream& out); // 파일에 출력
	void showFlightInfo(string s, int _flight_number, ofstream& out); // 파일에 출력
};

class Passenger
{
private:
	string name; // 이름

	Passenger* prev_passenger; // 같은 비행기의 이전 탑승객
	Passenger* next_passenger; // 같은 비행기의 다음 탑승객
	bool flag; // 예약 성공 여부
	Flight* this_flight; // 예약한 비행기편 포인터
	Customer* cus; // 고객 노드에 대한 포인터
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
	string name;  // 이름

	Customer* prev_customer; // 이전 고객에 대한 포인터
	Customer* next_customer; // 다음 고객에 대한 포인터
	Flight* reserve_flight_head; // 예약한 flight list head
	Flight* reserve_flight_tail; // 예약한 flight list tail
	Flight* standby_flight_head; // 대기 중 flight list head
	Flight* standby_flight_tail; // 대기 중 flight list tail
	bool flag; // 비행기 예약 여부
public:
	Customer(string _name);
	void add_flight(Flight* _flight); // 예약 비행기 추가
	void add_standby_flight(Flight* _flight); // 대기 비행기 추가
	bool is_reserve(); // 예약했으면 true, 예약 안 했으면 false
	bool is_standby(); // 대기 했으면 true, 대기 없으면 false
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
	void add(string _name, Flight* this_flight); // 예약 고객 리스트에 인자로 받은 이름대로 Passenger 객체를 생성해 고객 추가
	void connect_link(Passenger* prev, Passenger* next);
	void connect_link(Passenger* prev, Passenger* curr, Passenger* next);
	bool is_empty(); // 예약고객리스트가 비어있는지 확인
	friend class Flight;
	friend class ReservationSystem;
};

class StandByPassenger // 우선순위 큐로 삽입
{
private:
	Passenger* head;
	Passenger* tail;
public:
	StandByPassenger();
	void enque(string _name);
	string deque(); // 대기인원 deque. standby 인원 변동 없음.
	void connect_link(Passenger* prev, Passenger* next);
	void connect_link(Passenger* prev, Passenger* curr, Passenger* next);
	bool is_full(); // 대기고객리스트가 비어있는지 확인
	bool is_empty(); // 대기고객리스트가 꽉 찼는지 확인
	friend class Flight;
	friend class ReservationSystem;
};