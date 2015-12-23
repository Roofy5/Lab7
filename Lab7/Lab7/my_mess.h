#pragma once

class my_mess
{
public:
	enum MY_MESSAGE
	{
		WARN_INTERF_ERROR, //wybranie opcji 0
		ERR_ALLOC_MEM,     //b³¹d alokacji pamiêci
		WARN_ARR_FULL,     //tablica jest wypelniona (last > ndim)
		WARN_ARR_EMPT,     //tablica jest pusta (last = 0)
		WARN_ARR_UNKN,     //niepoprawny kod dzia³ania (interfejs)
		WARN_ARR_NULL,	   //wskaznik dat = NULL
		WARN_CREATE_FILE,  //blad przy otworzeniu pliku do zapisu
		WARN_OPEN_FILE,	   //blad przy twoarciu pliku do odczytu
		ERR_LOAD_FILE,	   //blad przy odczycie
		ERR_TO_LONG_NAME,  //za dluga nazwa wierzcholka  >512
		TOT_NUMB                 //ogólna iloœæ komunikatów
	};

	static char *strtab[TOT_NUMB];  //tablica tekstowa komunikatów

public:
	void mess(enum MY_MESSAGE ms);    //Przy wywo³ani tej funkcji na ekran //pozostaje wyprowadzony komunikat. Jeœli to b³¹d, obliczenia trzeba //skoñczyæ, jeœli nie – kontynuowaæ. ms – sk³adowa enumeration, która podaje //numer komunikatu
};
