#include "stdafx.h"
#include "my_mess.h"

#include <iostream>

using namespace std;

char *my_mess::strtab[] =
{
	"W  Nieznany kod",				  //WARN_INTERF_ERROR
	"E  memory alloc error",          //ERR_ALLOC_MEM
	"W  array is full",               //WARN_ARR_FULL
	"W  array is empty",              //WARN_ARR_EMPT
	"W  niepoprawny kod operacji",    //WARN_ARR_UNKN
	"W  array = NULL",				  //WARN_ARR_NULL,
	"W	nie moge otworzyc pliku do zapisu",  //WARN_CREATE_FILE
	"W	nie moge otworzyc pliku do odczytu", //WARN_OPEN_FILE
	"E  Blad przy wczytywaniu pliku",		 //ERR_LOAD_FILE
	"E  Za dluga nazwa wierzcholka"			 //ERR_TO_LONG_NAME
};

void my_mess::mess(enum MY_MESSAGE ms)
{
	if (strtab[ms][0] == 'E')
	{
		cout << "ERROR: " << &strtab[ms][1] << endl;
		system("pause");
		exit(1);
	}
	else if (strtab[ms][0] == 'W')
	{
		cout << "WARNING: " << &strtab[ms][1] << endl;
	}
}
