#include "stdafx.h"
#include "my_coord.h"
#include <iostream>

using namespace std;

my_coord::my_coord(double x, double y)
{
	alloc();
	pcoord[0] = x;
	pcoord[1] = y;
}

/*my_coord::my_coord(const my_coord & ob)
{
	if (ob.pcoord)
	{
		alloc();
		pcoord[0] = ob.pcoord[0];
		pcoord[1] = ob.pcoord[1];
	}
	else
		pcoord = NULL;
}*/

/*my_coord::~my_coord() //inline w klasie
{
	if (pcoord)
		delete[] pcoord;
}*/

void my_coord::alloc()
{
	try
	{
		pcoord = new double[2];
	}
	catch (std::bad_alloc e)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}
}

my_coord & my_coord::operator=(const my_coord & ob)
{
	if (this == &ob)
		return *this;

	if (pcoord)
	{
		delete[]pcoord;
		pcoord = NULL;
	}

	if (ob.pcoord)
	{
		alloc();
		pcoord[0] = ob.pcoord[0];
		pcoord[1] = ob.pcoord[1];
	}
	else
	{
		pcoord = NULL;
	}

	return *this;
}

bool my_coord::operator==(const my_coord &ob) const
{
	if (pcoord && ob.pcoord)
	{
		if (pcoord[0] == ob.pcoord[0] && pcoord[1] == ob.pcoord[1])
			return true;
		else
			return false;
	}
	return false;
}

istream & operator>>(istream & strumien, my_coord & ob)
{
	if (ob.pcoord)
	{
		cout << "Podaj x: ";
		strumien >> ob.pcoord[0];
		cout << "Podaj y: ";
		strumien >> ob.pcoord[1];
	}
	return strumien;
}

ostream & operator<<(ostream & strumien, const my_coord & ob)
{
	if (ob.pcoord)
	{
		strumien << "x: " << ob.pcoord[0] << "\ty: " << ob.pcoord[1];
	}
	return strumien;
}

ofstream & operator<<(ofstream & plik, const my_coord &ob)
{
	if (ob.pcoord)
	{
		plik.write((char*)ob.pcoord, 2*sizeof(double)); 
		if (!plik.good())
		{
			my_mess msg;
			msg.mess(my_mess::ERR_LOAD_FILE);
		}
	}
	return plik;
}

ifstream & operator>>(ifstream & plik, my_coord &ob)
{
	if (!ob.pcoord)
	{
		ob.alloc();
	}

	plik.read((char *)ob.pcoord, 2 * sizeof(double));
	if (!plik.good())
		ob.msg.mess(my_mess::ERR_LOAD_FILE);
	return plik;
}