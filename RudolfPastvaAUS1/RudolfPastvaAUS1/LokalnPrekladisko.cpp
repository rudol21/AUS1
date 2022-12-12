#include "LokalnPrekladisko.h"
#include "struktury/heap_monitor.h"

#define TYP1RADIUS 26
#define TYP2RADIUS 20
#define TYP1SPOTREBABATERIEZAMIN 2.50
#define TYP2SPOTREBABATERIEZAMIN 1.67
#define TYP1KMZAPOCMIN 0.75
#define TYP2KMZAPOCMIN 1.5


LokalnPrekladisko::LokalnPrekladisko(string pNazovLokPr)
{
	nazovLokPr = pNazovLokPr;
}


LokalnPrekladisko::~LokalnPrekladisko()
{
	for (auto p : dronyLokPrekladiska)
	{
		delete p;
	}
	
	for (auto p : zoznZasielokNaTriedenie)
	{
		delete p;
	}
	while (!zoznZasielokNaOdoslanie.isEmpty())
	{
		delete zoznZasielokNaOdoslanie.pop();
	}
	while (!zoznObjednavokNaVyzdvihnutie.isEmpty())
	{
		delete zoznObjednavokNaVyzdvihnutie.pop();
	}
}

void LokalnPrekladisko::vymazZoznZasielokNaTriedenie()
{
	zoznZasielokNaTriedenie.clear();
}

void LokalnPrekladisko::pridajZasielkuNaOdoslanie(Objednavka * obj)
{
	zoznZasielokNaOdoslanie.push(obj);
}
Objednavka* LokalnPrekladisko::odoberZasielkuNaOdoslanie()
{
	return zoznZasielokNaOdoslanie.pop();
}

void LokalnPrekladisko::pridajDrona(string pDatumPridaniaDoEvidencie)
{
	string pSerioveCis;
	int pTypDronu;
	cout << "Zadajte serioveCislo, typDronu(1/2): ";
	cin >> pSerioveCis >> pTypDronu;
	Dron *d = new Dron(pSerioveCis, pTypDronu, pDatumPridaniaDoEvidencie);
	dronyLokPrekladiska.add(d);
}

void LokalnPrekladisko::pridajDron(Dron * d)
{
	dronyLokPrekladiska.add(d);
}

bool LokalnPrekladisko::posliDronaZaniestZ(int aktualnyCas)
{
	Objednavka *obj = nullptr;
	double hmot;
	int dobaLetu;  
	
	if (!zoznZasielokNaOdoslanie.isEmpty())
	{
		obj = zoznZasielokNaOdoslanie.peek();
		hmot = obj->getHmZasielky();
		
		if (hmot <= 2)
		{
			dobaLetu = obj->getVzdialenostOd() * 2 * TYP1KMZAPOCMIN;
			for (int i = 0; i < dronyLokPrekladiska.size(); i++)
			{
				if (dronyLokPrekladiska[i]->getTypDronu() == 1 && dronyLokPrekladiska[i]->getJeDronVolny() && dronyLokPrekladiska[i]->getKapacitaBaterie() > (dobaLetu * 2.5))
				{
					
					dronyLokPrekladiska[i]->setJeDronVolny();
					dronyLokPrekladiska[i]->setCasPriletu(aktualnyCas + dobaLetu);
					dronyLokPrekladiska[i]->setPocetPrepZas();
					dronyLokPrekladiska[i]->odoberKapacituBaterie(dobaLetu);
					dronyLokPrekladiska[i]->setNalietaneHodiny(dobaLetu);
					obj = zoznZasielokNaOdoslanie.pop();
					setPocetDorucenychZasielokVRegione();
					delete obj;
					
					return true;
				}
			}
		}
		if (hmot <= 5)
		{
			dobaLetu = obj->getVzdialenostOd() * 2 * TYP2KMZAPOCMIN;
			for (int i = 0; i < dronyLokPrekladiska.size(); i++)
			{
				if (dronyLokPrekladiska[i]->getTypDronu() == 2 && dronyLokPrekladiska[i]->getJeDronVolny() && dronyLokPrekladiska[i]->getKapacitaBaterie() > (dobaLetu * 1.67))
				{
					
					dronyLokPrekladiska[i]->setJeDronVolny();
					dronyLokPrekladiska[i]->setCasPriletu(aktualnyCas + dobaLetu);
					dronyLokPrekladiska[i]->setPocetPrepZas();
					dronyLokPrekladiska[i]->odoberKapacituBaterie(dobaLetu);
					dronyLokPrekladiska[i]->setNalietaneHodiny(dobaLetu);
					obj = zoznZasielokNaOdoslanie.pop();
					setPocetDorucenychZasielokVRegione();
					delete obj;
					return true;
				}
			}
		}

		return false;
	}
}
bool LokalnPrekladisko::posliDronaVyzdvihnutZ(int aktualnaCas)
{
	Objednavka *obj = nullptr;
	double hmot;
	int dobaLetu;
	if (!zoznObjednavokNaVyzdvihnutie.isEmpty())
	{
		obj = zoznObjednavokNaVyzdvihnutie.peek();
		hmot = obj->getHmZasielky();

		if (hmot <= 2)
		{
			dobaLetu = obj->getVzdialenostOd() * 2 * TYP1KMZAPOCMIN;
			for (int i = 0; i < dronyLokPrekladiska.size(); i++)
			{
				if (dronyLokPrekladiska[i]->getCasKedyJeDronVolnyAktDen() < 1080 || aktualnaCas > 1080)
				{
					if (dronyLokPrekladiska[i]->getTypDronu() == 1 && dronyLokPrekladiska[i]->getJeDronVolny() && dronyLokPrekladiska[i]->getKapacitaBaterie() > (dobaLetu * TYP1SPOTREBABATERIEZAMIN))
					{
						dronyLokPrekladiska[i]->setJeDronVolny();
						dronyLokPrekladiska[i]->setCasPriletu(aktualnaCas + dobaLetu);
						dronyLokPrekladiska[i]->zoberBalik(obj);
						dronyLokPrekladiska[i]->setPocetPrepZas();
						dronyLokPrekladiska[i]->odoberKapacituBaterie(dobaLetu);
						dronyLokPrekladiska[i]->setNalietaneHodiny(dobaLetu);
						obj = zoznObjednavokNaVyzdvihnutie.pop();
						setPocetOdoslanychZasielokZRegiona();
						return true;
					}
				}
			}
		}
		if (hmot <= 5)
		{
			dobaLetu = obj->getVzdialenostOd() * 2 * TYP2KMZAPOCMIN;
			for (int i = 0; i < dronyLokPrekladiska.size(); i++)
			{
				if (dronyLokPrekladiska[i]->getCasKedyJeDronVolnyAktDen() < 1080 || aktualnaCas > 1080)
				{
					if (dronyLokPrekladiska[i]->getTypDronu() == 2 && dronyLokPrekladiska[i]->getJeDronVolny() && dronyLokPrekladiska[i]->getKapacitaBaterie() > (dobaLetu * TYP2SPOTREBABATERIEZAMIN))
					{
						dronyLokPrekladiska[i]->setJeDronVolny();
						dronyLokPrekladiska[i]->setCasPriletu(aktualnaCas + dobaLetu);
						dronyLokPrekladiska[i]->zoberBalik(obj);
						dronyLokPrekladiska[i]->setPocetPrepZas();
						dronyLokPrekladiska[i]->odoberKapacituBaterie(dobaLetu);
						dronyLokPrekladiska[i]->setNalietaneHodiny(dobaLetu);
						obj = zoznObjednavokNaVyzdvihnutie.pop();
						setPocetOdoslanychZasielokZRegiona();
						return true;
					}
				}
			}
		}

	}
	return false;
}

void LokalnPrekladisko::priletDrona(int aktualnyCas)
{
	for (int i = 0; i < dronyLokPrekladiska.size(); i++)
	{
		if (dronyLokPrekladiska[i]->getCasPriletu() == aktualnyCas)
		{
			dronyLokPrekladiska[i]->setJeDronVolny();
			if (dronyLokPrekladiska[i]->getBalik() != nullptr)
			{
				zoznZasielokNaTriedenie.add(dronyLokPrekladiska[i]->getBalik());
				dronyLokPrekladiska[i]->vylozBalik();
			}
		}
	}
}

void LokalnPrekladisko::pridajNovuObjednavkuNaVyzdvihnutie(Objednavka * obj)
{
	zoznObjednavokNaVyzdvihnutie.push(obj);
}
Objednavka* LokalnPrekladisko::odoberObjednavkuNaVyzdvihnutie()
{
	return zoznObjednavokNaVyzdvihnutie.pop();
}

void LokalnPrekladisko::pridajZasielkuNaTriedenie(Objednavka * zas)
{
	zoznZasielokNaTriedenie.add(zas);
}

void LokalnPrekladisko::vypisDrony()
{
	cout << "Lokalne prekladisko " << nazovLokPr << endl;
	for (int i = 0; i < dronyLokPrekladiska.size(); i++)
	{
		cout << dronyLokPrekladiska[i]->toString() << endl;
	}
}
string LokalnPrekladisko::getNazovLokPr()
{
	return nazovLokPr;
}

bool LokalnPrekladisko::jeMoznePridatObjednavku(int pVzdialenostOd, double hmot)
{
	int dobaLetu = 0;
	int vybratyDron = -1;
	if (hmot <= 2)
	{
		if (pVzdialenostOd > TYP1RADIUS)
			return false;
		dobaLetu = (pVzdialenostOd) * TYP1KMZAPOCMIN;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				vybratyDron = i;
				break;
			}
		}
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasPriletu() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu)) > (dronyLokPrekladiska[i]->getCasPriletu() + dronyLokPrekladiska[i]->getPotrebnyCasNaDobitie(dobaLetu)))
					vybratyDron = i;
				
			}
		}
		if (vybratyDron != -1)
		{
			if ((dronyLokPrekladiska[vybratyDron]->getCasPriletu() + (dobaLetu * 2 * 2.5) / 3.34 + dobaLetu * 2) < 1260)
				return true;
		}
	}
	if (hmot <= 5)
	{
		if (pVzdialenostOd > TYP2RADIUS)
			return false;
		dobaLetu = (pVzdialenostOd) * TYP2KMZAPOCMIN;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				vybratyDron = i;
				break;
			}
		}
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
   			    if ((dronyLokPrekladiska[vybratyDron]->getCasPriletu() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu)) > (dronyLokPrekladiska[i]->getCasPriletu() + dronyLokPrekladiska[i]->getPotrebnyCasNaDobitie(dobaLetu)))
				vybratyDron = i;
			}
		}
		if (vybratyDron != -1)
		{
			if ((dronyLokPrekladiska[vybratyDron]->getCasPriletu() + (dobaLetu * 2 * TYP2SPOTREBABATERIEZAMIN) / 2 + dobaLetu * 2) < 1260)
				return  true;
		}
	}
	return false;

}

bool LokalnPrekladisko::jeMoznePridatZasielku(int pVzdialenostPrijimatela, double hmot)
{
	int dobaLetu = 0;
	int vybratyDron = -1;
	if (hmot <= 2)
	{
		dobaLetu = (pVzdialenostPrijimatela) * TYP1KMZAPOCMIN;
		if (pVzdialenostPrijimatela > TYP1RADIUS)
			return false;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				vybratyDron = i;
				break;
			}
		}
		
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu)) > (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[i]->getPotrebnyCasNaDobitie(dobaLetu)))
					vybratyDron = i;					
			}
		}
		if (vybratyDron != -1)
		{
			if (dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu) + dobaLetu < 1080)
				return true;
		}
	}

	if (hmot <= 5)
	{
		if (pVzdialenostPrijimatela > TYP2RADIUS)
			return false;
		dobaLetu = (pVzdialenostPrijimatela) * TYP2KMZAPOCMIN;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				vybratyDron = i;
				break;
			}
		}
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu)) > (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[i]->getPotrebnyCasNaDobitie(dobaLetu)))
					vybratyDron = i;								
			}
		}
		if (vybratyDron != -1)
		{
			if (dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu) + dobaLetu < 1080)
				return true;
		}
	}
	return false;
}
void LokalnPrekladisko::setRozvrhNaNaslDen(int pVzdialenostPrijimatela, double hmot)
{

	int vybratyDron = -1;
	int dobaLetu = 0;
	int pomocnyCas = 0;
	if (hmot <= 2)
	{
		dobaLetu = (pVzdialenostPrijimatela) * TYP1KMZAPOCMIN;
		
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				vybratyDron = i;
				break;
			}
		}

		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu)) > (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[i]->getPotrebnyCasNaDobitie(dobaLetu)))
					vybratyDron = i;
			}
		}
		pomocnyCas = dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + (dobaLetu*2) + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu);
		if (vybratyDron != -1)
		{
			if (dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu) + dobaLetu < 1080)
			{
				dronyLokPrekladiska[vybratyDron]->setCasKedyJeDronVolnyNaslDen(pomocnyCas);
				dronyLokPrekladiska[vybratyDron]->setKapacitaBaterievCaseKedyJeDronVolnyNaslDen(dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu), dobaLetu * 2);
			}
			else
				vybratyDron = -1;
		}
		
		/*dobaLetu = (pVzdialenostPrijimatela) * 0.75;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				
				if (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + dobaLetu < 1260)
				{
					if (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() < pomocnyCasKedyJeDronVolny)
					{
						pomocnyCasKedyJeDronVolny = dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen();
						pomocny = dronyLokPrekladiska[i];
						pomocnyCas = dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + (2 * dobaLetu) + (((2 * dobaLetu)*TYP1SPOTREBABATERIEZAMIN)*0.3);
					}
				}
			}
		}*/
	}
	if (hmot <= 5 && vybratyDron == -1)
	{
		dobaLetu = (pVzdialenostPrijimatela) * TYP2KMZAPOCMIN;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				vybratyDron = i;
				break;
			}
		}

		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu)) > (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[i]->getPotrebnyCasNaDobitie(dobaLetu)))
					vybratyDron = i;
			}
		}
		pomocnyCas = dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + (2 * dobaLetu) + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu);
		if (vybratyDron != -1)
		{
			if (dronyLokPrekladiska[vybratyDron]->getCasKedyJeDrVolnyNaslDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu) + dobaLetu < 1080)
			{
				dronyLokPrekladiska[vybratyDron]->setCasKedyJeDronVolnyNaslDen(pomocnyCas);
				dronyLokPrekladiska[vybratyDron]->setKapacitaBaterievCaseKedyJeDronVolnyNaslDen(dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaDobitie(dobaLetu), dobaLetu * 2);
			}
			else
				vybratyDron = -1;
		}
		/*for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				dobaLetu = (pVzdialenostPrijimatela) * 1.5;
				if (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + dobaLetu < 1260)
				{
					if (dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() < pomocnyCasKedyJeDronVolny)
					{
						pomocnyCasKedyJeDronVolny = dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen();
						pomocny = dronyLokPrekladiska[i];
						pomocnyCas = dronyLokPrekladiska[i]->getCasKedyJeDrVolnyNaslDen() + (2 * dobaLetu) + (((2 * dobaLetu)*TYP2SPOTREBABATERIEZAMIN)*0.0);
					}
				}
			}
		}*/
	}
	
}

void LokalnPrekladisko::setRozvrhAktualnyDen(int pVzdialenostOd, double hmot)
{
	int vybratyDron = -1;
	int dobaLetu = 0;
	int pomocnyCas = 0;

	if (hmot <= 2)
	{
		dobaLetu = (pVzdialenostOd) * TYP1KMZAPOCMIN;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				vybratyDron = i;
				break;
			}
		}

		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 1)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasKedyJeDronVolnyAktDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaNabitieNaCestu(dobaLetu)) > (dronyLokPrekladiska[i]->getCasKedyJeDronVolnyAktDen() + dronyLokPrekladiska[i]->getPotrebnyCasNaNabitieNaCestu(dobaLetu)))
					vybratyDron = i;
			}
		}
		pomocnyCas = dronyLokPrekladiska[vybratyDron]->getCasKedyJeDronVolnyAktDen() + (2 * dobaLetu) + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaNabitieNaCestu(dobaLetu);
		if (vybratyDron != -1)
		{
			if (dronyLokPrekladiska[vybratyDron]->getCasKedyJeDronVolnyAktDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaNabitieNaCestu(dobaLetu) + dobaLetu < 1260)
				dronyLokPrekladiska[vybratyDron]->setCasKedyJeDronVolnyAktDen(pomocnyCas);
			else
				vybratyDron = -1;
		}
	}
	if (hmot <= 5 && vybratyDron == -1)
	{
		dobaLetu = (pVzdialenostOd) * TYP2KMZAPOCMIN;
		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				vybratyDron = i;
				break;
			}
		}

		for (int i = 0; i < dronyLokPrekladiska.size(); i++)
		{
			if (dronyLokPrekladiska[i]->getTypDronu() == 2)
			{
				if ((dronyLokPrekladiska[vybratyDron]->getCasKedyJeDronVolnyAktDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaNabitieNaCestu(dobaLetu)) > (dronyLokPrekladiska[i]->getCasKedyJeDronVolnyAktDen() + dronyLokPrekladiska[i]->getPotrebnyCasNaNabitieNaCestu(dobaLetu)))
					vybratyDron = i;
			}
		}
		pomocnyCas = dronyLokPrekladiska[vybratyDron]->getCasKedyJeDronVolnyAktDen() + (2 * dobaLetu) + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaNabitieNaCestu(dobaLetu);
		if (vybratyDron != -1)
		{
			if (dronyLokPrekladiska[vybratyDron]->getCasKedyJeDronVolnyAktDen() + dronyLokPrekladiska[vybratyDron]->getPotrebnyCasNaNabitieNaCestu(dobaLetu) + dobaLetu < 1080)
				dronyLokPrekladiska[vybratyDron]->setCasKedyJeDronVolnyAktDen(pomocnyCas);
			else
				vybratyDron = -1;
		}
	}
	
}

double LokalnPrekladisko::getVahaBalikovSmerujucichDoCS()
{
	double pom = 0.0;
	for (int i = 0; i < zoznZasielokNaTriedenie.size(); i++)
	{
		pom = pom + zoznZasielokNaTriedenie[i]->getHmZasielky();
	}

	return pom;
}

ArrayList<Objednavka*> LokalnPrekladisko::getBalikyNaTriedenie()
{
	return zoznZasielokNaTriedenie;
}

void LokalnPrekladisko::dobyKapacituBaterieDronom(int cas)
{
	for (int i = 0; i < dronyLokPrekladiska.size(); i++)
	{

		if(dronyLokPrekladiska[i]->getJeDronVolny())
		dronyLokPrekladiska[i]->setKapacitaBaterie(1);
		if (dronyLokPrekladiska[i]->getCasKedyJeDronVolnyAktDen() < cas)
			dronyLokPrekladiska[i]->setCasKedyJeDronVolnyAktDen(cas);
	}
}

void LokalnPrekladisko::novyDenDron()
{
	for (int i = 0; i < dronyLokPrekladiska.size(); i++)
	{
		dronyLokPrekladiska[i]->novyden();
	}
}

int LokalnPrekladisko::getPocetDorucenychZasielokVRegione()
{
	return pocetDorucenychZasielokVRegione;
}

void LokalnPrekladisko::setPocetDorucenychZasielokVRegione()
{
	pocetDorucenychZasielokVRegione++;
}

int LokalnPrekladisko::getPocetOdoslanychZasielokZRegiona()
{
	return pocetOdoslanychZasielokZRegiona;
}

void LokalnPrekladisko::setPocetOdoslanychZasielokZRegiona()
{
	pocetOdoslanychZasielokZRegiona++;
}

string LokalnPrekladisko::getPocetNalietanychHodDronov(int typDronu)
{
	int nalietaneHodiny = 0;
	string retazec,pomRet;
	int hod, min;
	for (int i = 0; i < dronyLokPrekladiska.size(); i++)
	{
		if (dronyLokPrekladiska[i]->getTypDronu() == typDronu)
			nalietaneHodiny = nalietaneHodiny + dronyLokPrekladiska[i]->getNalietaneHodiny();
	}
	hod = nalietaneHodiny / 60;
	min = nalietaneHodiny - (hod * 60);
	if (min < 10)
		pomRet = "0";
	else
		pomRet = "";
	retazec = "Nalietane hodiny dronov TYP" + to_string(typDronu) + ": " + to_string(hod) + ":" + pomRet + to_string(min) + "hod.";
		return retazec;
}

bool LokalnPrekladisko::jeCasVyzdvihnutiaZasielkyMenejAko1Hod()
{
	//zoznObjednavokNaVyzdvihnutie
	//dronyLokPrekladiska
	return false;
}

void LokalnPrekladisko::kontrolnyVypis()
{
	cout << "Lokalne prekladisko: " + nazovLokPr << endl<<"zoznZasielokNaTriedenie= "<<endl;
	for (int i = 0; i < zoznZasielokNaTriedenie.size(); i++)
	{
		cout << zoznZasielokNaTriedenie[i]->getHmZasielky() << zoznZasielokNaTriedenie[i]->getRegionOd() << zoznZasielokNaTriedenie[i]->getRegionPr() << zoznZasielokNaTriedenie[i]->getVzdialenostOd() << zoznZasielokNaTriedenie[i]->getVzdialenostPr() << endl;
	}
	cout << endl;
	
}



void LokalnPrekladisko::zapisStavLPDoSuboru(fstream &zapisovac)
{
	ExplicitQueue<Objednavka*> duplikat1 = ExplicitQueue<Objednavka*>();
	ExplicitQueue<Objednavka*> duplikat2 = ExplicitQueue<Objednavka*>();

	duplikat1 = ExplicitQueue<Objednavka*>(zoznZasielokNaOdoslanie);
	duplikat2 = ExplicitQueue<Objednavka*>(zoznObjednavokNaVyzdvihnutie);

	zapisovac << to_string(zoznZasielokNaTriedenie.size()) <<endl;
	for (int i = 0; i < zoznZasielokNaTriedenie.size(); i++)
	{
		zapisovac << zoznZasielokNaTriedenie[i]->toString()<<endl;
	}
	zapisovac << to_string(zoznZasielokNaOdoslanie.size()) << endl;
	for (int i = 0; i < zoznZasielokNaOdoslanie.size(); i++)
	{
		zapisovac << duplikat1.pop()->toString() << endl;
	}
	zapisovac << to_string(zoznObjednavokNaVyzdvihnutie.size()) << endl;
	for (int i = 0; i < zoznObjednavokNaVyzdvihnutie.size(); i++)
	{
		zapisovac << duplikat2.pop()->toString() << endl;
	}
	zapisovac << pocetDorucenychZasielokVRegione << " " << pocetOdoslanychZasielokZRegiona << " " << pocetZrusenychZasielokRegion << endl;
	zapisovac << dronyLokPrekladiska.size() << endl;
	for (int i = 0; i < dronyLokPrekladiska.size(); i++)
	{
		zapisovac << dronyLokPrekladiska[i]->toStringPreZapisDouboru()<<endl;
		if (!dronyLokPrekladiska[i]->getJeDronVolny())
			zapisovac << dronyLokPrekladiska[i]->getBalik()->toString() << endl;
	}
}

void LokalnPrekladisko::nacitajStavLPZoSuboru(ifstream & cin)
{
	double pHmotnost;
	string pRegionOdosielatela, pRegionPrijimatela;
	int pVzdialenostOd, pVzdialenostPr;
	int pocet;
	cin >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		cin >> pHmotnost;
		cin >> pRegionOdosielatela;
		cin >> pVzdialenostOd;
		cin >> pRegionPrijimatela;
		cin >> pVzdialenostPr;
		Objednavka * obj = new Objednavka(pHmotnost, pRegionOdosielatela, pVzdialenostOd, pRegionPrijimatela, pVzdialenostPr);
		zoznZasielokNaTriedenie.add(obj);
	}
	cin >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		cin >> pHmotnost;
		cin >> pRegionOdosielatela;
		cin >> pVzdialenostOd;
		cin >> pRegionPrijimatela;
		cin >> pVzdialenostPr;
		Objednavka * obj = new Objednavka(pHmotnost, pRegionOdosielatela, pVzdialenostOd, pRegionPrijimatela, pVzdialenostPr);
		zoznZasielokNaOdoslanie.push(obj);
	}
	cin >> pocet;
	for (int i = 0; i < pocet; ++i)
	{	
		cin >> pHmotnost;
		cin >> pRegionOdosielatela;
		cin >> pVzdialenostOd;
		cin >> pRegionPrijimatela;
		cin >> pVzdialenostPr;
		Objednavka * obj = new Objednavka(pHmotnost, pRegionOdosielatela, pVzdialenostOd, pRegionPrijimatela, pVzdialenostPr);
		zoznObjednavokNaVyzdvihnutie.push(obj);
	}
	cin >> pocetDorucenychZasielokVRegione >> pocetOdoslanychZasielokZRegiona >> pocetZrusenychZasielokRegion;

	string pSerioveCis, pDatumPridaniaDoEvidencie;
	int pTypDronu;
	cin >> pocet;
	for (int i = 0; i < pocet; i++)
	{
		cin >> pSerioveCis >> pTypDronu >> pDatumPridaniaDoEvidencie;
		Dron *d = new Dron(pSerioveCis, pTypDronu, pDatumPridaniaDoEvidencie);	
		d->nacitajZvysneUdaje(cin);
		dronyLokPrekladiska.add(d);
		if (!(d->getJeDronVolny()))
		{
			cin >> pHmotnost;
			cin >> pRegionOdosielatela;
			cin >> pVzdialenostOd;
			cin >> pRegionPrijimatela;
			cin >> pVzdialenostPr;
			Objednavka * obj = new Objednavka(pHmotnost, pRegionOdosielatela, pVzdialenostOd, pRegionPrijimatela, pVzdialenostPr);
			d->zoberBalik(obj);
		}
	}
	
	
}


