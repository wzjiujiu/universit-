#include "corso.h"


collabprof Corso::createprof(std::string matricolatit, std::string matricola, int lezione, int es, int lab, std::string idcorso)
{
	collabprof p;
	p.es = es;
	p.idcorso = idcorso;
	p.lab = lab;
	p.matricola = matricola;
	p.lezione = lezione;
	p.matricolatit = matricolatit;
	return p;
	
}

void Corso::addprof(collabprof p)
{
	this->collabprofs.push_back(p);

}

void Corso::generaldefine(std::string identifier, std::string annoaccademico, int attivo, int verspar)
{
	this->attivo = attivo;
	this->annoaccademico = annoaccademico;
	this->identifier = identifier;
	this->verspar = verspar;
}
