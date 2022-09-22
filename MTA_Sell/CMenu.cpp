#include<iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <chrono>
#include <thread>
#include "CMenu.h"
#include "CProdus.h"
#include "CUser.h"
#include "CMagazin.h"
#include "Error_File.h"
#include "Error_Auth.h"
#include "Error_Product.h"

using namespace std;
#define DIM_X 35
#define DIM_Y 9

vector<CUser> utilizatori;
CUser Utilizator_curent;
vector<CMagazin> magazine;
vector<CProdus> AllProducts;
ofstream log_file("log.txt");

CMenu* CMenu::instance = nullptr;

CMenu* CMenu::getInstance()
{
	if (instance == nullptr)
	{
		instance = new CMenu();
	}
	return instance;
}
void CMenu::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
void welcome()
{
	system("cls");
	string mesaj = "Welcome to MTA Sell.";
	string credit = "Made by Sandu Dragos.";
	for (int i = 0; i < DIM_X; i++)
	{
		cout << "@";
	}
	cout << endl;
	for (int i = 0; i < DIM_Y; i++, cout << endl)
	{
		for (int j = 0; j < DIM_X; j++)
		{
			if (j == 0 || j == DIM_X - 1)
				cout << "@";
			else
			{
				if (i == DIM_Y / 2 && j == DIM_X / 2 - mesaj.length() / 2)
				{
					cout << mesaj;
					j += mesaj.length() - 1;
				}
				else
				{
					if (i == DIM_Y - 1 && j == DIM_X - credit.length() - 2)
					{
						cout << credit;
						j += credit.length() - 1;
					}
					else
						cout << " ";
				}
			}
		}

	}
	for (int i = 0; i < DIM_X; i++)
	{
		cout << "@";
	}
}
bool check_username(string username)
{
	for (int i = 0; i < utilizatori.size(); i++)
	{
		if (utilizatori[i].get_name() == username)
			return true;
	}
	return false;
}
bool verifica_utilizator(string name, string pass)
{
	for (auto it = utilizatori.begin(); it != utilizatori.end(); it++)
	{
		if ((*it).get_name() == name && (*it).get_pass() == pass)
		{
			CUser utilizator(name, pass);
			Utilizator_curent = utilizator;
			return true;
		}
	}
	return false;
}
void read_password(string& password)
{
	char pass[26];
	int p = 0;
	char ch;
	do {
		ch = _getch();
		if (ch == '\b' && p > 1)
		{
			pass[--p] = '\0';
			cout << "\b \b";
		}
		else
		{
			pass[p] = ch;
			if (pass[p] != 13) {
				cout << "*";
			}
			p++;
		}

	} while (pass[p - 1] != 13);
	pass[p - 1] = '\0';
	password = pass;
}
void Log_in(string& tmp_name, string& tmp_pass)
{
	string name;
	cout << "Username: ";
	cin >> name;
	cout << "Password: ";
	string pass;
	read_password(pass);

	tmp_name = name;
	tmp_pass = (string)pass;
}

void Credentiale()
{
	cout << "\nCe operatiune doriti sa efectuati?\n1. Login.\n2. Crearea unui cont nou de utilizator.\n";
	int nr; cin >> nr;
	if (nr == 1)
	{
		cout << "\nPentru a continua va rugam sa va introduceti datele de logare:\n";
		string name, pass;
		Log_in(name, pass);
		int count = 1;
		if (verifica_utilizator(name, (string)pass) == true)
		{
			cout << endl << "V-ati autentificat cu succes!\n";
			cout << "Meniul pentru utilizatori se incarca...";
			std::this_thread::sleep_for(std::chrono::milliseconds(2500));
			system("cls");
		}
		else
		{
			while (count != 3)
			{
				cout << "\nUsername-ul sau parola sunt gresite." << endl;
				cout << "Mai aveti " << 3 - count << " incercari." << endl;
				Log_in(name, pass);
				if (verifica_utilizator(name, pass) == true)
				{
					cout << "\nV-ati autentificat cu succes!\n";
					cout << "Meniul pentru utilizatori se incarca...";
					std::this_thread::sleep_for(std::chrono::milliseconds(2500));
					system("cls");
					break;
				}
				else
					count++;
			}
			if (count == 3)
			{
				cout << "\nIncercarile dumneavoastra de autentificare au esuat. Va rugam sa incercati mai tarziu.\n";
				throw new Error_Auth("Mai mult de 3 incercari de autentificare.");
			}

		}
	}
	else
	{
        int count=0;
		string aux_name, aux_pass;
		do
		{
            if(count>0)
                {
                    cout << "\nAcest Username a fost deja folosit. Va rugam sa incercati altul.\n";
                }
			cout << "Introduceti Username-ul contului:\n";
			cin >> aux_name;
			cout << "Introduceti parola contului:\n";
			read_password(aux_pass);
            count++;
		}while (check_username(aux_name));
		ofstream file;
		file.open("Users.txt", ofstream::app);
		file << endl << aux_name + " " + aux_pass;
		cout << "\nContul a fost creat cu succes.\n";
		CUser utilizator(aux_name, aux_pass);
		Utilizator_curent = utilizator;
	}

}
void read_users(const string filename)
{
	ifstream file(filename);
	string name, pass;
	if (file.is_open())
	{
		while (file.good())
		{
			file >> name >> pass;
			CUser tmp_user(name, pass);
			utilizatori.push_back(tmp_user);
		}
	}
	else
	{
		throw new Error_File("Eroare la deschiderea fisierului.");
	}
	file.close();
}

void read_products(string filenameMagazine)
{
	ifstream f(filenameMagazine);
	string magazin, filename;
	if (f.is_open())
	{
		while (f.good())
		{
		
			f >> magazin;
			filename =magazin+ ".txt";
			vector<CProdus> produse;
			ifstream file(filename);
			int k = 0;
			if (file.is_open())
			{
				while (file.good())
				{
					string denumire, descriere, tmp;
					vector <CCustom> personalizari;
					float pret;
					int cantitate;
				
					getline(file, denumire, '|');
					if (k >= 1)
						denumire = denumire.substr(1, denumire.size() - 1);
					getline(file, descriere, '|');
					getline(file, tmp, '|');
					pret = stof(tmp);
					getline(file, tmp, '|');
					cantitate = stoi(tmp);
				
					while (file.peek() != '\n' && file.good())
					{
						getline(file, tmp, ',');
						CCustom aux(tmp);
						personalizari.push_back(aux);
					}
					CProdus tmp_produs (denumire, descriere, pret, cantitate, personalizari);
					produse.push_back(tmp_produs);
					k++;
				}
			}
			else
			{
				throw new Error_File("Eroare la deschiderea fisierului.");
			}
			file.close();
			CMagazin tmp_magazin(magazin, produse);
			magazine.push_back(tmp_magazin);
		}
	}
	else
	{
		throw new Error_File("Eroare la deschiderea fisierului.");
	}
	f.close();
	
}


bool unique_product(string denumire,string magazin,int cantitate)
{
	int count = 0;
	
	for (int j = 0; j < AllProducts.size(); j++)
	{
		if (AllProducts[j].get_denumire() == denumire)
		{
			AllProducts[j].set_magazine().push_back(magazin);
			AllProducts[j].set_catitate() += cantitate;
			return false;
		}
	}
	return true;

}

void Meniu_Produse()
{
	for (int i = 0; i < magazine.size(); i++)
	{
		vector<CProdus>produse = magazine[i].get_produse();
		for (int j = 0; j < produse.size(); j++)
		{
			produse[j].set_magazine().push_back(magazine[i].get_denumire());
			
			if (unique_product(produse[j].get_denumire(),magazine[i].get_denumire(),produse[j].get_cantitate()))
			{
				AllProducts.push_back(produse[j]);
			}
		}
	}
}
void print_Meniu()
{
	for (int i = 0; i < AllProducts.size(); i++)
	{
		vector<string>tmp_mag = AllProducts[i].get_magazine();
		cout << i + 1 << ". " << AllProducts[i].get_denumire() << "|"
			<< AllProducts[i].get_pret() << "|" << AllProducts[i].get_cantitate() << "|Disponibil in " << tmp_mag.size() << " magazine:";


		for (int j = 0; j < tmp_mag.size(); j++)
		{
			if (j < tmp_mag.size() - 1)
				cout << tmp_mag[j] << ", ";
			else
				cout << tmp_mag[j];
		}
		cout << endl;
	}
}
CMagazin find_store(string denumire_magazin)
{
	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i].get_denumire() == denumire_magazin)
			return magazine[i];
	}
}
CProdus find_product(CMagazin store, string denumire_produs)
{
	vector<CProdus>produse = store.get_produse();
	for (int i = 0; i < produse.size(); i++)
	{
		if (produse[i].get_denumire() == denumire_produs)
			return produse[i];
	}
}
bool check_allCustoms(CProdus produs)
{
	vector<CCustom>personalizari = produs.get_personalizari();
	for (auto custom : personalizari)
	{
		if (custom.get_isOn() == false)
			return true;
	}
	return false;
}

void personalizeaza_produsul(CProdus& produs_ales)
{
	vector<CCustom> personalizari = produs_ales.get_personalizari();
	log_file << "Userul " << Utilizator_curent.get_name() << " a intrat in meniul de personalizare a produsului" << endl;

	for (int i = 0; i < personalizari.size(); i++)
	{
		cout << i + 1 <<". " <<personalizari[i].get_option() << endl;
	}
	while (check_allCustoms(produs_ales))
	{
		cout << "Selecteaza optiunea de personalizare dorita de mai jos.\nDaca doresti sa iesi din meniul de personalizari apasa 0.\n";
		int opt_custom;
		cin >> opt_custom;
		if (opt_custom == 0)
			break;
		
		if (personalizari[opt_custom - 1].get_isOn() == true)
			cout << "Ati configurat deja aceasta pesonalizare.\n";
		else
		{
			log_file << "Userul " << Utilizator_curent.get_name() << " a selectat optiunea de personalizare " << personalizari[opt_custom - 1].get_option() << endl;
			cout << "Introduceti " << personalizari[opt_custom - 1].get_option() << " dorita:";

			string details;
			cin >> details;
			personalizari[opt_custom - 1].set_details() = details;
			personalizari[opt_custom - 1].set_IsOn() = true;
			produs_ales.set_personalizari() = personalizari;
		}
	}
	produs_ales.set_personalizari() = personalizari;
}

void selecteaza_produse()
{
	vector<CProdus>produse_comanda;
	float pret_comanda = 0;
	bool withCard = false;
	string adresa_comanda;
	bool flag = false;
	while (true)
	{
		int optiune;
		cout << "Pentru a comanda te rugam sa introduci !NUMARUL! produsului. Apasa 0 daca nu doresti nimic.\n";
		cin >> optiune;
		if (optiune == 0)
		{
			break;
		}
		else
		{
			if (optiune > 0 && optiune <= AllProducts.size())
			{
				
				string denumire_produs = AllProducts[optiune - 1].get_denumire();
				log_file<<"Userul "<<Utilizator_curent.get_name()<<" a selectat produsul " << denumire_produs << endl;
				cout << "Ati selectat produsul: " << denumire_produs <<endl;
				string magazin_ales = "";
				
				if (AllProducts[optiune - 1].get_magazine().size() > 1)
				{
					cout << "Introduceti numele magazinului din care doriti sa comandati produsul: ";
					
					cin >> magazin_ales;
					log_file<< "Userul " << Utilizator_curent.get_name() << " a introdus magazinul " << magazin_ales << endl;
				}
				
				int cantitate;
				cout << "Introdu cantitatea dorita: ";
				cin >> cantitate;
				log_file << "Userul " << Utilizator_curent.get_name() << " a introdus cantitatea   " << cantitate << endl;
				
				if (cantitate > 0 && cantitate <= AllProducts[optiune - 1].get_cantitate())
				{
					flag = true;
					CMagazin tmp_magazin;
					string tmp_denumire_magazin = "";
					int k = 0;
					while (tmp_denumire_magazin=="")
					{
						if (k >= 1)
						{
							cout << "Nu ati introdus corect numele magazinului. Va rugam introduceti din nou.";
							cin >> magazin_ales;
						}
						if (k >= 4)
							throw new Error_Product("Magazinul produsului a fost introdus gresit de prea multe ori.");
						if (magazin_ales == "")
						{
							tmp_magazin = find_store(AllProducts[optiune-1].get_magazine()[0]);
							break;
						}
						else
						{
							tmp_magazin = find_store(magazin_ales);
							tmp_denumire_magazin = tmp_magazin.get_denumire();
						}
						k++;
					}
					
					
					CProdus produs_ales = find_product(tmp_magazin, denumire_produs);
					produs_ales.set_cantitate() = cantitate;
					
					pret_comanda += cantitate * produs_ales.get_pret();
					
					
					
					//de verificat personalizarile care sunt disponibile
					
					personalizeaza_produsul(produs_ales);
					
					produse_comanda.push_back(produs_ales);
					AllProducts[optiune - 1].set_cantitate() -= cantitate;
					
					cout << "Produsul a fost adaugat in cos.\n";
				}
				else
				{
					cout << "Cantitatea introdusa nu este disponibila.\n";
				}
			}
			else
			{
				cout << "Optiunea introdusa nu este valida.\n";
			}
		}
	}
	if (flag == true)
	{
		cout << "Doresti sa platesti cu cardul? (1. Da /2. Nu)";
		int opt_card;
		cin >> opt_card;
		if (opt_card == 1)
		{
			withCard = true;
		}
		log_file << "Userul " << Utilizator_curent.get_name() << " a selectat plata cu cardul" << withCard << endl;
		cout << "Introduceti adresa de livrare: ";
		cin >> adresa_comanda;

		log_file << "Userul " << Utilizator_curent.get_name() << " a introdus adresa de livrare " << adresa_comanda << endl;
		CComanda comanda_client(adresa_comanda, pret_comanda, withCard, produse_comanda);
		Utilizator_curent.set_comenzi().push_back(comanda_client);
		cout << "Comanda a fost plasata cu succes. O puteti gasi accesand istoricul comenzilor dumneavoastra.\n";
		log_file << "Userul " << Utilizator_curent.get_name() << " a plasat comanda cu succes." << endl;

		string istoric_utilizator = Utilizator_curent.get_name() + ".txt";
		ofstream istoric(istoric_utilizator, ofstream::app);
		istoric << comanda_client << endl;
		istoric.close();
	}
	else
	{
		cout << "Nu ati introdus niciun produs in cosul de cumparaturi. Va uram o zi placuta in continure.";
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	system("cls");
	
}
void User_Menu()
{
	Credentiale();
	int optiune;
	cout << "Te rugam sa selectezi una din optiunile de mai jos:\n1. Afiseaza produsele disponibile.\n2. Afiseaza istoricul de comenzi.\n";
	cin >> optiune;
	switch (optiune)
	{

	case 1:
	{
		log_file << "Userul " << Utilizator_curent.get_name() << " a ales sa se afiseze produsele." << endl;
		print_Meniu();
		selecteaza_produse();
		break;
	}
		
	case 2:
		log_file << "Userul " << Utilizator_curent.get_name() << " a ales sa afiseze istoricul comenzilor." << endl;
		Utilizator_curent.afiseaza_istoric();
		cout << "Apasati o tasta pentru a continua.";
		string ch;
		cin >> ch;
		break;
	}
	
	
}

void CMenu::running()
{

	read_products("Nume_Magazine.txt");
	read_users("Users.txt");
	Meniu_Produse();

	while (true)
	{
		welcome();
		cout << "\nAlegeti o optiune din cele de mai jos:\n1.Intra in aplicatie.\n0.Exit.\n";
		int choice;
		cin >> choice;
		int pas = 0;
		switch (choice)
		{
			pas++;
			log_file << "Pasul " << pas << ":\n";
		case 1:
			log_file << "Userul " << Utilizator_curent.get_name() << " a ales sa intre in aplicatie." << endl;
			User_Menu();
			break;
		case 0:
			log_file << "Userul " << Utilizator_curent.get_name() << " a ales sa iasa din aplicatie." << endl;
			cout << "Sa aveti o zi buna in continuare!";
			break;
		}
		if (choice == 0)
			break;
	}
}
