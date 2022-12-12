#pragma once
#include <string>
#include "struktury/heap_monitor.h"
using namespace std;
class Objednavka
{
	double hmotnostZasielky;
	string regionOdosielatela;
	int vzdialenostOdosielatela;
	string regionPrijimatela;
	int vzdialenostPrijimatela;

public:
	Objednavka(double pHmotnost, string pRegionOdosielatela, int pVzdialenostOd, string pRegionPrijimatela, int pVzdialenostPrijimatela);
	~Objednavka();
	double getHmZasielky();
	string getRegionOd();
	string getRegionPr();
	int getVzdialenostOd();
	int getVzdialenostPr();
	string toString();


};

