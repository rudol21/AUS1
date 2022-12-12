#include "Objednavka.h"
#include "struktury/heap_monitor.h"





Objednavka::Objednavka(double pHmotnost, string pRegionOdosielatela, int pVzdialenostOd, string pRegionPrijimatela, int pVzdialenostPrijimatela)
{
	hmotnostZasielky = pHmotnost;
	regionOdosielatela = pRegionOdosielatela;
	vzdialenostOdosielatela = pVzdialenostOd;
	regionPrijimatela = pRegionPrijimatela;
	vzdialenostPrijimatela = pVzdialenostPrijimatela;
}

Objednavka::~Objednavka()
{
}

double Objednavka::getHmZasielky()
{
	return hmotnostZasielky;
}

string Objednavka::getRegionOd()
{
	return regionOdosielatela;
}

string Objednavka::getRegionPr()
{
	return regionPrijimatela;
}

int Objednavka::getVzdialenostOd()
{
	return vzdialenostOdosielatela;
}

int Objednavka::getVzdialenostPr()
{
	return vzdialenostPrijimatela;
}

string Objednavka::toString()
{
	string retazec = "";
	retazec = to_string(hmotnostZasielky) + " " + regionOdosielatela + " " + to_string(vzdialenostOdosielatela) + " " + regionPrijimatela + " " + to_string(vzdialenostPrijimatela);
	return retazec;
}


