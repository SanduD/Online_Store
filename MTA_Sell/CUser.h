#pragma once
#include <string>
#include <iostream>
#include <vector>
#include<fstream>
#include "CComanda.h"
using namespace std;

class CUser
{
	string username;
	string password;
	vector<CComanda> comenzi;
public:
	CUser() {}
	CUser(string name, string pass) :username(name), password(pass){}
	string get_name() { return username; }
	string get_pass() { return password; }
	
	void afiseaza_istoric();
	vector<CComanda>get_comenzi() { return comenzi; }

	vector<CComanda>& set_comenzi() { return comenzi; }
	friend ostream& operator <<(ostream& out, CUser& user);
};

