#ifndef CORSO_H
#define CORSO_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
typedef struct prof
{
	std::string matricola;
	int lezione;
	int es;
	int lab;
	std::string idcorso;
	std::string matricolatit;
	int set;
	int num;
}collabprof;

class Corso
{
public:
	collabprof createprof(std::string matricolatit,std::string matricola, int lezione, int es,int lab, std::string idcorso,int set,int j);
	void addprof(collabprof p);
	void generaldefine( std::string id,std::string annoaccademico,std::string nome, int cfu,int lezione,int es, int lab, int verspar,int durataesame,int t_entro,int t_esco,std::string modalita,std::string luogo);
	std::string generateid();
	std::string getidentifier();
	std::string getnome();
	std::string getannoaccademico();
	int getdurataesame();
	std::string getid();
	int getcfu();
	int getlez();
	int getes();
	int getlab();
	void printprofs(int verspar,FILE *fp);
	std::string getcollabprof(int set);
	std::string getsingleprof(collabprof p);
	int getverpar();
	std::string getattivo();
	void printcorsiraggrupati( FILE* fp);
	std::string getmod();
	std::string getluogo();
	int getentro();
	int getesco();
	void generaldefinedb(std::string identifier, std::string annoaccademico, std::string attivo, int verspar, int durataesame, int t_entro, int t_esco, std::string modalita, std::string luogo);
	std::string getidtit(int verpar);
	void attivare();
	void spengnere();
	int controlloattivo();
	int getnumprofinoneset(int set);
	std::string getmatricolaprofcollab(int set, int num);
	int getlezprofcollab(int set, int num);
	int getesprofcollab(int set, int num);
	int getlabprofcollab(int set, int num);
	void addcorsirag(std::string corsoid);
	void defineluogo(std::string luogo);
	void definemod(std::string mod);
	void definedurata(int durataesame);
	void definet_entro(int t_entro);
	void definet_esco(int t_esco);
	void defineattivo(std::string attivo);
	std::vector<collabprof> getcollabprofvec();
	int getesametime();

	
 
private:
	std::string identifier = "a";
	std::string annoaccademico;
	std::string attivo;
	int verspar = -1;
	std::vector<collabprof> collabprofs;
	int durataesame=-1;
	int t_entro=-1;
	int t_esco=-1;
	std::string modalita;
	std::string luogo;
	std::vector<std::string> corsiragruppati;
	std::string id ;
	std::string nome;
	int lez=-1;
	int es=-1;
	int lab=-1;
	int cfu=-1;

	

};


#endif
