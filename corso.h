#ifndef CORSO_H
#define CORSO_H
#include <iostream>
#include <string>
#include <vector>
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
	std::vector<collabprof> collabprofs;
	int durataesame=-1;
	int t_entro=-1;
	int t_esco=-1;
	std::string modalita = "";
	std::string luogo = "";


};


#endif
