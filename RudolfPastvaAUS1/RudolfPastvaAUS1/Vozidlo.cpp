#include "Vozidlo.h"
#include <fstream>


Vozidlo::Vozidlo(string pSpz, double pNosnost, int pPrevadzkoveNaklady, string pDatumPridaniaDoEvidencie)
{
	spz = pSpz;
	nosnost = pNosnost;
	datumPridaniaDoEvidencie = pDatumPridaniaDoEvidencie;
	prevadzkoveNaklady = pPrevadzkoveNaklady;
}

Vozidlo::~Vozidlo()
{
	for (auto p : zoznPrevazanychZasielok)
	{
		delete p;
	}
	
}

string Vozidlo::getSPZ()
{
	return spz;
}

double Vozidlo::getNosnost()
{
	return nosnost;
}


void Vozidlo::vylozVsetkyZasielky()
{

}

bool Vozidlo::vylozZasielku()
{
	return false;
}

string Vozidlo::toString()
{
	string retazec = spz + " /" + to_string(nosnost) + " /" + to_string(prevadzkoveNaklady) + " /" + "(" + datumPridaniaDoEvidencie + ")";
	return retazec;
}

void Vozidlo::pridajZastavkuDoTrasy(LokalnPrekladisko *pZastvavka)
{
	zoznZastavok.add(pZastvavka);
}

void Vozidlo::zrusTrasu()
{
	zoznZastavok.clear();
}

void Vozidlo::setJeRezervovane()
{
	
	jeRezervovane = !jeRezervovane;
}

bool Vozidlo::getJeAutoRezervovane()
{
	return jeRezervovane;
}

string Vozidlo::getPoslednuZastavku()
{
	if (zoznZastavok.size() == 0)
		return "";
	return zoznPrevazanychZasielok[zoznPrevazanychZasielok.size() - 1]->getRegionPr();
}

int Vozidlo::getPocetZastavok()
{
	return zoznPrevazanychZasielok.size();
}

void Vozidlo::rozvezBaliky()
{
	int j = 0;
	for (int i = 0; i < zoznZastavok.size(); i++)
	{
		while ( j < zoznPrevazanychZasielok.size() && zoznZastavok[i]->getNazovLokPr().compare(zoznPrevazanychZasielok[j]->getRegionPr()) == 0)
		{
			zoznZastavok[i]->pridajZasielkuNaOdoslanie(zoznPrevazanychZasielok[j]);
			j++;
		}
	}
	zoznPrevazanychZasielok.clear();
}

void Vozidlo::nalozBalikDoAuta(Objednavka * obj)
{
	zoznPrevazanychZasielok.add(obj);
}
void Vozidlo::zozbierajBaliky()
{
	for (int i = zoznZastavok.size() - 1; i > -1; i--)
	{

		for (int j = 0; j < zoznZastavok[i]->getBalikyNaTriedenie().size(); j++)
		{

			zoznPrevazanychZasielok.add(zoznZastavok[i]->getBalikyNaTriedenie()[j]);
		}
		zoznZastavok[i]->vymazZoznZasielokNaTriedenie();
	}
}





void Vozidlo::vylozVoz( ArrayList<Objednavka*>& z)
{
	for (int i = 0; i < zoznPrevazanychZasielok.size(); i++)
	{
		z.add(zoznPrevazanychZasielok[i]);
	}
	setJeRezervovane(); 
	zoznPrevazanychZasielok.clear();
	zoznZastavok.clear();

}

void Vozidlo::setCelkovePrevadzkoveNaklady()
{
	celkovePrevadzkoveNaklady = celkovePrevadzkoveNaklady + (2 * prevadzkoveNaklady * zoznZastavok.size());
}

int Vozidlo::getCelkovePrevadzkoveNaklady()
{
	return celkovePrevadzkoveNaklady;
}

void Vozidlo::zapisDoSuboru(fstream & zapisovac)
{
	
	zapisovac << spz << " " <<to_string(nosnost) << " " << to_string(prevadzkoveNaklady) << " " << datumPridaniaDoEvidencie << " " << to_string(celkovePrevadzkoveNaklady) << endl;
	zapisovac << to_string(zoznPrevazanychZasielok.size()) << endl;
	for (int i = 0; i < zoznPrevazanychZasielok.size(); i++)
	{
		zapisovac << zoznPrevazanychZasielok[i]->toString()<<endl;
	}
	zapisovac << to_string(jeRezervovane) << endl;
	if (jeRezervovane)
	{
		zapisovac << zoznZastavok[0]->getNazovLokPr() << " " << zoznZastavok[zoznZastavok.size() - 1]->getNazovLokPr() << endl;
	}
	
	
}

void Vozidlo::nacitajZvysneUdajeVozidla(ifstream & cin)
{

	int pocet;
	cin >> celkovePrevadzkoveNaklady;
	cin >> pocet;	
	for (int i = 0; i < pocet; i++)
	{
		double pHmotnost;
		string pRegionOdosielatela, pRegionPrijimatela;
		int pVzdialenostOd, pVzdialenostPr;
		cin >> pHmotnost;
		cin >> pRegionOdosielatela;
		cin >> pVzdialenostOd;
		cin >> pRegionPrijimatela;
		cin >> pVzdialenostPr;
		Objednavka * obj = new Objednavka(pHmotnost, pRegionOdosielatela, pVzdialenostOd, pRegionPrijimatela, pVzdialenostPr);
		zoznPrevazanychZasielok.add(obj);
	}
	cin >> jeRezervovane;
	
	
	

}



