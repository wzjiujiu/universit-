#ifndef CORSO_H
#define CORSO_H
#include <iostream>
#include <string>
#include <list>
typedef struct prof
{
	std::string matricola;
	int lezione;
	int es;
	int lab;
	std::string idcorso;
	std::string matricolatit;
}collabprof;

class Corso
{
public:
	collabprof createprof(std::string matricolatit,std::string matricola, int lezione, int es,int lab, std::string idcorso);
	void addprof(collabprof p);
	void generaldefine(std::string identifier, std::string annoaccademico, int attivo, int verspar);
 
private:
	std::string identifier = "";
	std::string annoaccademico = "";
	int attivo = -1;
	int verspar = -1;
	std::list<collabprof> collabprofs;
	int durataesame;
	int t_entro;
	int t_esco;
	std::string modalita = "";
	std::string luogo = "";


};


#endif
