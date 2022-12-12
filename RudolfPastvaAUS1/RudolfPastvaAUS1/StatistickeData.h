#pragma once
#include "LokalnPrekladisko.h"
#include "VozovyPark.h"
class StatistickeData
{
	Array<LokalnPrekladisko*> *zoznLokPre;
	VozovyPark *vozovyPark;
public:
	StatistickeData(Array<LokalnPrekladisko*> &zoznLokalnychPrekladisk, VozovyPark &vozPark);
	~StatistickeData();
	void vypisRegioVKtBoloNajviacDorucenychZasielok();
	void vypisRegioZKtBoloNajviacOdoslanychZasielok();
	void vypisCelkovyPocetDorucenychZasielok();
	void vypisCelkoveNakladyVozidiel();
	void vypisCelkovyPocetNalietanychHodinVReg();
};

