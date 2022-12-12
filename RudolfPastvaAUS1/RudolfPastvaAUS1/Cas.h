#pragma once
#include <string>
#include "struktury/heap_monitor.h"
#include <fstream>
using namespace std;
class Cas
{
	int rok = 2019;
	int mesiac = 3;
	int den = 16;
	int hodina = 7;//prerobit hodina je zbytocna
	int minuta = 00;
public:
	Cas();
	~Cas();
	string getDatum();
	int getCas();
	void posunCasOMinutu();
	string toString();
	void nacitajcas(ifstream &cin);

};

