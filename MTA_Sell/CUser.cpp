#include "CUser.h"
#include"Error_File.h"
ostream& operator<<(ostream& out, CUser& user)
{
    out << user.username << " " << user.password << "\n";
    return out;
}
void CUser::afiseaza_istoric()
{
    string filename = username + ".txt";
	
    ifstream file(filename);
    if (file.is_open())
    {
        while (file.good())
        {
            string tmp_comanda;
            getline(file, tmp_comanda, '\n');
            cout << tmp_comanda << endl;
        }
    }
    else
    {
        throw new Error_File("Eroare la deschiderea fisierului.");
    }
}