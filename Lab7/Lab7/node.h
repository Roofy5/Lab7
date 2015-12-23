#pragma once
#include "my_coord.h"

class node : public my_coord
{
	int numb;	//numer wierzcholka
	char str[512]; //nazwa wierzcholka
	my_mess msg;
public:
	node();
	node(int nb, char *st, double xx, double yy);

	node & operator=(const node & ob);
	bool operator==(const node &ob) const;

	friend istream & operator>>(istream & strumien, node & ob);
	friend ostream & operator<<(ostream & strumien, const node & ob);

	friend ofstream & operator<<(ofstream & plik, const node &ob);
	friend ifstream & operator>>(ifstream & plik, node &ob);

private:
	bool Compare_Text(const char * a, const char * b) const;
};