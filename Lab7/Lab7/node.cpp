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
		strcpy_s(str, strlen(st)+1, st);
	}
	catch (...)
	{
		msg.mess(my_mess::ERR_TO_LONG_NAME);
	}
}

node & node::operator=(const node & ob)
{
	if (this == &ob)
		return *this;

	(my_coord &)(*this) = (my_coord &)ob;
	numb = ob.numb;
	try
	{
		strcpy_s(str, strlen(ob.str) + 1, ob.str); //Tutaj przy kopiowaniu nzawy nie jest potrzebne wyczyszczenie str (memset) poniewaz ostatni znak i tak zawsze jest \0
	}
	catch (...)
	{
		msg.mess(my_mess::ERR_TO_LONG_NAME);
	}

	return *this;
}

bool node::operator == (const node &ob) const
{
	if ((my_coord &)(*this) == (my_coord &)(ob))
		if (numb == ob.numb)
			if (Compare_Text(str, ob.str))
				return true;
	return false;
}

istream & operator>>(istream & strumien, node & ob)
{
	cout << "Podaj numer wierzcholka: ";
	strumien >> ob.numb;
	cout << "Podaj nazwe wierzcholka (max 512): ";

	strumien >> ws >> ob.str;
	
	strumien >> (my_coord &)ob;
	return strumien;
}

ostream & operator<<(ostream & strumien, const node & ob);

ofstream & operator<<(ofstream & plik, const node &ob);
ifstream & operator>>(ifstream & plik, node &ob);

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