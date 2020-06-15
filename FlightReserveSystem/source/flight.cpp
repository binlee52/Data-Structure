#include "flight.h"
#include <iomanip> // setw(), setfill() 라이브러리 비행기 편의 이름을 4자리 수로 출력하기 위함.
#include <sstream>

using namespace std;

Flight::Flight(int _flight_number, string _from_city, string _to_city, int _capacity)
	: flight_number(_flight_number), from_city(_from_city), to_city(_to_city),
	capacity(_capacity), passenger(0), standby(0), full(false), flag(false)
{
	prev_flight = NULL;
	next_flight = NULL;
	reserve_list = new ReservePassenger;
	standby_list = new StandByPassenger; 
}

Flight::Flight()
	: flight_number(-1), from_city("dummy node"), to_city("dummy node"),
	capacity(-1), passenger(-1), standby(-1), full(false), flag(false)
{
	prev_flight = NULL;
	next_flight = NULL;

	reserve_list = new ReservePassenger;
	standby_list = new StandByPassenger;
}

/**
Function: Flight::is_full
Parameter: None
Return: bool

Description: 예약 고객리스트 Flight::reserve_list가 꽉 찼는지 확인
**/
bool Flight::is_full()
{
	full = capacity <= passenger;
	return full;
}

/**
Function: Flight::show_name
Parameter: ofstream&
Return: None

Description: 파일에 결과 출력
**/
void Flight::show_name(ofstream& out)
{
	out << "[Flight NO." << setw(4) << setfill('0') << flight_number << "]" << endl;
	out << "Reserved List: ";
	Passenger * rp = reserve_list->head->next_passenger;
	while (rp != reserve_list->tail)
	{
		out << rp->name << " ";
		rp = rp->next_passenger;
	}
	out << endl;
	out << "Stand-by List : ";
	Passenger* sp = standby_list->head->next_passenger;
	while (sp != standby_list->tail && sp != NULL)
	{
		out << sp->name << " ";
		sp = sp->next_passenger;
	}
	out << endl << "------------------------------" << endl;
}


/**
Function: Flight::show_info
Parameter: ofstream&
Return: None

Description: 파일에 결과 출력
**/
void Flight::show_info(ofstream& out)
{

	out << "[Flight NO." << setw(4) << setfill('0') << flight_number << "]" << endl;
	out << "From : " << from_city << endl;
	out << "To : " << to_city << endl;
	out << "Capacity : " << capacity << "명" << endl;
	out << "Reserved : " << passenger << "명" << endl;
	if (standby > 0)
		out << "Stand-by  : " << standby << "명" << endl;
	out << endl << "------------------------------" << endl;
}


/**
Function: reserve_flight
Parameter: string, Flight*
Return: None

Description: 이름 순으로 비행기에 고객 예약. reserve 인원 추가.
**/
void Flight::reserve_flight(string _name, Flight* this_flight)
{
	reserve_list->add(_name, this_flight);
	passenger++;
}


/**
Function: stand_flight
Parameter: string
Return: None

Description: 대기 신청한 순서대로 비행기에 고객 대기. standby 인원 추가.
**/
void Flight::stand_flight(string _name)
{
	standby_list->enque(_name);
	standby++;
}


/**
Function: pop_standby
Parameter: 
Return: string

Description: 가장 먼저 대기 신청한 고객을 대기고객리스트에서 pop. standby 인원 감소
**/
string Flight::pop_standby()
{
	string s = standby_list->deque();
	standby--;
	return s;
}

ReservationSystem::ReservationSystem()
	: head_flight(NULL), tail_flight(NULL), flight_cnt(0), customer_cnt(0)
{
	head_flight = new Flight(-1, "Dummy Flight", "Dummy Flight", -1);	// dummy node
	tail_flight = new Flight(10000, "Dummy Flight", "Dummy Flight", -1);	// dummy node
	connect_link(head_flight, tail_flight);

	head_customer = new Customer("dummy node"); // dummy node
	tail_customer = new Customer("dummy node"); // dummy node
	connect_link(head_customer, tail_customer);
}

ReservationSystem::~ReservationSystem()
{
	while (head_customer->next_customer != tail_customer)
	{
		Customer* c = head_customer->next_customer;
		connect_link(c->prev_customer, c->next_customer);
		delete c;
	}
	delete head_customer;
	delete tail_customer;
	while (head_flight->next_flight != tail_flight)
	{
		Flight* f = head_flight->next_flight;
		connect_link(f->prev_flight, f->next_flight);
		delete f;
	}
	delete head_flight;
	delete tail_flight;
}

void ReservationSystem::connect_link(Flight* prev, Flight* curr, Flight* next)
{
	curr->prev_flight = prev;
	curr->next_flight = next;
	curr->prev_flight->next_flight = curr;
	curr->next_flight->prev_flight = curr;
}

void ReservationSystem::connect_link(Flight* prev, Flight* next)
{
	prev->next_flight = next;
	next->prev_flight = prev;
}

/**
Function: ReservationSystem::insert_flight
Parameter: int, string, string, int
Return:

Description: 비행기 리스트에 비행기 추가
**/
void ReservationSystem::insert_flight(int _flight_number, string _from_city, string _to_city, int _capacity)
{
	if (!is_full())
	{
		Flight* new_flight = new Flight(_flight_number, _from_city, _to_city, _capacity);
		if (is_empty())
		{
			std::cout << "Insert " << setw(4) << setfill('0') << new_flight->flight_number << endl; 
			connect_link(head_flight, new_flight, tail_flight);
		}	
		else
		{
			//Flight* minFlight;
			Flight* p = head_flight->next_flight;	// 인덱스 비행기
			int new_flight_number = new_flight->flight_number;
			while (p != NULL && p != tail_flight)
			{

				if (p->flight_number == new_flight_number)	// 같은 비행기편이 이미 존재할 경우
				{
					std::cout << setw(4) << setfill('0') << new_flight_number << " is already exits." << endl;
					flight_cnt--;
					break;
				}
				else if (p->flight_number < new_flight_number)	// new_flight의 flight_number가 인덱스 비행기들보다 작을 때
					p = p->next_flight;
				else						// new_flight의 flight number가 인덱스 비행기보다 클 때
				{
					std::cout << "Insert " << setw(4) << setfill('0') << new_flight->flight_number << endl;
					connect_link(p->prev_flight, new_flight, p);
					break;
				}

				if (p == tail_flight)		// List의 모든 flight number가 new_flight보다 작을 때
				{
					std::cout << "Insert " << setw(4) << setfill('0') << new_flight->flight_number << endl;
					connect_link(tail_flight->prev_flight, new_flight, tail_flight);
					break;
				}	
			}
		}
		flight_cnt++;
	}
}

/**
Function: ReservationSystem::delete_flight
Parameter: int
Return:

Description: 비행기 리스트에서 비행기편 삭제
**/
void ReservationSystem::delete_flight(int _flight_number)
{
	if (!is_empty())
	{
		Flight* p = head_flight->next_flight;
		bool found = false;
		while (p != tail_flight && p != NULL)
		{
			if (_flight_number == p->flight_number)
			{	
				connect_link(p->prev_flight, p->next_flight);
				flight_cnt--;
				Passenger* temp = p->reserve_list->head->next_passenger;
				while (p->reserve_list->head->next_passenger != p->reserve_list->tail)
				{
					Passenger* temp = p->reserve_list->head->next_passenger;
					Customer* c = temp->cus;
					delete_flight_in_reserve(c, _flight_number);
					connect_link(temp->prev_passenger, temp->next_passenger);
					if (!c->is_reserve() && !c->is_standby())
					{
						connect_link(c->prev_customer, c->next_customer);
						delete c;
					}
					delete temp;
				}
				while (p->standby_list->head->next_passenger != p->standby_list->tail)
				{
					Passenger* temp = p->standby_list->head->next_passenger;
					Customer* c = temp->cus;
					delete_flight_in_standby(c, _flight_number);
					connect_link(temp->prev_passenger, temp->next_passenger);
					if (!c->is_reserve() && !c->is_standby())
					{
						connect_link(c->prev_customer, c->next_customer);
						delete c;
					}
					delete temp;
				}
				delete p;
				std::cout << setw(4) << setfill('0') << _flight_number << " delete Complete!" << endl; // testing
				found = true;
				break;
			}
			p = p->next_flight;
		}
		if (!found)
			std::cout << setw(4) << setfill('0') << _flight_number << " does not exist." << endl;
	}
}

void ReservationSystem::connect_link(Passenger* prev, Passenger* next)
{
	prev->next_passenger = next;
	next->prev_passenger = prev;
}

/**
Function: ReservationSystem::cancle
Parameter: string, int
Return:

Description: 비행기 예약 혹은 대기 취소(전체 삭제, 혹은 특정 편 삭제 가능)
**/
void ReservationSystem::cancle(string _name, int _flight_number)
{
	if (is_empty())
	{
		std::cout << "비행기가 없습니다." << endl;
	}
	else if (_flight_number != 0)
		cancle_reserve(_name, _flight_number);
	else
		cancle_all_reserve(_name);
}

/**
Function: ReservationSystem::cancle_all_reserve
Parameter: string
Return:

Description: 모든 예약 및 대기 취소
**/
void ReservationSystem::cancle_all_reserve(string _name) // 삭제 
{
	bool found = false;
	Customer* c = head_customer->next_customer;
	while (c != tail_customer && !found)
	{
		if (c->name == _name)
		{
			found = true;
			break;
		}
		c = c->next_customer;
	}
	if (!found)
		std::cout << _name << "고객님은 고객 리스트에 명단이 없습니다." << endl;
	else
	{
		if (c->is_reserve() || c->is_standby())
		{
			while (c->is_reserve())
			{
				Flight* p = c->reserve_flight_head->next_flight;
				connect_link(p->prev_flight, p->next_flight);
				int flight_number = p->flight_number;
				cancle_reserve(_name, flight_number);
				delete p;
			}
			while (c->is_standby())
			{
				Flight* p = c->standby_flight_head->next_flight;
				connect_link(p->prev_flight, p->next_flight);
				int flight_number = p->flight_number;
				cancle_standby(_name, flight_number);
				delete p;
			}
		}
	}
}

/**
Function: ReservationSystem::cancle_standby
Parameter: string, int
Return:

Description: 특정 비행기편 대기 취소
**/
void ReservationSystem::cancle_standby(string _name, int _flight_number)
{
	if (!is_empty())
	{
		Flight* p = head_flight->next_flight;
		bool found = false;
		while (p != tail_flight && p != NULL && !found)
		{
			if (_flight_number == p->flight_number)
			{
				Passenger* q = p->standby_list->head->next_passenger;
				while (q != p->standby_list->tail && q != NULL)
				{
					if (q->name == _name)
					{
						found = true;
						connect_link(q->prev_passenger, q->next_passenger);
						p->standby--;
						// 비행기편 고객의 Customer link 고객 노드와 연결
						Customer* customerLink = q->cus;
						// 고객 노드에서 예약한 비행기편 비행기 편 삭제
						delete_flight_in_standby(customerLink, _flight_number);
						if (!customerLink->flag && !customerLink->is_standby())
							connect_link(customerLink->prev_customer, customerLink->next_customer);
						delete q;
						break;
					}
					q = q->next_passenger;
				}
			}
			p = p->next_flight;
		}
		if (!found)
			std::cout << setw(4) << setfill('0') << _flight_number << " 비행기편이나 " << _name
			<< "탑승객이 예약 리스트에 존재하지 않습니다." << endl;
	}
}

/**
Function: ReservationSystem::cancle_reserve
Parameter: string, int
Return:

Description: 특정 비행기편 예약 취소
**/
void ReservationSystem::cancle_reserve(string _name, int _flight_number)
{
	if (!is_empty())
	{
		Flight* p = head_flight->next_flight;
		bool found = false;
		while (p != tail_flight && p != NULL && !found)
		{
			if (_flight_number == p->flight_number)
			{
				Passenger* q = p->reserve_list->head->next_passenger;
				while (q != p->reserve_list->tail && q != NULL)
				{
					if (q->name == _name)
					{
						std::cout << "Cancle " << _name << " in " << setw(4) << setfill('0') << p->flight_number << endl;
						found = true;
						connect_link(q->prev_passenger, q->next_passenger);
						p->passenger--;
						// 비행기편 고객의 Customer link 고객 노드와 연결
						Customer* customerLink = q->cus;
						// 고객 노드에서 예약한 비행기편 비행기 편 삭제
						delete_flight_in_reserve(customerLink, _flight_number);
						if (!customerLink->flag && !customerLink->is_standby())
							connect_link(customerLink->prev_customer, customerLink->next_customer);
						delete q;
						if (p->standby > 0 && !(p->is_full())) // TODO
						{
							string temp = p->pop_standby();
							Customer* c = head_customer->next_customer;
							while (c->name != temp)
								c = c->next_customer;
							delete_flight_in_standby(c, p->flight_number);
							reserve(temp, _flight_number);
							Passenger* t = p->reserve_list->head->next_passenger;
							std::cout << "goto Reserved: " << temp << endl;
						}
						break;
					}
					q = q->next_passenger;
				}
			}
			p = p->next_flight;
		}
		if (!found)
			std::cout << setw(4) << setfill('0') << _flight_number << " 비행기편이나 " << _name 
				<< "탑승객이 예약 리스트에 존재하지 않습니다." << endl;
	}
}


/**
Function: ReservationSystem::delete_flight_in_reserve
Parameter: Customer*, int
Return:

Description: 예약한 특정 비행기편 Customer 객체의 예약 비행기 리스트에서 삭제
**/
void ReservationSystem::delete_flight_in_reserve(Customer* customerLink, int _flight_number)
{
	Flight* q = customerLink->reserve_flight_head->next_flight;
	while (q != customerLink->reserve_flight_tail)
	{
		if (q->flight_number == _flight_number)
		{
			connect_link(q->prev_flight, q->next_flight);
			break;
		}
		q = q->next_flight;
	}
	customerLink->is_reserve();
}

/**
Function: ReservationSystem::standby_flight_in_reserve
Parameter: Customer*, int
Return:

Description: 대기 중인특정 비행기편 Customer 객체의 대기 비행기 리스트에서 삭제
**/
void ReservationSystem::delete_flight_in_standby(Customer* customerLink, int _flight_number)
{
	Flight* q = customerLink->standby_flight_head->next_flight;
	while (q != customerLink->standby_flight_tail)
	{
		if (q->flight_number == _flight_number)
		{
			connect_link(q->prev_flight, q->next_flight);
			break;
		}
		q = q->next_flight;
	}
	customerLink->is_reserve();
}

/**
Function: ReservationSystem::linkPasCus
Parameter: Flight*, string
Return:

Description: Passenger 클래스의 멤버변수 cus가 Customer 객체를 가리키도록 연결
**/
void ReservationSystem::linkPasCus(Flight* _flight, string _name)
{
	bool flag = false;
	Passenger* p = _flight->reserve_list->head->next_passenger;
	// reserve_list에 있는 경우
	while (p != _flight->reserve_list->tail)
	{
		if (p->name == _name)
		{
			Customer* c = head_customer->next_customer;
			while (c != tail_customer)
			{
				c->is_reserve();
				if (c->name == _name)
				{
					p->cus = c;
					flag = true;
					break;
				}
				c = c->next_customer;
			}
			break;
		}
		p = p->next_passenger;
	}
	// standby_list에 있는 경우
	if (!flag) 
	{
		p = _flight->standby_list->head->next_passenger;
		while (p != _flight->standby_list->tail)
		{
			if (p->name == _name)
			{
				Customer* c = head_customer->next_customer;
				while (c != tail_customer)
				{
					c->is_reserve();
					if (c->name == _name)
					{
						p->cus = c;
						flag = true;
						break;
					}
					c = c->next_customer;
				}
				break;
			}
			p = p->next_passenger;
		}
	}
	if (!flag)
		std::cout << "Link 실패" << endl;
}

/**
Function: ReservationSystem::reserve
Parameter: string, int
Return:

Description: 비행기 예약 혹은 대기
**/
void ReservationSystem::reserve(string _name, int _flight_number)
{
	if (!is_empty())
	{
		Customer* c = head_customer->next_customer;
		bool is_flight = false;
		while (c != tail_customer)
		{
			if (c->name == _name)
			{
				Flight* p = c->reserve_flight_head->next_flight;
				while (p != c->reserve_flight_tail && !is_flight)
				{
					if (p->flight_number == _flight_number)
					{
						is_flight = true;
						break;
					}
					p = p->next_flight;
				}
				p = c->standby_flight_head->next_flight;
				while (p != c->standby_flight_tail && !is_flight)
				{
					if (p->flight_number == _flight_number)
					{
						is_flight = true;
						break;
					}
					p = p->next_flight;
				}
			}
			c = c->next_customer;
		}
		if (!is_flight)
		{
			// Flight에 추가
			Flight* p = head_flight->next_flight;
			while (p != tail_flight && p != NULL)
			{
				if (p->flight_number == _flight_number)
				{
					if (!p->is_full())
					{
						p->reserve_flight(_name, p);
						Flight* temp = new Flight;
						*temp = *p;
						add_customer(_name, temp);
						linkPasCus(p, _name);
						std::cout << "Reserve " << _name << " in " << setw(4) << setfill('0') << p->flight_number << endl;
						break;
					}
					else
					{
						std::cout << setw(4) << setfill('0') << p->flight_number << " is Full." << endl;
						std::cout << "goto Stand-by List" << _name << endl;
						p->stand_flight(_name);
						Flight* temp = new Flight;
						*temp = *p;
						standby_customer(_name, temp);
						linkPasCus(p, _name);
						break;
					}
				}
				p = p->next_flight;
			}
		}
		else
			std::cout << _name << " has already booked " << setw(4) << setfill('0') << _flight_number << endl;
	}
	else
		std::cout << "Empty Flight List" << endl;
}

/**
Function: ReservationSystem::standby_customer
Parameter: string, Flight*
Return:

Description: 대기 고객 추가
**/
void ReservationSystem::standby_customer(string _name, Flight* _flight)
{
	Flight* p = _flight;
	// Customer에 추가
	Customer* newCustomer = new Customer(_name);
	newCustomer->add_standby_flight(p);
	if (is_empty_cumstomer())
	{
		connect_link(head_customer, newCustomer, tail_customer);
		customer_cnt++;
	}
	else
	{
		Customer* c = head_customer->next_customer;
		while (c != tail_customer && c != NULL)
		{
			if (newCustomer->name > c->name)
			{
				c = c->next_customer;
			}
			else if (newCustomer->name == c->name) // 같은 이름 있을시 비행기 추가
			{
				c->add_standby_flight(p);
				break;
			}
			else
			{
				connect_link(c->prev_customer, newCustomer, c);
				customer_cnt++;
				break;
			}

			if (c == tail_customer)
			{
				connect_link(tail_customer->prev_customer, newCustomer, tail_customer);
				customer_cnt++;
				break;
			}
		}
	}
}

/**
Function: ReservationSystem::add_customer
Parameter: string, Flight*
Return:

Description: 예약 고객 추가
**/
void ReservationSystem::add_customer(string _name, Flight* _flight)
{
	Flight* p = _flight;
	// Customer에 추가
	Customer* newCustomer = new Customer(_name);
	newCustomer->add_flight(p);
	newCustomer->is_reserve();
	if (is_empty_cumstomer())
	{
		connect_link(head_customer, newCustomer, tail_customer);
		customer_cnt++;
	}
	else
	{
		Customer* c = head_customer->next_customer;
		while (c != tail_customer && c != NULL)
		{
			if (newCustomer->name > c->name)
			{
				c = c->next_customer;
			}
			else if (newCustomer->name == c->name) // 같은 이름 있을시 비행기 추가
			{	
				c->add_flight(p);
				c->is_reserve();
				break;
			}
			else
			{
				connect_link(c->prev_customer, newCustomer, c);
				customer_cnt++;
				break;
			}

			if (c == tail_customer)
			{
				connect_link(tail_customer->prev_customer, newCustomer, tail_customer);
				customer_cnt++;
				break;
			}
		}
	}
}


/**
Function: Customer::add_standby_flight
Parameter: Flight*
Return: 

Description: 비행기를 대기비행기 리스트에 추가
**/
void Customer::add_standby_flight(Flight* _flight)
{
	Flight* newFlight = _flight;
	if (!is_standby()) // 비행기를 하나도 예약하지 않았다면
		connect_link(standby_flight_head, newFlight, standby_flight_tail);
	else // 비행기가 예약 되어있다면
	{
		Flight* p = standby_flight_head->next_flight;
		while (p != standby_flight_tail && p != NULL)
		{
			if (newFlight->flight_number > p->flight_number)
				p = p->next_flight;
			else if (newFlight->flight_number < p->flight_number)
			{
				connect_link(p->prev_flight, newFlight, p);
				break;
			}
			else
			{
				std::cout << "이미 같은 비행기를 예약했습니다." << endl;
				break;
			}
			if (p == standby_flight_tail)
			{
				connect_link(p->prev_flight, newFlight, p);
				break;
			}
		}
	}
}

/**
Function: Customer::add_flight
Parameter: Flight*
Return:

Description: 비행기를 예약 비행기 리스트에 추가
**/
void Customer::add_flight(Flight* _flight)
{
	Flight* newFlight = _flight;
	if (!is_reserve()) // 비행기를 하나도 예약하지 않았다면
		connect_link(reserve_flight_head, newFlight, reserve_flight_tail);
	else // 비행기가 예약 되어있다면
	{
		Flight* p = reserve_flight_head->next_flight;
		while (p != reserve_flight_tail && p != NULL)
		{
			if (newFlight->flight_number > p->flight_number)
				p = p->next_flight;
			else if (newFlight->flight_number < p->flight_number)
			{
				connect_link(p->prev_flight, newFlight, p);
				break;
			}
			else
			{
				std::cout << "이미 같은 비행기를 예약했습니다." << endl;
				break;
			}
			if (p == reserve_flight_tail)
			{
				connect_link(p->prev_flight, newFlight, p);
				break;
			}				
		}
	}
	is_reserve();
}

/**
Function: Customer::is_reserve
Parameter:
Return:

Description: 예약된 비행기가 있으면 true, 없으면 false return
**/
bool Customer::is_reserve()
{
	if (reserve_flight_head->next_flight != reserve_flight_tail) // 예약한 비행기가 있을 시
	{
		flag = true;
		return true;
	}
	else // 예약한 비행기가 없을 시
	{
		flag = false;
		return false;
	}
}

/**
Function: Customer::is_standby
Parameter:
Return:

Description: 대기 중인 비행기가 있으면 true, 없으면 false return
**/
bool Customer::is_standby()
{
	if (standby_flight_head->next_flight != standby_flight_tail) // 대기 중인 비행기가 있을 시
		return true;
	else // 대기 중인 비행기가 없을 시
		return false;
}

/**
Function: ReservationSystem::is_empty
Parameter:
Return:

Description: 비행기 리스트가 비어있는지 확인
**/
bool ReservationSystem::is_empty()
{
	if (head_flight->next_flight == tail_flight && flight_cnt <= 0)
		return true;
	return false;
}

/**
Function: ReservationSystem::is_full
Parameter:
Return:

Description: 비행기 리스트가 꽉 차있는지 확인
**/
bool ReservationSystem::is_full()
{
	Flight* temp = new Flight(-1, "abc", "abc", -1);
	if (temp == NULL)
		return true;
	delete temp;
	return false;
}

/**
Function: ReservationSystem::is_empty_customer
Parameter:
Return:

Description: 고객 객체가 비어있는지 확인
**/
bool ReservationSystem::is_empty_cumstomer()
{
	return head_customer->next_customer == tail_customer;
}


void ReservationSystem::showAllFlightNumber(string c, ofstream& out)
{	
	if (!is_empty())
	{
		out << "==============================" << endl;
		out << "총 비행기: " << flight_cnt << "대" << endl;
		Flight* p = head_flight->next_flight;
		while (p != tail_flight && p != NULL)
		{
			if (c == "PA" || c == "pa")
				showFlightInfo("PA", p->flight_number, out);
			else if (c == "PF" || c == "pf")
				showFlightInfo("PF", p->flight_number, out);
			else
			{
				std::cout << "Wrong Order!" << endl;
				break;
			}
				
			p = p->next_flight; 
		}
	}
	else
		std::cout << "비행기가 없습니다." << endl << endl;
	out << "==============================" << endl;
}


void ReservationSystem::showAllCustomerInfo(ofstream& out)
{
	if (!is_empty_cumstomer())
	{
		Customer* p = head_customer->next_customer;
		while (p != tail_customer && p != NULL)
		{
			out << p->name << " ";
			p = p->next_customer;
		}
		out << endl;
	}
	else
		std::cout << "No Customer!" << endl;
}


void ReservationSystem::showFlightInfo(string s, int _flight_number, ofstream& out)
{
	if (!is_empty())
	{
		Flight* p = head_flight->next_flight;
		while (p != tail_flight && p != NULL)
		{
			if (p->flight_number == _flight_number)
			{
				if (s == "PA" || s == "pa" || s == "PR" || s == "pr")
					p->show_name(out);
				else if(s == "PF" || s == "pf")
					p->show_info(out);
				break;
			}
			p = p->next_flight;
		}
	}
}


void ReservationSystem::ShowCustomerInfo(string _name, ofstream& out)
{
	bool found = false;
	Customer* p = head_customer->next_customer;
	while (p != tail_customer && p != NULL && !found)
	{
		if (p->name == _name)
		{
			found = true;
			out << "[Customer Name: " << p->name << "]" << endl;
			Flight* q = p->reserve_flight_head ->next_flight;
			if (p->is_reserve())
			{
				out << "Reserved Flight: " << endl;
				while (q != p->reserve_flight_tail && q != NULL)
				{
					out << "[Flight NO." << setw(4) << setfill('0') << q->flight_number << "]" << endl;
					out << "From: " << q->from_city << endl;
					out << "To  : " << q->to_city << endl;
					out << "Reservation: OK" << endl << endl;
					q = q->next_flight;
				}
			}
			q = p->standby_flight_head->next_flight;
			if (p->is_standby())
			{
				std::cout << "Standby Flight: " << endl;
				while (q != p->standby_flight_tail && q != NULL)
				{
					out << "[Flight NO." << setw(4) << setfill('0') << q->flight_number << "]" << endl;
					out << "From: " << q->from_city << endl;
					out << "To  : " << q->to_city << endl;
					out << "Reservation: Fail" << endl << endl;
					q = q->next_flight;
				}
			}
		}
		p = p->next_customer;
	}
	if (!found)
		std::cout << _name << "고객님은 예약 또는 대기 중인 비행기가 없습니다. " << endl;
	out << "------------------------------" << endl;
}	


Passenger::Passenger(string _name)
	: name(_name), prev_passenger(NULL), next_passenger(NULL), flag(false), this_flight(NULL), cus(NULL)
{}

ReservePassenger::ReservePassenger()
{
	head = new Passenger("Dummy Node");
	tail = new Passenger("Dummy Node");
	connect_link(head, tail);
}

/**
Function: ReservePassenger::add
Parameter: string, Flight*
Return:

Description: parameter로 받은 string 대로 passenger 객체를 생성하고 예약한 비행기 편과 링크
**/
void ReservePassenger::add(string _name, Flight* this_flight)
{
	Passenger* newPassenger = new Passenger(_name);
	newPassenger->flag = true;
	Passenger* p = head->next_passenger;
	newPassenger->this_flight = this_flight;
	if (is_empty())
		connect_link(head, newPassenger, tail);
	else
	{
		while (p != NULL && p != tail)
		{
			if (p->name < newPassenger->name)
				p = p->next_passenger;
			else
			{
				connect_link(p->prev_passenger, newPassenger, p);
				break;
			}
			if (p == tail)
			{
				connect_link(p->prev_passenger, newPassenger, p);
				break;
			}
		}
	}
}

/**
Function: ReservePassenger::is_empty
Parameter:
Return:

Description: 예약고객리스트가 비어있는지 확인
**/
bool ReservePassenger::is_empty()
{
	if (head->next_passenger == tail)
		return true;
	return false;
}

void ReservePassenger::connect_link(Passenger* prev, Passenger* next)
{
	prev->next_passenger = next;
	next->prev_passenger = prev;
}

void ReservePassenger::connect_link(Passenger* prev, Passenger* curr, Passenger* next)
{
	curr->prev_passenger = prev;
	curr->next_passenger = next;
	curr->prev_passenger->next_passenger = curr;
	curr->next_passenger->prev_passenger = curr;
}

StandByPassenger::StandByPassenger()
{
	head = new Passenger("Dummy Node");
	tail = new Passenger("Dummy Node");
	connect_link(head, tail);
}

/**
Function: StandbyPassenger::enque
Parameter: string
Return:

Description: parameter로 받은 string 대로 Passenger 객체를 생성
**/
void StandByPassenger::enque(string _name) 
{
	Passenger* newPassenger = new Passenger(_name);
	//newPassenger->cus = new Customer(_name);
	if (is_empty())
		connect_link(head, newPassenger, tail);
	else
		connect_link(tail->prev_passenger, newPassenger, tail);
}

/**
Function: StandByPassenger::deque
Parameter:
Return:

Description: 가장 먼저 대기신청한 고객을 deque. standby 인원 변동은 Flight class 에서 한다.
**/
string StandByPassenger::deque()
{
	if (!is_empty())
	{
		Passenger* p = head->next_passenger;
		connect_link(head, p->next_passenger);
		string deque_name = p->name;
		delete p;
		return deque_name;
	}
	return "Empty stand-by list.";
}

/**
Function: StandByPassenger::is_full
Parameter:
Return:

Description: 대기고객리스트가 꽉 찼는지 학인
**/
bool StandByPassenger::is_full()
{
	Passenger* temp = new Passenger("temp");
	if (temp == NULL)
		return true;
	delete temp;
	return false;
}

/**
Function: StandByPassenger::is_empty
Parameter:
Return:

Description: 대기고객리스트가 비어있는지 학인
**/
bool StandByPassenger::is_empty()
{
	if (head->next_passenger == tail)
		return true;
	return false;
}


void StandByPassenger::connect_link(Passenger* prev, Passenger* next)
{
	prev->next_passenger = next;
	next->prev_passenger = prev;
}

void StandByPassenger::connect_link(Passenger* prev, Passenger* curr, Passenger* next)
{
	curr->prev_passenger = prev;
	curr->next_passenger = next;
	curr->prev_passenger->next_passenger = curr;
	curr->next_passenger->prev_passenger = curr;
}

Customer::Customer(string _name)
	: name(_name), next_customer(NULL), prev_customer(NULL), flag(false)
{
	reserve_flight_head = new Flight(-1, "dummy node", "dummy node", -1);
	reserve_flight_tail = new Flight(10001, "dummy node", "dummy node", -1);
	connect_link(reserve_flight_head, reserve_flight_tail);

	standby_flight_head = new Flight(-1, "dummy node", "dummy node", -1);
	standby_flight_tail = new Flight(10001, "dummy node", "dummy node", -1);
	connect_link(standby_flight_head, standby_flight_tail);
}

void ReservationSystem::connect_link(Customer* prev, Customer* next)
{
	prev->next_customer = next;
	next->prev_customer = prev;
}

void ReservationSystem::connect_link(Customer* prev, Customer* curr, Customer* next)
{
	curr->prev_customer = prev;
	curr->prev_customer->next_customer = curr;
	curr->next_customer = next;
	curr->next_customer->prev_customer = curr;
}

void Customer::connect_link(Flight* prev, Flight* next)
{
	prev->next_flight = next;
	next->prev_flight = prev;
}

void Customer::connect_link(Flight* prev, Flight* curr, Flight* next)
{
	curr->prev_flight = prev;
	curr->prev_flight->next_flight = curr;
	curr->next_flight = next;
	curr->next_flight->prev_flight = curr;
}

