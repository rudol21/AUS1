#pragma once
#include <string>
#include "struktury/heap_monitor.h"
#include "Objednavka.h"
#include <fstream>

using namespace std;


class Dron
{

	string serioveCislo = "";
	int typDronu = -1;
	double  kapacitaBaterie = 100.0;
	int pocetPrepravenychZasielok = 0;
	int nalietaneHodiny = 0;
	bool jeDronVolny = true;
	int casKedyJeDronVolnyNaslDen = 420; 
	int casKedyJeDronVolnyAktDen = 420;
	double  kapacitaBaterievCasKedyJeDronVolnyNaslDen = 100.0;
	int casPriletu = 0;
	string datumPridaniaDoEvidencie;
	Objednavka *balik = nullptr;
public:
	Dron(string pSerioveCis, int pTypDronu, string pDatumPridaniaDoEvidencie);
	~Dron();
	string getSerioveCislo();
	int getTypDronu();
	double getKapacitaBaterie();
	int getPocetPrepravenychZ();
	int getNalietaneHodiny();
	bool getJeDronVolny();
	void setKapacitaBaterie(int pocetMinNabijania);
	void setPocetPrepZas();
	void setNalietaneHodiny(int pocetMinutLetu);
	void setJeDronVolny();
	void pripocitajCasNaNaslDen(int pMinuty);
	int getCasKedyJeDrVolnyNaslDen();
	void setCasKedyJeDronVolnyNaslDen(int pomocnyCas);
	int getCasKedyJeDronVolnyAktDen();
	void setCasKedyJeDronVolnyAktDen(int pomocnyCas);
	int getCasPriletu();
	void setCasPriletu(int pNovyCasPriletu);
	Objednavka* getBalik();
	void zoberBalik(Objednavka * obj);
	void vylozBalik();
	string toString();
	string toStringPreZapisDouboru();
	void odoberKapacituBaterie(int pocetMinut);
	int getPotrebnyCasNaDobitie(int dobaLetu);
	int getPotrebnyCasNaNabitieNaCestu(int dobaLetu);
	void setKapacitaBaterievCaseKedyJeDronVolnyNaslDen(int x,int dobaLetu);
	void novyden();
	void nacitajZvysneUdaje(ifstream &cin);



};

