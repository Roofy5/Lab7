#include "stdafx.h"
#include "CExcel_class.h"
#include <Windows.h>

ofstream & CExcel_class::CreateOfstream(ofstream & strumien, my_coord & ob)
{
	char wsk[32];
	ChangePoint(ob.pcoord[0], wsk, 32);
	strumien << wsk;
	strumien << ";";
	ChangePoint(ob.pcoord[1], wsk, 32);
	strumien << wsk;
	strumien << endl;
	return strumien;
}

ofstream & CExcel_class::CreateOfstream(ofstream & strumien, node & ob)
{
	strumien << ob.numb;
	strumien << ";";
	strumien << ob.str;
	strumien << ";";
	CreateOfstream(strumien, (my_coord &)ob);

	return strumien;
}

void CExcel_class::ChangePoint(double a, char * wsk, int dlugosc)
{
	sprintf_s(wsk, dlugosc * sizeof(char), "%lf", a);

	for (int i = 0; i < dlugosc; i++)
	{
		if (wsk[i] == '.')
		{
			wsk[i] = ',';
			break;
		}
	}
}

void CExcel_class::SpawnExcel(char * file)
{
	char excel_path[256];
	char excel_file_path[512];
	
	if (FindExcelPath(excel_path) == false)
	{
		// Wskazac manualnie
		//cout << "Prosze wskazac sciezke do Excela samodzielnie.\n";
		//system("pause");
		MessageBoxA(NULL, "Program nie mogl znalezc sciezki dostepu do programu Excel.\nProsze wksazac sciezke do aplikacji excel.exe", "Warning", MB_OK | MB_ICONWARNING);
		TCHAR filtr[] = _T("Excel (*.exe)");
		CFileDialog plik(true, _T("exe"), _T("*.exe"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filtr);
		plik.DoModal();

		sprintf_s(excel_file_path, 512 * sizeof(char), "%s", (CW2A)plik.GetPathName().GetString());
	}
	else
	{
		strcpy_s(excel_file_path, 256 * sizeof(char), excel_path);
		strcat_s(excel_file_path, 256 * sizeof(char), "EXCEL.exe");
	}

	_spawnl(_P_NOWAIT, excel_file_path, " ", file, NULL); //_P_WAIT -czeka na zakonczenie, _P_NOWAIT !czeka
	//_spawnl(_P_NOWAIT, "D:\\Programy\\Office 2007\\Office12\\EXCEL.exe", "EXCEL.exe", file, NULL); //_P_WAIT -czeka na zakonczenie, _P_NOWAIT !czeka
	//int i = _spawnlp(_P_WAIT, "EXCEL.exe", file, NULL); // Poszukuje w PATH - u mnie nie dziala :(
}

bool CExcel_class::FindExcelPath(char * path)
{
	HKEY klucz;
	LONG ret;

	ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\excel.exe", 0, KEY_READ, &klucz);

	if (ret != ERROR_SUCCESS)
	{
		// Zle
		cout << "Nie moge otworzyc/znalezc sciezki do Excel\n";
		return false;		
	}
	//OK

	char excel_path[256];
	DWORD typ = REG_SZ;
	DWORD ilosc = 256;
	memset(excel_path, 0, 256);

	if (RegQueryValueExA(klucz, "Path", NULL, &typ, (LPBYTE)excel_path, &ilosc) != ERROR_SUCCESS)
	{
		cout << "Nie moge odczytac klucz rejestru\n";
		RegCloseKey(klucz);
		return false;
	}
	RegCloseKey(klucz);

	memcpy(path, excel_path, 256 * sizeof(char));

	return true;
}