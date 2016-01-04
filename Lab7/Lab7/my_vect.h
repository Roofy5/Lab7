#pragma once
#include "my_mess.h"
#include "CExcel_class.h"
#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push, 1)
template <class T>
class my_vect
{
	T *dat;        //wskaznik do danych typu ogolnego
	size_t ndim;   //rozmiar tablicy, na ktory pozostala zaalokowana
	size_t last;   //wskazuje na pierwsza pusta pozycje w tablice
	my_mess msg;
	CExcel_class ExcelObject;

public:
	my_vect(size_t dm); //konstruktor - alokuje pamiec dla tablicy typu T na dm elementow
	my_vect() { dat = NULL; ndim = last = 0; liczba_alokacji = 1; }
	//my_vect(const my_vect &ob); //Nieptrzebny kontruktor kopiujacy
	~my_vect();
	void init(size_t dm);	//alokuje pamiec o dm elementow, jesli dat = NULL
	T *get_begin();			//zwraca wskaünik do poczπtku tablicy dat
	T *get_end();			//zwraca wskaünik do dat[last]
	void disp();			//wyswietla stan tablicy
	void push(const T &ob); //dodaje element typu T do pierwszej wolnej pozycji w tablice
	T *pop();               //zwraca wskaznik do ostatniego elementu tablicy i usuwa jego, lub NULL (tablica pusta)
	T & operator [] (const size_t ind); //0 <= ind < last
	bool insert(const T &ob, size_t ind);
	bool insertTable(const T * tab, size_t ind, size_t numb);
	void remove(size_t ind); //usuwa element tablicy o indeksie ind, kompresuje tablicu
	bool removeAll(); //przestawia last na 0
	bool save(const char * filename);
	bool load(const char * filename);
	bool excel(char * filePath);

private:
	int liczba_alokacji;
	bool alloc();            //alocuje pamiÍÊ
	T* alloc(size_t rozmiar);
	void checkLast();		 //sprawdza czy nie przekroczylismy tablicy true-OK false-Blad
	void realloc();			 //realokuje pamiec

};
#pragma pack(pop)

//#####################
//##### DEFINICJE #####
//#####################

template <class T>
my_vect<T>::my_vect(size_t dm)
{
	ndim = dm;
	alloc();
	last = 0;
	liczba_alokacji = 1;
}

template <class T>
my_vect<T>::~my_vect()
{
	if (dat)
	{
		/*for (size_t i = 0; i < last; i++)
		delete dat[i];*/
		delete[] dat;
	}
}

template <class T>
void my_vect<T>::init(size_t dm)
{
	if (!dat)
	{
		ndim = dm;
		alloc();
		last = 0;
	}
}

template <class T>
T* my_vect<T>::get_begin()
{
	return dat;
}

template <class T>
T* my_vect<T>::get_end()			//zwraca wskaünik do dat[last]
{
	if (dat)
		return &dat[last];
	else
		return NULL;
}

template <class T>
void my_vect<T>::disp()			//wyswietla stan tablicy
{
	if (dat)
	{
		size_t i = 0;
		for (i = 0; i < last; i++)
			cout << "[" << i << "]   " << dat[i] << endl;
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
	}
	if (last == 0)
		msg.mess(my_mess::WARN_ARR_EMPT);
}

template <class T>
void my_vect<T>::push(const T &ob) //dodaje element typu T do pierwszej wolnej pozycji w tablice
{
	if (dat)
	{
		checkLast();
		dat[last] = ob;
		last++;
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
	}
}

template <class T>
T* my_vect<T>::pop()  //zwraca wskaznik do ostatniego elementu tablicy i usuwa jego, lub NULL (tablica pusta)
{
	if (dat)
	{
		if (last == 0)
		{
			msg.mess(my_mess::WARN_ARR_EMPT);
			return NULL;
		}
		else
		{
			last--;
			return &dat[last];
		}
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
		return NULL;
	}
}

template <class T>
T & my_vect<T>::operator [] (const size_t ind) //0 <= ind < last
{
	if (dat)
	{
		if (ind >= 0 && ind < last) //Sprawdzam index - dzieki temu unikam Page Fault
		{
			return dat[ind]; //return &dat[ind]; 
		}
		else
		{
			//return dat[last]; //return NULL
			throw "Nieprawidlowy index!\n";
		}
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
		//return NULL; //return NULL
		throw "Tablica pusta!\n";
	}
}

template <class T>
bool my_vect<T>::insert(const T &ob, size_t ind)
{
	if (dat)
	{
		if (ind+1 >= 0 && ind+1 <= last) // ind=-1 - Dzieki temu mozna wstawic przed pierwszy element
		{
			size_t i;
			last++;
			checkLast();
			for (i = last; i > ind+1; i--)
			{
				dat[i] = dat[i-1];
			}
			dat[ind + 1] = ob;
			return true;
		}
		else
			return false;
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
		return false;
	}
}

template <class T>
bool my_vect<T>::insertTable(const T * tab, size_t ind, size_t numb)
{
	if (dat)
	{
		for (size_t i = 0; i < numb; i++)
			if (!insert(tab[i], ind++))
				return false;
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
		return false;
	}
	return true;
}

template <class T>
void my_vect<T>::remove(size_t ind) //usuwa element tablicy o indeksie ind, kompresuje tablice
{
	if (dat)
	{
		if (ind >= 0 && ind < last)
		{
			//T * temp = alloc(ndim - 1);

			size_t dat_i = 0;
			for (size_t tmp_i = 0; tmp_i < ndim - 1; tmp_i++, dat_i++)
			{
				if (tmp_i == ind)
					dat_i++;
				dat[tmp_i] = dat[dat_i];
			}

			//delete[] dat;
			//dat = temp;
			//temp = NULL;

			//ndim--;
			last--;
		}
		else
			return;
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_NULL);
	}
}

template <class T>
bool my_vect<T>::removeAll()
{
	//Funkcja ustawia tylko last na pozycje 0 - nie usuwa elementow
	//Na zajeciach mowil Pan zeby elementy tylko "przestawiac" jezeli usuwamy
	//W podobny sposob dziala remove
	//Mozna takze zrobic delete []dat ale w projekcie nie jest to sprecyzowane
	if (dat && last!=0)
	{
		last = 0;
		return true;
	}
	else
		return false;
}

template <class T>
bool my_vect<T>::save(const char * filename)
{
	ofstream plik(filename, ios::out | ios::binary);
	if (!plik.is_open())
	{
		msg.mess(my_mess::WARN_CREATE_FILE);
		return false;
	}
	
	plik.write((char *)&ndim, sizeof(size_t)); //Zapisuje wymiar ndim kodujac na char
	plik.write((char *)&last, sizeof(size_t)); //Zapisuje last kodujac na char
	for (size_t i = 0; i < ndim; i++)
		plik << dat[i]; //Przeciazony operator << w klasie ktora przechowujemy w vector

	plik.close();
	return true;
}

template <class T>
bool my_vect<T>::load(const char * filename)
{
	ifstream plik(filename, ios::in | ios::binary);
	if (!plik.is_open())
	{
		msg.mess(my_mess::WARN_OPEN_FILE);
		return false;
	}

	if (dat)
		delete[]dat;

	plik.read((char *)&ndim, sizeof(size_t));
	plik.read((char *)&last, sizeof(size_t));

	//Alokuje nowa tablice o wymiarze ndim
	//Tablice alokuje tylko raz - nie wykonuje push()
	//Dzieki temu wzrasta wydajnosc
	
	dat = alloc(ndim); 

	for (size_t i = 0; i < ndim; i++) //Odczytuje dopoki i<last - last jest zapisywany i odczytywany z pliku - dzieki temu mam dokladna kontrole ile wczytac danych - nie musze uzywac End Of File
	{
		plik >> dat[i]; //Przeciazony operator >> w klasie ktora przechowujemy w vector
	}

	plik.close();
	return true;
}

template <class T>
bool my_vect<T>::excel(char * filePath)
{
	ofstream plik(filePath, ios::out);
	if (!plik.is_open())
	{
		msg.mess(my_mess::WARN_CREATE_FILE);
		return false;
	}

	T * ptr = get_begin();
	T * end = get_end();
	while (ptr != end)
	{
		ExcelObject.CreateOfstream(plik, *ptr);
		ptr++;
		if (!plik.good())
		{
			msg.mess(my_mess::ERR_SAVE_FILE);
		}
	}
	plik.close();

	ExcelObject.SpawnExcel(filePath);
	return true;
}

template <class T>
bool my_vect<T>::alloc()
{
	if (ndim > 0)
	{
		try
		{
			dat = new T[ndim];
			return true;
		}
		catch (std::bad_alloc e)
		{
			msg.mess(my_mess::ERR_ALLOC_MEM);
		}
	}
	return false;
}

template <class T>
T* my_vect<T>::alloc(size_t rozmiar)
{
	try
	{
		T* tmp = new T[rozmiar];
		return tmp;
	}
	catch (bad_alloc e)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}
	return NULL;
}

template <class T>
void  my_vect<T>::checkLast()
{
	if (dat)
	{
		if (last >= ndim)
		{
			realloc();
		}
		else
			return; // OK
	}
	else
		msg.mess(my_mess::WARN_ARR_NULL);
}

template <class T>
void my_vect<T>::realloc()
{
	size_t temp_ndim = ndim + liczba_alokacji * 2; //moj algorytm realokacji
	T *tmp = alloc(temp_ndim);
	size_t i;
	for (i = 0; i < ndim; i++)
	{
		tmp[i] = dat[i]; //kopiowanie tablicy
	}
	delete[]dat;
	dat = tmp;
	tmp = NULL;
	//ndim++;
	ndim = temp_ndim;
	liczba_alokacji++;
}

