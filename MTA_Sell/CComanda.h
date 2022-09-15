#pragma once
#include <vector>
#include <string>	
#include <iostream>
#include "CProdus.h"
using namespace std;
class CComanda
{
	vector<CProdus> produse;
	float pret_total;
	bool withCard;
	string adresa;
	
public:
	CComanda(){}
	CComanda(string adresa, float pret, bool withCard, vector<CProdus> produse) : adresa(adresa), pret_total(pret), withCard(withCard), produse(produse) {}
	string get_adresa() { return adresa; }
	float get_pret_total() { return pret_total; }
	bool get_withCard() { return withCard; }
	vector<CProdus> get_produse() { return produse; }
	
	friend ostream& operator<<(ostream& out, CComanda& comanda);
	~CComanda() {}
	
};

