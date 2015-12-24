#pragma once

#include "my_vect.h"
#include "my_coord.h"
#include "node.h"

class my_interf
{
public:
	enum MY_INTERF //Zmiana na public z private
	{
		MY_INTERF_ERROR, //Wprowadzenie wart 0

		MY_INTERF_PUSH,
		MY_INTERF_POP,
		MY_INTERF_DISP,
		MY_INTERF_FIND,

		MY_INTERF_REMOVE, //Dodane - usuniecie z tablicy
		MY_INTERF_SAVE,	  //Dodane - zapis do pliku
		MY_INTERF_LOAD,		//Dodane - odczyt z pliku

		MY_INTERF_FINISH,
		MY_INTERF_TOT
	};

private:
	//my_vect<my_coord> vect;
	my_vect<node> vect;
	int MAX_INTERF_CHAR;
	char str_interf[MY_INTERF_TOT][512];  //komunikaty, wyœwietlane na monitorze
	my_mess msg;
	
public:
	bool run;

	my_interf();
	my_interf(size_t dim);
	void menu();
	void push();
	void pop();
	void disp();
	void find();

	void remove();
	void save();
	void load();

	void finish();
	void defaul();
};
