#include "corsobig.h"

void Corsobig::definegeneralinfo(std::string identifier, std::string idcorso, std::string titolo, int cfu, int orelezione, int orelab, int orees)
{
	this->identifier = identifier;
	this->idcorso = idcorso;
	this->titolo = titolo;
	this->cfu = cfu;
	this->orelezione = orelezione;
	this->orelab = orelab;
	this->orees = orees;
}

void Corsobig::addcorso(Corso c)
{
	this->corsianni.push_back(c);

}
