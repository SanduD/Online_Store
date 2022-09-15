#include "CComanda.h"
ostream& operator<<(ostream& out, CComanda& comanda)
{
	out << "Produse comanda: ";
	vector<CProdus> produse = comanda.produse;
	for (int i = 0; i < produse.size(); i++)
	{
		out <<i+1<<". "<<produse[i].get_denumire() << " - " << produse[i].get_cantitate()<<" | ";
	}
	out << "Adresa de livrare: " << comanda.adresa;
	out << " | Pret total: " << comanda.pret_total;
	out << " | Cu card: " << comanda.withCard ;
	return out;
}