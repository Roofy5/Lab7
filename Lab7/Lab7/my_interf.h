#pragma once

#include "my_vect.h"
#include "my_coord.h"
#include "node.h"
#include "CExcel_class.h"

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

		MY_INTERF_INSERT, //Dodane - dodanie na pozycje
		MY_INTERF_INSERTTABLE, //Dodane - dodanie tablicy obiektow
		MY_INTERF_REMOVE, //Dodane - usuniecie z tablicy
		MY_INTERF_REMOVEALL, //Dodane - usuniecie wszystkiego
		MY_INTERF_MODIFY, //Dodane - modyfikowanie obiektu
		MY_INTERF_SAVE,	  //Dodane - zapis do pliku
		MY_INTERF_LOAD,		//Dodane - odczyt z pliku
		MY_INTERF_EXCEL,  //Dodane - zapis do pliku CSV i uruchomienie Excela

		MY_INTERF_FINISH,
		MY_INTERF_TOT
	};

private:
	//my_vect<my_coord> vect;
	my_vect<node> vect;
	int MAX_INTERF_CHAR;
	char str_interf[MY_INTERF_TOT][512];  //komunikaty, wy�wietlane na monitorze
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

	void insert();
	void insertTable();
	void remove();
	void removeAll();
	void modify();
	void save();
	void load();
	void excel();

	void finish();
	void defaul();
};
