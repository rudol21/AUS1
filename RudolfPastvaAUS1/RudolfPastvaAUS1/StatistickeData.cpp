#include "StatistickeData.h"






StatistickeData::StatistickeData(Array<LokalnPrekladisko*> &zoznLokalnychPrekladisk, VozovyPark &vozPark)
{
	zoznLokPre = &zoznLokalnychPrekladisk;
	vozovyPark = &vozPark;
}

StatistickeData::~StatistickeData()
{
}
void StatistickeData::vypisRegioVKtBoloNajviacDorucenychZasielok()
{
	int najviacZasielok = (*zoznLokPre)[0]->getPocetDorucenychZasielokVRegione();
	int index = 0;
	for (int i = 1; i < (*zoznLokPre).size(); i++)
	{
		if (najviacZasielok < (*zoznLokPre)[i]->getPocetDorucenychZasielokVRegione())
		{
			najviacZasielok = (*zoznLokPre)[i]->getPocetDorucenychZasielokVRegione();
			index = i;
		}
	}
	cout << "Najviac zasielok bolo dorucenych do regionu " << (*zoznLokPre)[index]->getNazovLokPr() << " s celkovym poctom: " << (*zoznLokPre)[index]->getPocetDorucenychZasielokVRegione() << endl;
}

void StatistickeData::vypisRegioZKtBoloNajviacOdoslanychZasielok()
{
	int najviacOdoslanych = (*zoznLokPre)[0]->getPocetOdoslanychZasielokZRegiona();
	int index = 0;
	for (int i = 1; i < (*zoznLokPre).size(); i++)
	{
		if (najviacOdoslanych < (*zoznLokPre)[i]->getPocetOdoslanychZasielokZRegiona())
		{
			najviacOdoslanych = (*zoznLokPre)[i]->getPocetOdoslanychZasielokZRegiona();
			index = i;
		}
	}
	cout << "Najviac zasielok bolo odoslanych z regiona " << (*zoznLokPre)[index]->getNazovLokPr() << " s celkovym poctom: " << (*zoznLokPre)[index]->getPocetOdoslanychZasielokZRegiona() << endl;

}

void StatistickeData::vypisCelkovyPocetDorucenychZasielok()
{
	int celkovyPocetDorucenych = (*zoznLokPre)[0]->getPocetOdoslanychZasielokZRegiona();
	for (int i = 0; i < (*zoznLokPre).size(); i++)
	{
		celkovyPocetDorucenych = celkovyPocetDorucenych + (*zoznLokPre)[i]->getPocetDorucenychZasielokVRegione();
	}
	cout << "Celkovy pocet dorucenych zasielok: " << celkovyPocetDorucenych << endl;

}

void StatistickeData::vypisCelkoveNakladyVozidiel()
{
	cout << "Celkove naklady vozidiel ktore vlastny spolocnost su: " << (*vozovyPark).getCelkoveNakladyVozidiel() << "eur" << endl;
}

void StatistickeData::vypisCelkovyPocetNalietanychHodinVReg()
{
	for (int i = 0; i < (*zoznLokPre).size(); i++)
	{
		cout << "Region: " + (*zoznLokPre)[i]->getNazovLokPr() << endl << (*zoznLokPre)[i]->getPocetNalietanychHodDronov(1) << endl << (*zoznLokPre)[i]->getPocetNalietanychHodDronov(2) << endl;
	}
}
