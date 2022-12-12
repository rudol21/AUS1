#pragma once
#include "VozovyPark.h"
#include "Cas.h"
#include "LokalnPrekladisko.h"
#include "Objednavka.h"
#include "struktury/array.h"
#include "struktury/heap_monitor.h"
#include "StatistickeData.h"
using namespace std;
class CentralnySklad
{
	structures::Array<LokalnPrekladisko*> zoznLokalnychPrekladisk = Array<LokalnPrekladisko*>(24);
	VozovyPark vozPark = VozovyPark();
	Cas c = Cas();
	StatistickeData statistika = StatistickeData(zoznLokalnychPrekladisk,vozPark);
	structures::ArrayList<Objednavka*> zoznBalikovNaTriedenie = ArrayList<Objednavka*>();
public:
	CentralnySklad();
	~CentralnySklad();
	void pridajVozidlo();
	void pridajVoz(Vozidlo * voz);
	bool vytvorObjednavku();
	void pridajDrona();
	void vypisVozidla();
	void vypisDronyLokPr(string pLokPr);
	int getIndex(string pLokPr);
	void posunCasOMin();	
	void posunCas(int pMinuty);
	void naplnZoznLokalnychPrekladisk(const char * menoSuboru);
	void nacitajDronyZoSuboru(const char * menoSuboru);
	void zberBalikov();
	void rozvozBalikov();
	void nalozBalikyDoAut();
	double getVahaBalikov();	
	void vylozVozidla();
	void vypisDronySpolocnosti();
	void novyDenDron();
	void aktualizujPrevadzkoveNaklady();
	string getDatumCas();
	void testovacieObjednavky(const char *menoSuboru);
	void vypisRegioVKtBoloNajviacDorucenychZasielok();
	void vypisRegioZKtBoloNajviacOdoslanychZasielok();
	void vypisCelkovyPocetDorucenychZasielok();
	void vypisCelkoveNakladyVozidiel();
	void vypisCelkovyPocetNalietanychHodinVReg();

	void kontrolnyVypisObjednavok();
	void zapisStavDoSuboru(const char *menoSuboru);
	void nacitajStavZoSuboru(const char *menoSuboru);
	bool skontrolujNazovLP(string nazov);
};

