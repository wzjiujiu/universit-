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

private:
	std::string identifier = "";
	std::string idcorso = "";
	std::string titolo = "";
	int cfu=-1;
	int orelezione = -1;
	int orelab = -1;
	int orees = -1;
	std::vector<Corso> corsianni;
	

};



#endif
