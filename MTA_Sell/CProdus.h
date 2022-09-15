#pragma once
#include<string>
#include <vector>
#include "CCustom.h"
using namespace std;
class CProdus
{
	string denumire;
	string descriere;
	float pret;
	int cantitate;
	vector<CCustom> personalizari;
	vector<string> magazine;
public:
	
	CProdus(string denumire,string descriere, float pret, int cantitate, vector<CCustom> personalizari):denumire(denumire),descriere(descriere),pret(pret),cantitate(cantitate), personalizari(personalizari) {}

	string get_denumire() { return denumire; }
	string get_descriere() { return descriere; }
	float get_pret() { return pret; }
	int get_cantitate() { return cantitate; }
	vector<string>get_magazine() { return magazine; }
	vector<CCustom>get_personalizari() { return personalizari; }
	
	
	int& set_catitate() { return cantitate; }
	vector<string>& set_magazine() { return magazine; }
	int& set_cantitate() { return cantitate; }
	vector<CCustom>& set_personalizari() { return personalizari; }
	~CProdus(){}
	
};

