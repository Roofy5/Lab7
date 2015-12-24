// Michal Gucwa
// Zmiana: 08 - grudzien - 2015
// Zmiana: 10 - grudzien - 2015 //Dodanie zapisu/odczytu do pliku binarnego
// Zmiana 15 - grudzien - 2015  //Dodanie do load funkcji close(), w menu atoi(), zwracanie ifstream/ofstream, kontrola wczytywania danych
//							    //Migracja na MFC >> !!!!! <<
// Zmiana 17 - grudzieñ - 2015  //Destruktor my_coord inline, poprawa strumien cin w my_coord
// Zmiana 19 - grudzieñ - 2015 //GitHub
// Zmiana 20 - grudzieñ - 2015 //Poprawki przez SF
// Zmiana 22 - grudzieñ - 2015 //Dodanie klasy node
// Ostatnia zmiana 24 - grudzieñ - 2015 //My_coord zmiana wyswietlania <<, obsluga >> << w node (TODO: obsluga spacji)
										// Rozpozcecie prac nad Excel

#include "stdafx.h"
#include <iostream>
#include "my_interf.h"
#include "my_coord.h"
#include "my_mess.h"
#include "my_vect.h"
#include "node.h"

using namespace std;

int MFC_Init()
{
	//######################### Funkcje MFC ####################//
	int nRetCode = 0;
	HMODULE hModule = ::GetModuleHandle(NULL);
	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}
	return nRetCode;
	//######################### Funkcje MFC ####################//
}

int main(int argc, char* argv[])
{
	MFC_Init();
	
	int op;  //operacje
	char komenda[32];
	my_interf ifc(3);

	while (ifc.run)
	{
		ifc.menu();
		cin >> komenda;
		op = atoi(komenda);

		//cin >> op;
		//system("CLS");
		switch (op)
		{
		case ifc.MY_INTERF_PUSH: //push
			ifc.push();
			break;
		case ifc.MY_INTERF_POP:
			ifc.pop();
			break;
		case ifc.MY_INTERF_DISP:
			ifc.disp();
			break;
		case ifc.MY_INTERF_FIND:
			ifc.find();
			break;
		case ifc.MY_INTERF_REMOVE:
			ifc.remove();
			break;
		case ifc.MY_INTERF_SAVE:
			ifc.save();
			break;
		case ifc.MY_INTERF_LOAD:
			ifc.load();
			break;
		case ifc.MY_INTERF_FINISH:
			ifc.finish();
			break;
		default:
			ifc.defaul();
		};
	}

	system("pause");
	return 0;
}
