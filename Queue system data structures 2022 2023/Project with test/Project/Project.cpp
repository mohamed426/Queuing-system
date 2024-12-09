#include<iostream>
#include<string>
#include<fstream>
using namespace std;

ifstream tst("test.txt");

struct Nnode// for normal clients
{
	string service_name, mobile_number;
	int client_no = 0;
	Nnode* nextn = 0;
};

Nnode* n_current = NULL;
Nnode* n_front = NULL;
Nnode* n_rear = NULL;

struct Vnode// for vip clients
{
	string service_name, mobile_number;
	int client_no = 0;
	Vnode* nextv = 0;
};

Vnode* v_current = NULL;
Vnode* v_front = NULL;
Vnode* v_rear = NULL;

void cenq(int cli, string servname, string mobilenum)// for normal clients
{
	n_current = new Nnode();
	n_current->mobile_number = mobilenum;
	n_current->client_no = cli;
	n_current->service_name = servname;
	if (n_rear == NULL)
	{
		n_front = n_current;
		n_rear = n_current;
	}
	else
	{
		n_rear->nextn = n_current;
		n_rear = n_current;
	}
	n_rear->nextn = NULL;
}

void venq(int cli, string servname, string mobilenum)// for vip clients
{
	v_current = new Vnode();
	v_current->mobile_number = mobilenum;
	v_current->client_no = cli;
	v_current->service_name = servname;
	if (v_rear == NULL)
	{
		v_front = v_current;
		v_rear = v_current;
	}
	else
	{
		v_rear->nextv = v_current;
		v_rear = v_current;
	}
	v_rear->nextv = NULL;
}

void displayall()// for all clients
{
	if (v_front != NULL)
	{
		v_current = v_front;
		while (v_current != NULL)
		{
			cout << "Customer : " << v_current->client_no << "V\t"<<v_current->mobile_number<<"\t"<< v_current->service_name<< endl;
			v_current = v_current->nextv;
		}
	}
	if (n_front != NULL)
	{
		n_current = n_front;
		
		while (n_current != NULL)
		{
			cout << "Customer : " << n_current->client_no << "C\t"<<n_current->mobile_number<<"\t"<<n_current->service_name << endl;
			n_current = n_current->nextn;
		}
	}
	else if (v_front == NULL || n_front == NULL)
	{
		cout << "There are no customers" << endl;
	}
}

void displayvip()// for vip clients
{
	if (v_front != NULL)
	{
		v_current = v_front;

		while (v_current != NULL)
		{
			cout << "Customer : " << v_current->client_no << "V\t" << v_current->mobile_number << "\t" << v_current->service_name << endl;
			v_current = v_current->nextv;
		}
	}
	else
	{
		cout << "There are no customers" << endl;
	}
}

void deq()
{
	if (v_front != NULL)
	{
		v_current = v_front;
		v_front = v_front->nextv;
		delete v_current;
	}
	else if (n_front != NULL)
	{
		n_current = n_front;
		n_front = n_front->nextn;
		delete n_current;
	}
	else if (n_front == NULL && v_front == NULL)
	{
		cout << "There are no customers" << endl;
	}
	if (n_front == NULL)
	{
		n_rear = NULL;
	}
	if (v_front == NULL)
	{
		v_rear = NULL;
	}
}

bool how_many_num(string phone)//to check if phonenumber contains 11 numbers only 
{
	if (phone.size() == 11)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool containsOnlyNumbers(string const& str) //to check if phonenumber contains numbers only 
{
	return str.find_first_not_of("0123456789") == string::npos;
}

void search_by_phone()
{
	string phone;
	cout << "What is the phone number of the customer you want to search for ? " << endl;
	tst >> phone;
	//cin >> phone;
	if (containsOnlyNumbers(phone) && how_many_num(phone))
	{
		bool search_vip = 0;
		Vnode* i;
		for (i = v_front; i != NULL; i = i->nextv)
		{
			if (phone == i->mobile_number)
			{
				cout << "There " << i->client_no << "V" << endl;
				search_vip = 1;
			}
		}

		bool search_normal = 0;
		Nnode* j;
		for (j = n_front; j != NULL; j = j->nextn)
		{
			if (phone == j->mobile_number)
			{
				cout << "There " << j->client_no << "C" << endl;
				search_normal = 1;
			}
		}
		if (search_normal == 0 && search_vip == 0)
		{
			cout << "There are no customers" << endl;
		}
	}
	else// not contain numbers only and not = 11
	{
		while (true)
		{
			cout << "Phone number should contains 11 numbers only" << endl;
			cin >> phone;
			if (containsOnlyNumbers(phone) && how_many_num(phone))
			{
				bool search_vip = 0;
				Vnode* i;
				for (i = v_front; i != NULL; i = i->nextv)
				{
					if (phone == i->mobile_number)
					{
						cout << "There " << i->client_no << "V" << endl;
						search_vip = 1;
					}
				}
				bool search_normal = 0;
				Nnode* j;
				for (j = n_front; j != NULL; j = j->nextn)
				{
					if (phone == j->mobile_number)
					{
						cout << "There " << j->client_no << "C" << endl;
						search_normal = 1;
					}
				}
				if (search_normal == 0 && search_vip == 0)
				{
						cout << "There are no customers" << endl;
				}
				break;
			}
		}
	}
}

bool containsOnlyLetters(string const& str) //to check if servicename contains letters only 
{
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") == string::npos;
}

bool avilableservices(string sername)
{
	if (sername != "teller" && sername != "loans" && sername != "customer_service")
	{
		return false;
	}
}

void search_by_sername()
{
	bool search_vip = 0;
	bool search_normal = 0;
	string sername;
	cout << "What is the service through which you want to search for the customer ?"<<endl;
	tst >> sername;
	//cin >> sername;
	Vnode* i;
	if (containsOnlyLetters(sername))
	{
		for (i = v_front; i != NULL; i = i->nextv)
		{
			if (sername == i->service_name)
			{
				cout << "There " << i->client_no << "V" << endl;
				search_vip = 1;
			}
		}
		Nnode* j;
		for (j = n_front; j != NULL; j = j->nextn)
		{
			if (sername == j->service_name)
			{
				cout << "There " << j->client_no << "C" << endl;
				search_normal = 1;
			}
		}
		if (search_normal == 0 && search_vip == 0)
		{
			cout << "There are no customers" << endl;
		}
	}
	else//not contains letters only
	{
		while (true)
		{
			cout << "Service name should contains letters only" << endl;
			cin >> sername;
			if (containsOnlyLetters(sername))
			{
				for (i = v_front; i != NULL; i = i->nextv)
				{
					if (sername == i->service_name)
					{
						cout << "There " << i->client_no << "V" << endl;
						search_vip = 1;
					}
				}
				Nnode* j;
				for (j = n_front; j != NULL; j = j->nextn)
				{
					if (sername == j->service_name)
					{
						cout << "There " << j->client_no << "C" << endl;
						search_normal = 1;
					}
				}
				if (search_normal == 0 && search_vip == 0)
				{
					cout << "There are no customers" << endl;
				}
				break;
			}
		}
	}
	
}

int main()
{
	int clientnum = 1, vipnum = 1;
	system("color 03");
	string choose;
	while (true)
	{
		cout << "Welcome to the bank" << endl;

		cout << "Please choose the service you want :-" << endl;
		for (int i = 0; i < 25; i++)
		{
			cout << "*";
		}
		cout << endl;
		cout << "E - Enqueue \nD - Dequeue \nPA - Print All Clients \nPV - Print VIP Clients \n"
			<< "S - Search\nU - Update \nQ - Quit";
		cout << endl;
		for (int i = 0; i < 25; i++)
		{
			cout << "*";
		}
		cout << endl;
		tst >> choose;
		//cin >> choose;
		string service, phone;

		if (choose == "e" || choose == "E")
		{
			cout << "Enter your phone number : ";
			tst >> phone;
			//cin >> phone;
			if (containsOnlyNumbers(phone) && how_many_num(phone))
			{
				cout << "\nWhat service do you want ? : \n";
				cout << endl;
				cout << "- teller \n- customer_service \n- loans \n";
				tst >> service;
				//cin >> service;
				if (containsOnlyLetters(service) && avilableservices(service))
				{
					if (phone == "01155577889" || phone == "01133366117" || phone == "01122296224")
					{
						cout << "You are customer " << vipnum << "V" << endl;
						venq(vipnum, service, phone);
						vipnum++;
					}
					else
					{
						cout << "You are customer " << clientnum << "C" << endl;
						cenq(clientnum, service, phone);
						clientnum++;
					}
				}
				else//not contains letters only or invalid service
				{
					while (true)
					{
						cout << "Invalid Service" << endl;
						cout << endl;
						cout << "- teller \n- customer_service \n- loans \n";
						tst >> service;
						//cin >> service;
						if (containsOnlyLetters(service) && avilableservices(service))
						{
							if (phone == "01155577889" || phone == "01133366117" || phone == "01122296224")
							{
								cout << "You are customer " << vipnum << "V" << endl;
								venq(vipnum, service, phone);
								vipnum++;
							}
							else
							{
								cout << "You are customer " << clientnum << "C" << endl;
								cenq(clientnum, service, phone);
								clientnum++;
							}
							break;
						}
					}
				}
			}
			else//not contains numbers only and not = 11
			{
				while (true)
				{
					cout << "Phone number should contains 11 numbers only" << endl;
					tst >> phone;
					//cin >> phone;
					if (containsOnlyNumbers(phone) && how_many_num(phone))
					{
						cout << "\nWhat service do you want ? : \n";
						cout << endl;
						cout << "- teller \n- customer_service \n- loans \n";
						tst >> service;
						//cin >> service;
						if (containsOnlyLetters(service) && avilableservices(service))
						{
							if (phone == "01155577889" || phone == "01133366117" || phone == "01122296224")
							{
								cout << "You are customer " << vipnum << "V" << endl;
								venq(vipnum, service, phone);
								vipnum++;
							}
							else
							{
								cout << "You are customer " << clientnum << "C" << endl;
								cenq(clientnum, service, phone);
								clientnum++;
							}
						}

						else//not contains letters only
						{
							while (true)
							{
								cout << "Invalid Service\n" << endl;
								cout << endl;
								cout << "- teller \n- customer_service \n- loans \n";
								tst >> service;
								//cin >> service;
								if (containsOnlyLetters(service) && avilableservices(service))
								{
									if (phone == "01155577889" || phone == "01133366117" || phone == "01122296224")
									{
										cout << "You are customer " << vipnum << "V" << endl;
										venq(vipnum, service, phone);
										vipnum++;
									}
									else
									{
										cout << "You are customer " << clientnum << "C" << endl;
										cenq(clientnum, service, phone);
										clientnum++;
									}
									break;
								}
							}
						}
						break;
					}
				}
			}
		}

		else if (choose == "d" || choose == "D")
		{
			deq();
		}
		else if (choose == "pa" || choose == "PA")
		{
			displayall();
		}
		else if (choose == "pv" || choose == "PV")
		{
			displayvip();
		}
		else if (choose == "s" || choose == "S")
		{
			int kindofsearch;
			cout << "1- Search by phone\n2- Search by service name" << endl;
			tst >> kindofsearch;
			//cin >> kindofsearch;
			if (kindofsearch == 1)
			{
				search_by_phone();
			}
			else if (kindofsearch == 2)
			{
				search_by_sername();
			}
			else
			{
				cout << "Invalid choise" << endl;
			}
		}
		else if (choose == "u" || choose == "U")
		{
			cout << "Enter your phone number : ";
			tst >> phone;
			//cin >> phone;
			if (containsOnlyNumbers(phone) && how_many_num(phone))
			{
				cout << "\nWhat service do you want ? : \n";
				cout << endl;
				cout << "- teller \n- customer_service \n- loans \n";
				tst >> service;
				//cin >> service;
				if (containsOnlyLetters(service) && avilableservices(service))
				{
					cout << "You are VIP customer now " << vipnum << "V" << endl;
					venq(vipnum, service, phone);
					vipnum++;
				}
				else//not contains letters only or invalid service
				{
					while (true)
					{
						cout << "Invalid Service\n" << endl;
						cout << endl;
						cout << "- teller \n- customer_service \n- loans \n";
						cin >> service;
						if (containsOnlyLetters(service) && avilableservices(service))
						{
							cout << "You are VIP customer now " << vipnum << "V" << endl;
							venq(vipnum, service, phone);
							vipnum++;
							break;
						}
					}
				}
			}
			else//not contains numbers only and not = 11
			{
				while (true)
				{
					cout << "Phone number should contains 11 numbers only" << endl;
					cin >> phone;
					if (containsOnlyNumbers(phone) && how_many_num(phone))
					{
						cout << "\nWhat service do you want ? : \n";
						cout << endl;
						cout << "- teller \n- customer_service \n- loans \n";
						cin >> service;
						if (containsOnlyLetters(service) && avilableservices(service))
						{
							cout << "You are customer " << vipnum << "V" << endl;
							venq(vipnum, service, phone);
							vipnum++;
						}

						else//not contains letters only or invalid service
						{
							while (true)
							{
								cout << "Invalid Service\n" << endl;
								cout << endl;
								cout << "- teller \n- customer_service \n- loans \n";
								cin >> service;
								if (containsOnlyLetters(service) && avilableservices(service))
								{
									cout << "You are customer " << vipnum << "V" << endl;
									venq(vipnum, service, phone);
									vipnum++;
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
		else if (choose == "q" || choose == "Q")
		{
		    tst.close();
			return 0;
		}
		else
		{
			cout << "Invalid Choise" << endl;
		}
		cout << endl;
	}
}