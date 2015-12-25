#pragma once
#include "my_coord.h"
#include "node.h"

// Ta klasa obsluguje operacje zwiazne z zapisaniem pliku w formacie CSV
// oraz zawiera obsluge otwarcia Excela
// Nie uzywalem tutaj komunikatow my_mess, poniewaz stwierdzilem, ze niepotrzebnie zasmiece tamta klase
// komunikaty sa scisle powiazane tylko z ta klasa
// Caly program uzywa zwyklego jedno-bajtowego kodowania, nie wiem jak sie zachowa w przypadku nazw w wchar_t

class CExcel_class
{
public:
	ofstream & CreateOfstream(ofstream & strumien, my_coord & ob);
	ofstream & CreateOfstream(ofstream & strumien, node & ob);
	void SpawnExcel(char * file);
private:
	void ChangePoint(double a, char * wsk, int dlugosc); //Zmienia kropke w liczbie double na przecinek - Excel obsluguje przecinki a nie kropki
	bool FindExcelPath(char * path); //Stara sie znalezc sciezke do Excel.exe przeszukujac rejestr
};