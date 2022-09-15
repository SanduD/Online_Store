#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CProdus.h"
using namespace std;
class CMagazin
{
	string denumire;
	vector<CProdus>produse;
	
public:
	CMagazin() {};
	CMagazin(string denumire, vector<CProdus>produse) :denumire(denumire), produse(produse) {}
	string get_denumire() { return denumire; }
	vector<CProdus>get_produse() { return produse; }
	~CMagazin() {}
};