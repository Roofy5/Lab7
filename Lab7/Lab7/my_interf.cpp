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

	sprintf_s(str_interf[MY_INTERF_REMOVE], MAX_INTERF_CHAR*sizeof(char), "%d - remove", MY_INTERF_REMOVE); //Dodane - usuniecie z tablicy
	sprintf_s(str_interf[MY_INTERF_SAVE], MAX_INTERF_CHAR*sizeof(char), "%d - zapisz do pliku", MY_INTERF_SAVE);		//Dodane - zapis do pliku
	sprintf_s(str_interf[MY_INTERF_LOAD], MAX_INTERF_CHAR*sizeof(char), "%d - wczytaj z pliku", MY_INTERF_LOAD);		//Dodane - odczyt z pliku

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
	my_coord ob(0, 0);
	cin >> ob;
	vect.push(ob);
}

void my_interf::pop()
{
	my_coord *ptr = NULL;
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
	my_coord ob(0, 0);
	my_coord *ptr = NULL;
	cout << "input x, y - object for search\n";
	cin >> ob;
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
	my_coord ob(0, 0);
	my_coord *ptr = NULL;
	cout << "input x, y - object for search\n";
	cin >> ob;
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

void my_interf::remove()
{
	cout << "Podaj index: ";
	size_t i;
	cin >> i;
	vect.remove(i);
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


#ifdef FIND_ALGORITHM
#undef FIND_ALGORITHM
#endif

#ifdef MFC_Dialogs
#undef MFC_Dialogs
#endif