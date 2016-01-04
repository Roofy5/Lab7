#include "stdafx.h"
#include "node.h"
#include <iomanip>

node::node() : my_coord()
{
	numb = 0;
	strcpy_s(str, 7, "NoName");
}

node::node(int nb, char *st, double xx, double yy) : my_coord(xx, yy)
{
	numb = nb;
	try
	{
		if (strlen(str) + 1 > dl_nazwa)
			throw 1;
		strcpy_s(str, strlen(st)+1, st);
	}
	catch (...)
	{
		msg.mess(my_mess::ERR_TO_LONG_NAME);
	}
}

/*node::node(const node &ob)
{
}*/

node & node::operator=(const node & ob)
{
	if (this == &ob)
		return *this;

	(my_coord &)(*this) = (my_coord &)ob;
	numb = ob.numb;
	try
	{
		if (strlen(str) + 1 > dl_nazwa)
			throw 1;

		memset(str, 0, dl_nazwa);
		strcpy_s(str, strlen(ob.str) + 1, ob.str);
	}
	catch (...)
	{
		msg.mess(my_mess::ERR_TO_LONG_NAME);
	}

	return *this;
}

bool node::operator == (const node &ob) const
{
	/* Wyszukiwanie identycznego obiektu
	if ((my_coord &)(*this) == (my_coord &)(ob))
		if (numb == ob.numb)
			if (Compare_Text(str, ob.str))
				return true;
	*/

	if (numb == ob.numb)
		return true;
	return false;
}

istream & operator>>(istream & strumien, node & ob)
{
	char liczba[32];
	cout << "Podaj numer wierzcholka: ";
	strumien >> liczba;
	ob.numb = atoi(liczba);
	cout << "Podaj nazwe wierzcholka (max " << dl_nazwa << "): ";

	strumien >> ws >> setw(dl_nazwa) >> ob.str;

	strumien.clear();
	cin.ignore(10000, '\n'); //zabezpeczenie przed wpisaniem >32 znakow
	strumien >> (my_coord &)ob;
	return strumien;
}

ostream & operator<<(ostream & strumien, const node & ob)
{
	strumien << setw(4) << right << ob.numb << ". " << left << setw(10) << ob.str << " " << (my_coord &)ob;
	return strumien;
}

ofstream & operator<<(ofstream & plik, const node &ob)
{
	int dl = dl_nazwa;
	plik.write((char *)&dl, sizeof(int)); //Zapisanie wielkosci tablicy z define
	plik.write((char *)&ob.numb, sizeof(int));
	plik.write((char *)ob.str, dl_nazwa * sizeof(char));
	plik << (my_coord &)ob;
	//plik.good sprawdza my_coord

	return plik;
}

ifstream & operator>>(ifstream & plik, node &ob)
{
	int temp_dl = 0;
	plik.read((char *)&temp_dl, sizeof(int)); //Wczytanie wielkosci tablicy z define
	if (temp_dl != dl_nazwa) //Zabezpieczenie przed roznymi rozmiarami tablic
	{
		cout << "Niepoprawny rozmiar tablicy str (node).\nDefine zapisany do pliku = " << temp_dl;
		cout << "\nDefine w programie = " << dl_nazwa << endl;
		ob.msg.mess(my_mess::ERR_LOAD_FILE);
	}

	plik.read((char *)&ob.numb, sizeof(int));
	plik.read((char *)ob.str, dl_nazwa*sizeof(char));
	plik >> (my_coord &)ob;
	//plik.good sprawdza my_coord

	return plik;
}

bool node::Compare_Text(const char * a, const char * b) const
{
	int dl1 = strlen(a) + 1;
	int dl2 = strlen(b) + 1;

	if (dl1 != dl2)
		return false;

	for (int i = 0; i < dl1; i++)
	{
		if (a[i] != b[i])
			return false;
	}

	return true;
}