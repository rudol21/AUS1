#include "Cas.h"
#include "struktury/heap_monitor.h"






Cas::Cas()
{
	
}

Cas::~Cas()
{
}

string Cas::getDatum()
{
	string hod = "";
	string min = "";
	if (hodina < 10)
	{
		hod = "0" ;
	}
	if (minuta < 10)
	{
		min = "0";
	}
	string retazec = to_string(den) +"." +to_string(mesiac) + "." + to_string(rok) +"[" +hod + to_string(hodina) + ":"+min + to_string(minuta)+"]";
	return retazec;
}

int Cas::getCas()
{
	return (hodina * 60) + minuta;
}



void Cas::posunCasOMinutu()
{
	minuta = minuta++;
	if (minuta == 60)
	{
		minuta = 0;
		hodina++;
		
	}
	if (hodina == 21 && minuta == 1)
	{
			hodina = 7;
			minuta = 0;
			den++;
			if (den == 32)
			{
				den = 1;
				mesiac++;
				if (mesiac == 13)
				{
					mesiac = 1;
					rok++;
				}
			}
		
	}
}

string Cas::toString()
{
	string retazec = to_string(den) +" "+ to_string(mesiac) +" "+ to_string(rok) +" "+ to_string((hodina * 60)+ minuta);
	return retazec;
}

void Cas::nacitajcas(ifstream &cin)
{
	int minuty;
	int cislo;
	cin >> den;
	cin >> mesiac;
	cin >> rok;
	cin >> minuty;
	hodina = minuty / 60;
	minuta = minuty - (hodina * 60);
	
}


