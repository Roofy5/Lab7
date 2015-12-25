#pragma once

class my_mess
{
public:
	enum MY_MESSAGE
	{
		WARN_INTERF_ERROR, //wybranie opcji 0
		ERR_ALLOC_MEM,     //b��d alokacji pami�ci
		WARN_ARR_FULL,     //tablica jest wypelniona (last > ndim)
		WARN_ARR_EMPT,     //tablica jest pusta (last = 0)
		WARN_ARR_UNKN,     //niepoprawny kod dzia�ania (interfejs)
		WARN_ARR_NULL,	   //wskaznik dat = NULL
		WARN_CREATE_FILE,  //blad przy otworzeniu pliku do zapisu
		WARN_OPEN_FILE,	   //blad przy twoarciu pliku do odczytu
		ERR_LOAD_FILE,	   //blad przy odczycie
		ERR_SAVE_FILE,     //blad przy zapisie
		ERR_TO_LONG_NAME,  //za dluga nazwa wierzcholka  >dl_nazwa
		TOT_NUMB                 //og�lna ilo�� komunikat�w
	};

	static char *strtab[TOT_NUMB];  //tablica tekstowa komunikat�w

public:
	void mess(enum MY_MESSAGE ms);    //Przy wywo�ani tej funkcji na ekran //pozostaje wyprowadzony komunikat. Je�li to b��d, obliczenia trzeba //sko�czy�, je�li nie � kontynuowa�. ms � sk�adowa enumeration, kt�ra podaje //numer komunikatu
};
