#include "VozovyPark.h"
#include "struktury/heap_monitor.h"
#include <algorithm>



VozovyPark::VozovyPark()
{
}


VozovyPark::~VozovyPark()
{
	for (auto p : zoznamVozidiel)
	{
		delete p;
	}
}

Vozidlo * VozovyPark::getVozidlo(string spz)
{
	for (int i = 0; i < zoznamVozidiel.size(); i++)
	{
		if (zoznamVozidiel[i]->getSPZ().compare(spz) == 0)
			return zoznamVozidiel[i];
	}
}

Vozidlo * VozovyPark::getVozidloNaIndexe(int index)
{
	return zoznamVozidiel[index];
}

void VozovyPark::pridajVozidlo(string datumPridaniaDoEvidencie)
{
	string pSpz;
	double pNosnost;
	int pPrevadzkoveNaklady;
    cin >> pSpz >> pNosnost >> pPrevadzkoveNaklady;
	Vozidlo *v = new Vozidlo(pSpz, pNosnost, pPrevadzkoveNaklady, datumPridaniaDoEvidencie);
	zoznamVozidiel.add(v);
	
}

bool VozovyPark::odoberVozidlo(string pSpz)
{
	for (int i = 0; i < zoznamVozidiel.size(); i++)
	{
		if (zoznamVozidiel[i]->getSPZ().compare(pSpz) == 0)
		{
			zoznamVozidiel.removeAt(i);
			return true;
		}
		return false;
	}
}

void VozovyPark::vypisZoznam()
{	
	for (int i = 0; i < zoznamVozidiel.size(); i++)
	{
		cout << zoznamVozidiel[i]->toString()<<endl;
	}
}

int VozovyPark::getPocetVozidiel()
{
	return zoznamVozidiel.size();
}



int VozovyPark::getCelkoveNakladyVozidiel()
{
	int celkoveNaklady = 0;
	for (int i = 0; i < zoznamVozidiel.size(); i++)
	{
		celkoveNaklady = celkoveNaklady + zoznamVozidiel[i]->getCelkovePrevadzkoveNaklady();
	}
	return celkoveNaklady;
}

void VozovyPark::pridajVoz(Vozidlo * voz)
{
	zoznamVozidiel.add(voz);
}
