#include "stdafx.h"
#include "my_interf.h"
#include <iostream>
#include <algorithm>

//Odkomentowac jezeli chcemy uzywac algorytmu find z <algorithm>
//#define FIND_ALGORITHM 

//Odkomentowac jezeli chcemy uzywac obslugi MFC
#define MFC_Dialogs

using namespace std;

my_interf::my_interf(size_t dim)
{
	MAX_INTERF_CHAR = 512;
	//sprintf_s(str_interf[MY_INTERF_ERROR], MAX_INTERF_CHAR*sizeof(char), "%d - error", MY_INTERF_ERROR);
	sprintf_s(str_interf[MY_INTERF_PUSH], MAX_INTERF_CHAR*sizeof(char), "%d - push", MY_INTERF_PUSH);
	sprintf_s(str_interf[MY_INTERF_POP], MAX_INTERF_CHAR*sizeof(char), "%d - pop", MY_INTERF_POP);
	sprintf_s(str_interf[MY_INTERF_DISP], MAX_INTERF_CHAR*sizeof(char), "%d - disp", MY_INTERF_DISP);
	sprintf_s(str_interf[MY_INTERF_FIND], MAX_INTERF_CHAR*sizeof(char), "%d - find", MY_INTERF_FIND);

	sprintf_s(str_interf[MY_INTERF_INSERT], MAX_INTERF_CHAR*sizeof(char), "%d - insert", MY_INTERF_INSERT); //Dodane - dodanie za index
	sprintf_s(str_interf[MY_INTERF_INSERTTABLE], MAX_INTERF_CHAR*sizeof(char), "%d - insert array", MY_INTERF_INSERTTABLE); //Dodane - dodanie tablicy za index
	sprintf_s(str_interf[MY_INTERF_REMOVE], MAX_INTERF_CHAR*sizeof(char), "%d - remove", MY_INTERF_REMOVE); //Dodane - usuniecie z tablicy
	sprintf_s(str_interf[MY_INTERF_REMOVEALL], MAX_INTERF_CHAR*sizeof(char), "%d - remove ALL", MY_INTERF_REMOVEALL); //Dodane - usuniecie all z tablicy
	sprintf_s(str_interf[MY_INTERF_MODIFY], MAX_INTERF_CHAR*sizeof(char), "%d - modyfikuj obiekt", MY_INTERF_MODIFY); //Dodane - modyfikacja indexu
	sprintf_s(str_interf[MY_INTERF_SAVE], MAX_INTERF_CHAR*sizeof(char), "%d - zapisz do pliku", MY_INTERF_SAVE);		//Dodane - zapis do pliku
	sprintf_s(str_interf[MY_INTERF_LOAD], MAX_INTERF_CHAR*sizeof(char), "%d - wczytaj z pliku", MY_INTERF_LOAD);		//Dodane - odczyt z pliku
	sprintf_s(str_interf[MY_INTERF_EXCEL], MAX_INTERF_CHAR*sizeof(char), "%d - zapisz w foramcie CSV + Excel", MY_INTERF_EXCEL); //Dodane - zapis do pliku CSV i uruchomienie Excela

	sprintf_s(str_interf[MY_INTERF_FINISH], MAX_INTERF_CHAR*sizeof(char), "%d - finish", MY_INTERF_FINISH);
	vect.init(dim);
	run = true;
}

void my_interf::menu()
{
	int i;
	for (i = 1; i<MY_INTERF_TOT; i++)
	{
		cout << str_interf[i] << endl;
	}
}

void my_interf::push()
{
	//my_coord ob(0, 0);
	node ob(0, "NoName", 0, 0);
	cin >> ob;
	vect.push(ob);
}

void my_interf::pop()
{
	//my_coord *ptr = NULL;
	node *ptr = NULL;
	ptr = vect.pop();
	if (ptr)
	{
		cout << *ptr << endl;
	}
	else
	{
		return;
		//msg.mess(my_mess::WARN_ARR_EMPT); // Juz to wypisuje pop z my_vect
	}
}

void my_interf::disp()
{
	vect.disp();
}

#ifdef FIND_ALGORITHM
void my_interf::find()
{
	//my_coord ob(0, 0);
	//my_coord *ptr = NULL;
	node ob(0, "NoName", 0, 0);
	node *ptr = NULL;
	cout << "Wprowadz dane do poszukiwania: \n";
	//cin >> ob; // Wyszukiwanie identycznego obiektu

	cout << "Podaj numer wierzcholka: ";
	int nr;
	cin >> nr;
	node ob(nr, "NoName", 0, 0);

	ptr = vect.get_begin();
	size_t dist;
	while (ptr != vect.get_end())
	{
		ptr = ::find(ptr, vect.get_end(), ob); // Zmiana bylo Find
		if (ptr)
		{
			dist = ptr - vect.get_begin();
			/*if (dist == vect.get_end() - vect.get_begin())
				ptr = NULL;*/
			if (ptr == vect.get_end())
				break;
			else
				cout << "it = " << dist << " " << *ptr << endl;
			ptr++;
		}
		else
			cout << "search end\n";
	}
	cout << "search end\n";
}
#else
template <class T>
T * Find(T* ptr, T* lastPtr, const T &ob)
{
	while (ptr<lastPtr && (!(*ptr == ob)) )
		ptr++;

	if (ptr == lastPtr)
		return NULL;
	else
		return ptr;
}

void my_interf::find()
{
	//my_coord ob(0, 0);
	//my_coord *ptr = NULL;
	//node ob(0, "NoName", 0, 0);
	node *ptr = NULL;
	cout << "Wprowadz dane do poszukiwania: \n";
	//cin >> ob; // Wyszukiwanie identycznego obiektu

	cout << "Podaj numer wierzcholka: ";
	int nr;
	cin >> nr;
	node ob(nr, "NoName", 0, 0);

	ptr = vect.get_begin();
	size_t dist;
	while (ptr)
	{
		ptr = Find(ptr, vect.get_end(), ob);
		if (ptr)
		{
			dist = ptr - vect.get_begin();
			cout << "it = [" << dist << "]  " << *ptr << endl;
			ptr++;
		}
		else
			cout << "search end\n";
	}
}
#endif

void my_interf::finish()
{
	run = false; 
}

void my_interf::defaul()
{
	cout << "Nieznany kod operacji.\nWybierz ponownie.\n";
}

void my_interf::insert()
{
	node ob(0, "NoName", 0, 0);

	size_t index;
	cout << "Podaj index ZA ktorym chcesz wstawic obiekt. \nIndex=-1 <=> wstawienie elementu na poczatek wektora\n";
	cout << "Index: ";
	cin >> index;
	cout << "Dane obiektu ktory chcesz: " << endl;
	cin >> ob;

	if (vect.insert(ob, index))
		cout << "Dodano obiekt na pozycje " << index + 1 << endl;
	else
		cout << "Nie dodano obiektu!" << endl;
}

void my_interf::insertTable()
{
	node * tab = NULL;

	size_t dim;
	cout << "Podaj wielkosc tablicy: ";
	cin >> dim;
	if (dim <= 0)
	{
		cout << "Niewlasciwy rozmiar!\n";
		return;
	}

	size_t index;
	cout << "Podaj index ZA ktorym chcesz wstawic tablice obiektow. \nIndex=-1 <=> wstawienie tablicy na poczatek wektora\n";
	cout << "Index: ";
	cin >> index;

	try
	{
		tab = new node[dim];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}

	for (size_t i = 0; i < dim; i++)
	{
		cout << "Podaj element " << i << "/" << dim - 1 << ":\n";
		cin >> tab[i];
	}

	if(vect.insertTable(tab, index, dim))
		cout << "Dodano tablice na pozycje " << index + 1 << endl;
	else
		cout << "Nie dodano tablicy!" << endl;

	if (tab)
		delete[] tab;
	tab = NULL;
}

void my_interf::remove()
{
	cout << "Podaj index: ";
	size_t i;
	cin >> i;
	vect.remove(i);
}

void my_interf::removeAll()
{
	cout << "Czy jestes pewien usunac wszystko? (T/N): ";
	char odp;
	cin >> odp;
	if (odp == 'T')
	{
		if (vect.removeAll())
			cout << "Usunieto elementy\n";
		else
			cout << "Nie usunieto elementow\n";
	}
	else
		return;
}

void my_interf::modify()
{
	//Dzieki try/catch i throw w T& my_vect<T>::operator[] unikam page fault
	size_t nr;
	cout << "Podaj index obiektu ktory chcesz modyfikowac: ";
	cin >> nr;
	try
	{
		cout << "Modyfikujesz obiekt: " << vect[nr] << endl;
		cin >> vect[nr];
	}
	catch (const char * exc)
	{
		cout << exc;
		return;
	}
}

#ifdef MFC_Dialogs
void my_interf::save()
{
	CFileDialog plik(false, _T("gucwa")); //Moje wlasne rozszerzenie :)
	plik.DoModal();
	char filePath[1024];
	sprintf_s(filePath, 1024 * sizeof(char), "%s", (CW2A)plik.GetPathName().GetString()); //Konwersja do char*

	if (vect.save(filePath))
		cout << "Zapisano\n";
}

void my_interf::load()
{
	TCHAR filtr[] = _T("gucwa files (*.gucwa)");
	CFileDialog plik(true, _T("gucwa"), _T("*.gucwa"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filtr); //Wymuszenie otwarcia pliku o rozszerzeniu gucwa
	plik.DoModal();
	char filePath[1024];
	sprintf_s(filePath, 1024 * sizeof(char), "%s", (CW2A)plik.GetPathName().GetString());

	if (vect.load(filePath))
		cout << "Wczytano\n";
}
#else
void my_interf::save()
{
	cout << "Podaj nazwe pliku: ";
	char filename[512];
	cin >> filename;
	if(vect.save(filename))
		cout << "Zapisano\n";
}
void my_interf::load()
{
	cout << "Podaj nazwe pliku: ";
	char filename[512];
	cin >> filename;
	if (vect.load(filename))
		cout << "Wczytano\n";
}
#endif

void my_interf::excel()
{
	CFileDialog dialog(false, _T("csv"));
	dialog.DoModal();
	char filePath[1024];
	sprintf_s(filePath, 1024 * sizeof(char), "%s", (CW2A)dialog.GetPathName().GetString()); //Konwersja do char*

	//Przenioslem funkcje do klasy my_vect - doda�em do niej obiekt CExcel_class

	if(vect.excel(filePath))
		cout << "Zapisano. Uruchamiam Excel\n";
}


#ifdef FIND_ALGORITHM
#undef FIND_ALGORITHM
#endif

#ifdef MFC_Dialogs
#undef MFC_Dialogs
#endif