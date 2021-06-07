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

std::string Corsobig::getidentifier()
{
	return this->identifier;
}
std::string Corsobig::getidcorso()
{
	return this->idcorso;
}
std::string Corsobig::gettitolo()
{
	return this->titolo;

}
int Corsobig::getcfu()
{
	return this->cfu;
}
int Corsobig::getorelezione()
{
	return this->orelezione;
}
int Corsobig::getorelab()
{
	return this->orelab;
}
int Corsobig::getorees()
{
	return this->orees;
}

std::vector<Corso> Corsobig:: getcorsismall()
{
	return this->corsianni;

}
int Corso::getentro()
{
	return this->t_entro;
}
int Corso::getesco()
{
	return this->t_esco;
}