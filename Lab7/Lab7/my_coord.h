#pragma once
#include "my_mess.h"
#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push, 1)
class my_coord
{
	double *pcoord;  //pcoord[0] -; pcoord[1] - y
	my_mess msg;
public:
	my_coord() { alloc(); pcoord[0] = pcoord[1] = 0; }
	my_coord(double x, double y);
	//my_coord(const my_coord & ob); // Konstruktor Kopiujacy Niepotrzebny?
	~my_coord() { if (pcoord) delete[] pcoord; }

	my_coord & operator=(const my_coord & ob);
	bool operator==(const my_coord &ob) const;
	friend istream & operator>>(istream & strumien, my_coord & ob);
	friend ostream & operator<<(ostream & strumien, const my_coord & ob);

	friend ofstream & operator<<(ofstream & plik, const my_coord &ob);
	friend ifstream & operator>>(ifstream & plik, my_coord &ob);

	void FunExcel(ofstream & plik);
private:
	void alloc();
};
#pragma pack(pop)