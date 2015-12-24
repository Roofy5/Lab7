#pragma once
#include "my_coord.h"
#include "node.h"

class CExcel_class
{
public:
	ofstream & CreateOfstream(my_coord & ob);
	ofstream & CreateOfstream(node & ob);
private:
	void ChangePoint(double a, char * wsk, int dlugosc);
};