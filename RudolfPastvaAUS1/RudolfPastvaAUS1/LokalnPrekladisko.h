#pragma once
#include "struktury/heap_monitor.h"
#include "struktury/array_list.h"
#include <iostream>
#include "Dron.h"
#include "struktury/explicit_queue.h"
#include "struktury/queue.h"
#include "struktury/linked_list.h"
#include <string>
#include <fstream>



using namespace std;
using namespace structures;
class LokalnPrekladisko
{
	string nazovLokPr;
	ArrayList<Dron*> dronyLokPrekladiska = ArrayList<Dron*>();
	ArrayList<Objednavka*> zoznZasielokNaTriedenie = ArrayList<Objednavka*>();
	ExplicitQueue<Objednavka*> zoznZasielokNaOdoslanie = ExplicitQueue<Objednavka*>();
	ExplicitQueue<Objednavka*> zoznObjednavokNaVyzdvihnutie = ExplicitQueue<Objednavka*>();
	int pocetDorucenychZasielokVRegione = 0;
	int pocetOdoslanychZasielokZRegiona = 0;
	int pocetZrusenychZasielokRegion = 0;
public:
	LokalnPrekladisko(string pNazovLokPr);
	~LokalnPrekladisko();
	void vymazZoznZasielokNaTriedenie();
	void pridajZasielkuNaOdoslanie(Objednavka *obj);
	Objednavka* odoberZasielkuNaOdoslanie();
	void pridajDrona(string pDatumPridaniaDoEvidencie);
	void pridajDron(Dron * d);
	bool posliDronaZaniestZ(int aktualnyCas);
	bool posliDronaVyzdvihnutZ(int aktualnyCas);
	void priletDrona(int aktualnyCas);
	void pridajNovuObjednavkuNaVyzdvihnutie(Objednavka *obj);
	Objednavka* odoberObjednavkuNaVyzdvihnutie();
	void pridajZasielkuNaTriedenie(Objednavka* zas);
	void vypisDrony();
	string getNazovLokPr();
	bool jeMoznePridatObjednavku(int pVzdialenostOd, double hmot);
	bool jeMoznePridatZasielku(int pVzdialenostOd, double hmot);
	void setRozvrhNaNaslDen(int pVzdialenostPrijimatela, double hmot);
	void setRozvrhAktualnyDen(int pVzdialenostOd, double hmot);
	double getVahaBalikovSmerujucichDoCS();
	ArrayList<Objednavka*> getBalikyNaTriedenie();
	void dobyKapacituBaterieDronom(int cas);
	void novyDenDron();
	int getPocetDorucenychZasielokVRegione();
	void setPocetDorucenychZasielokVRegione();
	int getPocetOdoslanychZasielokZRegiona();
	void setPocetOdoslanychZasielokZRegiona();
	string getPocetNalietanychHodDronov(int typDronu);
	bool jeCasVyzdvihnutiaZasielkyMenejAko1Hod();

	void kontrolnyVypis();
	void zapisStavLPDoSuboru(fstream &zapisovac);
	void nacitajStavLPZoSuboru(ifstream &cin);

};

