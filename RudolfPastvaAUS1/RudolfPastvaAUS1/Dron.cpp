#include "Dron.h"

#define TYP1SPOTREBABATERIEZAMIN 2.50
#define TYP2SPOTREBABATERIEZAMIN 1.67
#define ZAOKRUHLOVANIE 0.99




Dron::Dron(string pSerioveCis, int pTypDronu, string pDatumPridaniaDoEvidencie)
{
	serioveCislo = pSerioveCis;
	typDronu = pTypDronu;
	datumPridaniaDoEvidencie = pDatumPridaniaDoEvidencie;
}

Dron::~Dron()
{
	delete balik;
}

string Dron::getSerioveCislo()
{
	return serioveCislo;
}

int Dron::getTypDronu()
{
	return typDronu;
}





double Dron::getKapacitaBaterie()
{
	return kapacitaBaterie;
}

int Dron::getPocetPrepravenychZ()
{
	return pocetPrepravenychZasielok;
}

int Dron::getNalietaneHodiny()
{
	return nalietaneHodiny;
}

bool Dron::getJeDronVolny()
{
	return jeDronVolny;
}

void Dron::setKapacitaBaterie(int pocetMinNabijania)
{
	double percentoBaterie1 = 3.34;
	double percentoBaterie2 = 2;
	if (typDronu == 1)
	{
		kapacitaBaterie = kapacitaBaterie + (percentoBaterie1 * pocetMinNabijania);

	}
	if (typDronu == 2)
	{
		kapacitaBaterie = kapacitaBaterie + (percentoBaterie2 * pocetMinNabijania);
	}
	if (kapacitaBaterie > 100)
		kapacitaBaterie = 100.0;
}



void Dron::setPocetPrepZas()
{
	pocetPrepravenychZasielok++;
}

void Dron::setNalietaneHodiny(int pocetMinutLetu)
{
	nalietaneHodiny = nalietaneHodiny + (pocetMinutLetu);
}

void Dron::setJeDronVolny()
{
	jeDronVolny = !jeDronVolny;
}

void Dron::pripocitajCasNaNaslDen(int pMinuty)
{
	casKedyJeDronVolnyNaslDen = casKedyJeDronVolnyNaslDen + pMinuty;
}

int Dron::getCasKedyJeDrVolnyNaslDen()
{
	return casKedyJeDronVolnyNaslDen;
}

void Dron::setCasKedyJeDronVolnyNaslDen(int pomocnyCas)
{
	casKedyJeDronVolnyNaslDen = pomocnyCas;
}

int Dron::getCasKedyJeDronVolnyAktDen()
{
	return casKedyJeDronVolnyAktDen;
}

void Dron::setCasKedyJeDronVolnyAktDen(int pomocnyCas)
{
	casKedyJeDronVolnyAktDen = pomocnyCas;
}

int Dron::getCasPriletu()
{
	return casPriletu;
}

void Dron::setCasPriletu(int pNovyCasPriletu)
{
	casPriletu = pNovyCasPriletu;
}

Objednavka* Dron::getBalik()
{
	return balik;
}

void Dron::zoberBalik(Objednavka * obj)
{
	balik = obj;
}

void Dron::vylozBalik()
{
	balik = nullptr;
}

string Dron::toString()
{
	int hod = nalietaneHodiny / 60;
	string pom = "";
	if (nalietaneHodiny - (hod * 60) < 10)
		pom = "0";
	string retazec = "Typ" + to_string(typDronu) + ", celkovy pocet nalietanych hodin " + to_string(hod) + ":"+ pom + to_string(nalietaneHodiny-(hod * 60)) +", celkovy pocet prepravenych zasielok:" + to_string(pocetPrepravenychZasielok) +" (" + datumPridaniaDoEvidencie + ")" + "kapacitabaterie: " + to_string(kapacitaBaterie) +" "+ to_string(jeDronVolny);
	return retazec;
}

string Dron::toStringPreZapisDouboru() // dorobit
{
	string retazec = serioveCislo + " " + to_string(typDronu) + " " + datumPridaniaDoEvidencie + " " + to_string(kapacitaBaterie) + " " + to_string(pocetPrepravenychZasielok) + " " + to_string(nalietaneHodiny) + " " + to_string(jeDronVolny) + " ";
	retazec = retazec + to_string(casKedyJeDronVolnyNaslDen) + " " + to_string(casKedyJeDronVolnyAktDen) + " " + to_string(kapacitaBaterievCasKedyJeDronVolnyNaslDen) + " " + to_string(casPriletu);
	return retazec;
}

void Dron::odoberKapacituBaterie(int pocetMinut)
{
	if (typDronu == 1)
	{
		kapacitaBaterie = kapacitaBaterie - (TYP1SPOTREBABATERIEZAMIN * pocetMinut);
	}
	if (typDronu == 2)
	{
		kapacitaBaterie = kapacitaBaterie - (TYP2SPOTREBABATERIEZAMIN * pocetMinut);
	}
	if (kapacitaBaterie < 0)
		kapacitaBaterie = 0;
}

int Dron::getPotrebnyCasNaDobitie(int dobaLetu)
{
	double potrebneDobitie;
	int pom;
	if (typDronu == 1)
	{
		potrebneDobitie = ((dobaLetu * 2) *TYP1SPOTREBABATERIEZAMIN) - kapacitaBaterievCasKedyJeDronVolnyNaslDen;
		if (potrebneDobitie <= 0)
			return 0;
		pom = potrebneDobitie / 3.34 + 1;
		return pom;
	}
	if (typDronu == 2)
	{
		potrebneDobitie = ((dobaLetu * 2) *TYP2SPOTREBABATERIEZAMIN) - kapacitaBaterievCasKedyJeDronVolnyNaslDen;
		if (potrebneDobitie <= 0)
			return 0;
		pom = potrebneDobitie / 2 + 1;
		return pom;
	}
	return 0;
}

int Dron::getPotrebnyCasNaNabitieNaCestu(int dobaLetu)
{
	double potrebneDobitie;
	int pom;
	if (typDronu == 1)
	{
		potrebneDobitie = ((dobaLetu * 2) *TYP1SPOTREBABATERIEZAMIN);
		pom = potrebneDobitie / 3.34 + ZAOKRUHLOVANIE;
		return pom;
	}
	if (typDronu == 2)
	{
		potrebneDobitie = ((dobaLetu * 2) *TYP2SPOTREBABATERIEZAMIN);
		pom = potrebneDobitie / 2 + ZAOKRUHLOVANIE;
		return pom;
	}
	return 0;
}

void Dron::setKapacitaBaterievCaseKedyJeDronVolnyNaslDen(int x, int dobaLetu)
{
	if (x >0)
	{
		kapacitaBaterievCasKedyJeDronVolnyNaslDen = 0;
	}
	if (x == 0)
	{
		if (typDronu == 1)
		{
			kapacitaBaterievCasKedyJeDronVolnyNaslDen = kapacitaBaterievCasKedyJeDronVolnyNaslDen - (dobaLetu * 2.5);
		}
		else 
		{
			kapacitaBaterievCasKedyJeDronVolnyNaslDen = kapacitaBaterievCasKedyJeDronVolnyNaslDen - (dobaLetu * 1.67);
		}
	}
	
}

void Dron::novyden()
{
	casKedyJeDronVolnyAktDen = casKedyJeDronVolnyNaslDen;
	casKedyJeDronVolnyNaslDen = 420;
	kapacitaBaterievCasKedyJeDronVolnyNaslDen = 100.0;
	kapacitaBaterie = 100.0;
	casPriletu = 0;
}

void Dron::nacitajZvysneUdaje(ifstream & cin)
{
	cin >> kapacitaBaterie;
	cin >> pocetPrepravenychZasielok;
	cin >> nalietaneHodiny;
	cin >> jeDronVolny;
	cin >> casKedyJeDronVolnyNaslDen;
	cin >> casKedyJeDronVolnyAktDen;
	cin >> kapacitaBaterievCasKedyJeDronVolnyNaslDen;
	cin >> casPriletu;
}
