#include "CentralnySklad.h"
#include <fstream>
#define TYP1RADIUS 26
#define TYP2RADIUS 20
using namespace std;
using namespace structures;

CentralnySklad::CentralnySklad()
{
	naplnZoznLokalnychPrekladisk("nazvyLokalnychPrekladisk.txt");
}


CentralnySklad::~CentralnySklad()
{	
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); ++i)
	{
		delete zoznLokalnychPrekladisk[i];
	}
	for (auto p : zoznBalikovNaTriedenie)
	{
		delete p;
	}
}

void CentralnySklad::pridajVozidlo()
{	
	vozPark.pridajVozidlo(c.getDatum());
}

void CentralnySklad::pridajVoz(Vozidlo * voz)
{
	vozPark.pridajVoz(voz);
}


void CentralnySklad::pridajDrona()
{
	string pLokPr;
	cout << "Zadajte lokalne prekladisko:";
	cin >> pLokPr;
	for(int i=0; i< zoznLokalnychPrekladisk.size(); i++)
		if (zoznLokalnychPrekladisk[i]->getNazovLokPr().compare(pLokPr) == 0)
		{
			zoznLokalnychPrekladisk[i]->pridajDrona(c.getDatum());
		}
}

void CentralnySklad::vypisVozidla()
{
	vozPark.vypisZoznam();	
}

void CentralnySklad::vypisDronyLokPr(string pLokPr)
{
	zoznLokalnychPrekladisk[getIndex(pLokPr)]->vypisDrony();
}

int CentralnySklad::getIndex(string pLokPr)
{
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
	{
		if (zoznLokalnychPrekladisk[i]->getNazovLokPr().compare(pLokPr) == 0)
		return i;
	}
}

void CentralnySklad::posunCasOMin()
{
	
	c.posunCasOMinutu();
	if (c.getCas() == 1260)
	{

		zberBalikov();
		rozvozBalikov();
		novyDenDron();
		c.posunCasOMinutu();
	}
	if (c.getCas() != 420)
	{
		for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
		{
			zoznLokalnychPrekladisk[i]->dobyKapacituBaterieDronom(c.getCas());
			if (!zoznLokalnychPrekladisk[i]->posliDronaVyzdvihnutZ(c.getCas()))//skontrolovat funkcnost
			{
				zoznLokalnychPrekladisk[i]->posliDronaZaniestZ(c.getCas());
			}
			zoznLokalnychPrekladisk[i]->priletDrona(c.getCas());

		}
	}
	
}

void CentralnySklad::posunCas(int pMinuty)
{
	for (int i = 0; i < pMinuty; i++)
	{
		posunCasOMin();
	}
}

bool CentralnySklad::vytvorObjednavku()
{
	double pHmotnost;
	string pRegionOdosielatela;
	int pVzdialenostOd;
	string pRegionPrijimatela;
	int pVzdialenostPrijimatela;
	cin >> pHmotnost >> pRegionOdosielatela >> pVzdialenostOd >> pRegionPrijimatela >> pVzdialenostPrijimatela;
	if (!(skontrolujNazovLP(pRegionOdosielatela) && skontrolujNazovLP(pRegionPrijimatela)))
	{
		cout << "Objednavka nebola prijata pretoze "<< pRegionOdosielatela <<" a "<< pRegionPrijimatela<<" niesu nazvy LP." << endl;
		return false;
	}
	if (pHmotnost > 5)
	{
		cout << "Objednavku nieje mozne vytvorit z dovodu prekrocenia hmotnosti." << endl;
		return false;
	}
	if (pHmotnost <= 2 && pVzdialenostOd > TYP1RADIUS || pVzdialenostPrijimatela > TYP1RADIUS)
	{
		cout << "Objednavku nieje mozne vytvorit z dovodu prekrocenia vzdialenosti." << endl;
		return false;
	}
	if (pHmotnost <= 5 && pHmotnost > 2 && pVzdialenostOd > TYP2RADIUS || pVzdialenostPrijimatela > TYP2RADIUS)
	{
		cout << "Objednavku nieje mozne vytvorit z dovodu prekrocenia vzdialenosti." << endl;
		return false;
	}
	if (zoznLokalnychPrekladisk[getIndex(pRegionOdosielatela)]->jeMoznePridatObjednavku(pVzdialenostOd, pHmotnost) && zoznLokalnychPrekladisk[getIndex(pRegionPrijimatela)]->jeMoznePridatZasielku(pVzdialenostPrijimatela, pHmotnost))
	{
		Objednavka * obj = new Objednavka(pHmotnost, pRegionOdosielatela, pVzdialenostOd, pRegionPrijimatela, pVzdialenostPrijimatela);
		zoznLokalnychPrekladisk[getIndex(pRegionOdosielatela)]->pridajNovuObjednavkuNaVyzdvihnutie(obj);
		zoznLokalnychPrekladisk[getIndex(pRegionPrijimatela)]->setRozvrhNaNaslDen(pVzdialenostPrijimatela,pHmotnost);
		zoznLokalnychPrekladisk[getIndex(pRegionOdosielatela)]->setRozvrhAktualnyDen(pVzdialenostOd,pHmotnost);
		cout << "Objednavka bola vytvorena." << endl;
		return true;
	}
	cout << "Nieje mozne vytvorit objednavku."<<endl;
	return false;
}

void CentralnySklad::naplnZoznLokalnychPrekladisk(const char * menoSuboru)
{
	int prvok = 0;
	string slovo;
	ifstream cin(menoSuboru);

	while (cin >> slovo)
	{
		LokalnPrekladisko *lp = new LokalnPrekladisko(slovo);
		zoznLokalnychPrekladisk[prvok]= lp;
		prvok++;
	}
	cin.close();
}

void CentralnySklad::nacitajDronyZoSuboru(const char * menoSuboru)
{
	int typ = -1;
	int index = 0;
	string serioveC;
	ifstream cin(menoSuboru);

	while (cin >> serioveC>>typ)
	{
		Dron *d = new Dron(serioveC, typ,c.getDatum());
		zoznLokalnychPrekladisk[index / 2]->pridajDron(d);
		index++;
	}
	cin.close();
}

void CentralnySklad::zberBalikov()
{
	for (int i = 0; i < vozPark.getPocetVozidiel(); i++)
	{
		if (vozPark.getVozidloNaIndexe(i)->getJeAutoRezervovane())
			vozPark.getVozidloNaIndexe(i)->zozbierajBaliky();
		else
			break;
	}
	aktualizujPrevadzkoveNaklady();
	vylozVozidla();
	

}

void CentralnySklad::rozvozBalikov()
{
	nalozBalikyDoAut();
	for (int i = 0; i < vozPark.getPocetVozidiel(); i++)
	{
		if (vozPark.getVozidloNaIndexe(i)->getJeAutoRezervovane())
			vozPark.getVozidloNaIndexe(i)->rozvezBaliky();
		else
			break;
	}
	zoznBalikovNaTriedenie.clear();
}

void CentralnySklad::nalozBalikyDoAut()
{
	int pocitadloVozidlo = 0;
	double aktualVaha = 0.0;
	vozPark.getVozidloNaIndexe(pocitadloVozidlo)->setJeRezervovane();
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
	{
		vozPark.getVozidloNaIndexe(pocitadloVozidlo)->pridajZastavkuDoTrasy(zoznLokalnychPrekladisk[i]);
		for (int j = 0; j < zoznBalikovNaTriedenie.size(); j++)
		{
			double aktualVaha = 0.0;
			if (zoznLokalnychPrekladisk[i]->getNazovLokPr().compare(zoznBalikovNaTriedenie[j]->getRegionPr()) == 0) 
			{
				if (vozPark.getVozidloNaIndexe(pocitadloVozidlo)->getNosnost() > aktualVaha + zoznBalikovNaTriedenie[j]->getHmZasielky())
				{
					vozPark.getVozidloNaIndexe(pocitadloVozidlo)->nalozBalikDoAuta(zoznBalikovNaTriedenie[j]);
					aktualVaha = aktualVaha + zoznBalikovNaTriedenie[j]->getHmZasielky();
				}
				else
				{
					pocitadloVozidlo++;
					vozPark.getVozidloNaIndexe(pocitadloVozidlo)->setJeRezervovane();
					vozPark.getVozidloNaIndexe(pocitadloVozidlo)->pridajZastavkuDoTrasy(zoznLokalnychPrekladisk[i]);
					vozPark.getVozidloNaIndexe(pocitadloVozidlo)->nalozBalikDoAuta(zoznBalikovNaTriedenie[j]);
					aktualVaha = zoznBalikovNaTriedenie[j]->getHmZasielky();
				}
				
			}
		}
	}
	
}

double CentralnySklad::getVahaBalikov()
{
	double pom = 0.0;
	for (int i = 0; i < zoznBalikovNaTriedenie.size(); i++)
	{
		pom = pom + zoznBalikovNaTriedenie[i]->getHmZasielky();
	}
	return pom;
}


void CentralnySklad::vylozVozidla()
{
	for (int i = 0; i < vozPark.getPocetVozidiel(); i++)
	{
		if (vozPark.getVozidloNaIndexe(i)->getJeAutoRezervovane())
			vozPark.getVozidloNaIndexe(i)->vylozVoz(zoznBalikovNaTriedenie);
		else
			break;
	}

}

/*void CentralnySklad::roztriedZoznBalikov()
{
	int pom = 0;
	ArrayList<Objednavka*> pomZozn = zoznBalikovNaTriedenie;
	zoznBalikovNaTriedenie.clear();
	while (pom< zoznLokalnychPrekladisk.size())
	{
		
		for (int i = 0; i < pomZozn.size(); i++)
		{
			if (zoznLokalnychPrekladisk[pom]->getNazovLokPr().compare(pomZozn[i]->getRegionPr()) == 0)
				zoznBalikovNaTriedenie.add(pomZozn[i]);
		}
		pom++;
	}
}*/

void CentralnySklad::vypisDronySpolocnosti()
{
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
	{
		zoznLokalnychPrekladisk[i]->vypisDrony();
	}	
}

void CentralnySklad::novyDenDron()
{
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
	{
		zoznLokalnychPrekladisk[i]->novyDenDron();
	}
}

void CentralnySklad::aktualizujPrevadzkoveNaklady()
{
	for (int i = 0; i < vozPark.getPocetVozidiel(); i++)
	{
		if (vozPark.getVozidloNaIndexe(i)->getJeAutoRezervovane())
			vozPark.getVozidloNaIndexe(i)->setCelkovePrevadzkoveNaklady();
		else
			break;
	}
}



string CentralnySklad::getDatumCas()
{
	return c.getDatum();
}

void CentralnySklad::vypisRegioVKtBoloNajviacDorucenychZasielok()
{
	statistika.vypisRegioVKtBoloNajviacDorucenychZasielok();
}

void CentralnySklad::vypisRegioZKtBoloNajviacOdoslanychZasielok()
{
	statistika.vypisRegioZKtBoloNajviacOdoslanychZasielok();
}

void CentralnySklad::vypisCelkovyPocetDorucenychZasielok()
{
	statistika.vypisCelkovyPocetDorucenychZasielok();
}

void CentralnySklad::vypisCelkoveNakladyVozidiel()
{
	statistika.vypisCelkoveNakladyVozidiel();
}

void CentralnySklad::vypisCelkovyPocetNalietanychHodinVReg()
{
	statistika.vypisCelkovyPocetNalietanychHodinVReg();
}





void CentralnySklad::kontrolnyVypisObjednavok()
{
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
	{
		zoznLokalnychPrekladisk[i]->kontrolnyVypis();
	}
}

void CentralnySklad::zapisStavDoSuboru(const char * menoSuboru)
{
	fstream zapisovac(menoSuboru);
	
	zapisovac << c.toString() << endl;
	zapisovac << zoznBalikovNaTriedenie.size() << endl;
	for (int i = 0; i < zoznBalikovNaTriedenie.size(); ++i)
	{
		zapisovac << zoznBalikovNaTriedenie[i]->toString() << endl;
	}
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); ++i)
	{
		zoznLokalnychPrekladisk[i]->zapisStavLPDoSuboru(zapisovac);
	}
	zapisovac << vozPark.getPocetVozidiel() << endl;
	for (int i = 0; i < vozPark.getPocetVozidiel(); ++i)
	{
		vozPark.getVozidloNaIndexe(i)->zapisDoSuboru(zapisovac);
	}

	zapisovac.close();
}

void CentralnySklad::nacitajStavZoSuboru(const char * menoSuboru)
{
	int pocet = 0;
	ifstream cin(menoSuboru);

	c.nacitajcas(cin);
	cin >> pocet;
	for (int i = 0; i < pocet; ++i)
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
		zoznBalikovNaTriedenie.add(obj);
	}
	for (int i = 0; i < zoznLokalnychPrekladisk.size(); ++i)
	{
		zoznLokalnychPrekladisk[i]->nacitajStavLPZoSuboru(cin);	
	}
	cin >> pocet;
	string pSpz, pDatumPridaniaDoEvidencie;
	double pNosnost;
	int pPrevadzkoveNaklady;
	bool maTrasu;
	string start, ciel;
	for (int i = 0; i < pocet; ++i)
	{
		cin >> pSpz;
		cin >> pNosnost;
		cin >> pPrevadzkoveNaklady;
		cin >> pDatumPridaniaDoEvidencie;
		Vozidlo *v = new Vozidlo( pSpz,  pNosnost,  pPrevadzkoveNaklady,  pDatumPridaniaDoEvidencie);
		v->nacitajZvysneUdajeVozidla(cin);
		
		if (v->getJeAutoRezervovane())
		{
			cin >> start >> ciel;
			for (int j = 0; j < zoznLokalnychPrekladisk.size(); ++j)
			{
				if (start.compare(zoznLokalnychPrekladisk[j]->getNazovLokPr()) == 0)
				{

					while (ciel.compare(zoznLokalnychPrekladisk[j]->getNazovLokPr()) != 0)
					{
						v->pridajZastavkuDoTrasy(zoznLokalnychPrekladisk[j]);
						++j;
					}
					v->pridajZastavkuDoTrasy(zoznLokalnychPrekladisk[j]);
				}
			}
		}
		vozPark.pridajVoz(v);
	}
	cin.close();
}

bool CentralnySklad::skontrolujNazovLP(string nazov)
{	
		for (int i = 0; i < zoznLokalnychPrekladisk.size(); i++)
		{
			if (zoznLokalnychPrekladisk[i]->getNazovLokPr().compare(nazov) == 0)
				return true;
		}	
		return false;

}
