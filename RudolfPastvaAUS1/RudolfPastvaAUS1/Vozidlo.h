#pragma once


#include "Cas.h"
#include "LokalnPrekladisko.h"
#include "Objednavka.h"
#include "struktury/array.h"
#include "struktury/heap_monitor.h"

using namespace std;

class Vozidlo
{
	ArrayList<Objednavka*> zoznPrevazanychZasielok = ArrayList<Objednavka*>();
	ArrayList<LokalnPrekladisko*> zoznZastavok = ArrayList<LokalnPrekladisko*>();
	string spz;
	double nosnost = 0.0;
	int prevadzkoveNaklady = 0;
	int celkovePrevadzkoveNaklady = 0;
	string datumPridaniaDoEvidencie;
	bool jeRezervovane = false;

public:
	Vozidlo(string pSpz, double pNosnost,int pPrevadzkoveNaklady, string pDatumPridaniaDoEvidencie);
	~Vozidlo();
	string getSPZ();
	double getNosnost();
	//int getPrevadzkoveNaklady();
	//void setLPKdeSaVozidloNachadza(LokalnePrekladisko* lokP);
	//void setVozidloNieJeVLP();
	void vylozVsetkyZasielky();
	bool vylozZasielku();
	string toString();
	void pridajZastavkuDoTrasy(LokalnPrekladisko *pZastvavka);
	void zrusTrasu();
	void setJeRezervovane();
	bool getJeAutoRezervovane();
	string getPoslednuZastavku();
	int getPocetZastavok();
	void rozvezBaliky();
	void nalozBalikDoAuta(Objednavka * obj);
	void zozbierajBaliky();
	void vylozVoz(ArrayList<Objednavka*> &z);
	void setCelkovePrevadzkoveNaklady();
	int getCelkovePrevadzkoveNaklady();
	void zapisDoSuboru(fstream &zapisovac);
	void nacitajZvysneUdajeVozidla(ifstream &cin);
	
	

};



