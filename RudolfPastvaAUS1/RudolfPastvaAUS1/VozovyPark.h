#pragma once
#include "Vozidlo.h"
#include "struktury/heap_monitor.h"
#include "struktury/array_list.h"
#include "struktury/array.h"
#include <string>
#include "LokalnPrekladisko.h"
#include "Objednavka.h"


using namespace std;
using namespace structures;

class VozovyPark
{
	ArrayList<Vozidlo*> zoznamVozidiel = ArrayList<Vozidlo*>();

public:
	VozovyPark();
	~VozovyPark();
	Vozidlo* getVozidlo(string spz);
	Vozidlo* getVozidloNaIndexe(int index);
	void pridajVozidlo(string datumPridaniaDoEvidencie);
	bool odoberVozidlo(string pSpz);
	void vypisZoznam();
	int getPocetVozidiel();
	//void zoradVozidla();
	int getCelkoveNakladyVozidiel();
	void pridajVoz(Vozidlo  * voz);
};

