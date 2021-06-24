#ifndef CORSOBIG_H
#define CORSOBIG_H
#include <iostream>
#include <list>
#include <string>
#include "corso.h"


class Corsobig
{
public:
	void definegeneralinfo(std::string iddentifier, std::string idcorso, std::string titolo,int cfu,int orelezione,int orelab,int orees);
	void addcorso(Corso c);
	std::string getidentifier();
	std::string getidcorso();
	std::string gettitolo();
	int getcfu();
	int getorelezione();
	int getorelab();
	int getorees();
	std::vector<Corso> getcorsismall();
	void setattivo();
	void setnonattivo();
	int checkattivo();
	void selectionsortanni(std::vector<Corso> smallcorsi, int l, int r);
	int definesessione(int sessione);
	int getses();
	int getexamtime(std::string annoaccademico);
	void impostaesame();
	int checkesameimpostato();
	int checkesameimpostato2();
	void impostaesame2();


private:
	std::string identifier = "";
	std::string idcorso = "";
	std::string titolo = "";
	int cfu=-1;
	int orelezione = -1;
	int orelab = -1;
	int orees = -1;
	std::vector<Corso> corsianni;
	int sessione = -1;
	int esameimpostato = -1;

	
	

};



#endif
