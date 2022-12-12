
#include <stdio.h>
#include <iostream>

#include "struktury/structure.h"
#include "struktury/structure_iterator.h"
#include "struktury/array.h"
#include "struktury/vector.h"
#include "struktury/array_list.h"
#include "struktury/linked_list.h"
#include "struktury/list.h"
#include "struktury/ds_routines.h"
#include "struktury/ds_structure_types.h"
#include "struktury/queue.h"
#include "struktury/explicit_queue.h"

#include "LokalnPrekladisko.h"
#include "CentralnySklad.h"

using namespace std;
using namespace structures;

int main(){
	initHeapMonitor();
	
	CentralnySklad *cs = new CentralnySklad();
	int minuty = 0;
	int x = -1;
	/*cs->nacitajDronyZoSuboru("dronyTestovacie.txt");
	Vozidlo *v;
	v = new Vozidlo("CA700CE", 4.2, 51, cs->getDatumCas());
	cs->pridajVoz(v);
	v = new Vozidlo("CA560KA", 2.5, 38, cs->getDatumCas());
	cs->pridajVoz(v);
	v = new Vozidlo("ZA894FK", 4.7, 65, cs->getDatumCas());
	cs->pridajVoz(v);
	cs->nalozBalikyDoAut();*/
	cs->nacitajStavZoSuboru("dataSpolocnosti.txt");
	while (x != 0)
	{
		
		printf("Vyberte si moznost ");
		cout <<"("<< cs->getDatumCas() <<")"<< endl;
		printf("1 = Pridanie vozidla do spolocnosti.\n");
		printf("2 = Pridanie drona lokalnemu prekladisku.\n");
		printf("3 = Vytvorenie objednavky.\n");
		printf("4 = Posun cas.\n");
		printf("5 = Vypis vozidla a drony spolocnosti.\n");
		printf("6 = Vypis vsetky objednavky smerujuce do CentralnehoSkladu.\n");
		printf("7 = Vypis sumarnych statistik spolocnosti.\n");
		printf("0 = Koniec.\n");

		cin >> x;
		switch (x)
		{
		case 1:
			cout << "Zadajte: spz, nosnost vozidla.";
			cs->pridajVozidlo();
			break;
		case 2:
			cs->pridajDrona();
			break;
		case 3:
			cout << "Pre vytvorenie objednavky zadajte: hmotnost, region odosielatela, vzdialenostOd, region prijimatela, vzdialenostPr."<<endl;
			cs->vytvorObjednavku();
			break;
		case 4:
			
			cout << "Zadajte o kolko sa ma posunut cas v minutach: ";
			cin >> minuty;
			cs->posunCas(minuty);
			break;
		case 5:
			cout << "Vozidla spolocnosti Age of Express" << endl;
			cs->vypisVozidla();
			cout << "Drony jednotlivych prekladisk:" << endl;
			cs->vypisDronySpolocnosti();
			break;
		case 6:
			cs->kontrolnyVypisObjednavok();
			
			break;
		case 7:	
			cs->vypisRegioVKtBoloNajviacDorucenychZasielok();
			cs->vypisRegioZKtBoloNajviacOdoslanychZasielok();
			cs->vypisCelkovyPocetDorucenychZasielok();
			cs->vypisCelkoveNakladyVozidiel();
			cs->vypisCelkovyPocetNalietanychHodinVReg();
			break;
		case 0:
			cs->zapisStavDoSuboru("dataSpolocnosti.txt");
			delete cs;
			break;

		}
	}
	
}