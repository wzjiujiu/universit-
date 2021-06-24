#ifndef UNI_H
#define UNI_H

#include <iostream>
#include <string>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include <fstream>
#include "prof.h"
#include "corso.h"
#include "aula.h"
#include "corsobig.h"
#include "studente.h"
#include "corsobig.h"
#include "corsostudio.h"
#include <cctype>
#include "sessione.h"
#define BUF 500
#define N 500

class Uni
{

public:
	//corsi
	void getcorsi(char* filename, std::vector<Corsobig>* corsiout);
	Corso procede(Corso small, std::string info, int parallel, std::string corsoid, std::vector<Prof> profs);
	void procedeinto(char** map, int j, int start, int end, std::string info);
	int numprofcollab(char* string);
	std::string getmatricolatit(char* string);
	char* getcollabprofinfo(char* string, int j, int* end);
	std::vector<std::string> getcorsoidvec(std::string corsoid);
	std::vector<std::string> getesamiinfo(std::string esameinfo);
	void selectionsort(std::vector<Corso> smallcorsi, int l, int r);
	void generatedbcorsi(char* filename, std::vector<Corsobig> listcorsi);
	void getcorsifromdb(std::string filename, std::vector<Corsobig>* corsiout);
	int idnopresente(std::string id, std::vector<Corsobig> corsiout);
	Corso procede1(Corso small, std::string info, int parallel, std::string corsoid);
	void inseriscicorso(char* filename, std::vector<Corsobig>* corsiout,int *flag);
	int ereditabile(std::string attivo, int parallelo, std::string collabproinfo, std::string esamiinfo, std::string raggrupamento, int pos, int posc, std::vector<Corsobig> corsi, std::vector<Prof> profs,Corso *small,int riga,std::string corsoid);
	int annopresente(std::string anno, std::vector<Corsobig> corsi, std::string id);
	int getcorsopos(std::string id, std::vector<Corsobig> corsi);
	bool checkprofcollab(std::string info, int parallel, int pos, int posc, std::vector<Corsobig> corsi, std::vector<Prof> profs,Corso *small,std::string corsoid);
	void setokvet(int *ok, std::string *matricolatit,std::vector<std::string>* vect,int numcollabprof,int pos, int posc, std::vector<Corsobig> corsi,int set, std::vector<Prof> profs,int j);
	std::string getmatricolatit1(char* string);
	bool checkraggruppamenti(std::string raggrupamenti, std::vector<Corsobig> corsi,int* vuoto,Corso *small);
	bool ereditaesami(Corso* small, std::string esamiinfo,int pos, int posc, std::vector<Corsobig> corsi);
	int caricabile(std::string attivo, std::string parallelo, std::string collabproinfo, std::string esamiinfo, std::string raggrupamento, int pos, int posc, std::vector<Corsobig> corsi, std::vector<Prof> profs, Corso* small, int riga, std::string corsoid);
	int controlloparallel(int parallel, std::string collabprofinfo);
	int controllocollabprof(std::string collabprofinfo, int parallel, std::vector<Prof> profs);
	bool is_number(const std::string& s);
	int controlloesami(std::string esaminfo);
	int controlloraggrupamenti(std::string raggrupamentiinfo, std::vector<Prof> profs);
	Corso elaboracorsirag(Corso small, std::string info);
	std::vector<Corsostudio> modificacorsostudioafterinsert(std::string attivo, std::string id, std::vector<Corsostudio> corsistudi);
	//student

	void generetedbstudenti(char* filename, std::vector<Studente>listastudenti);
	std::vector <Studente> getstudenti(char* filename);
	std::vector<Studente>getstudentsfromdb(char* filename);
	std::vector<Studente> updatestudent(char* filename);

	//prof
	std::vector<Prof>getprofs(char* filename);
	void generetedbprofessori(char* filename, std::vector<Prof>listaprofessori);
	std::vector<Prof>getprofsfromdb(char* filename);
	std::vector<Prof> updateprof(char* filename);
	bool profinlist(std::vector<Prof>listaprofessori, std::string matricola);
	void chargeindtime(std::string filename, std::vector<Prof>* profs);
	void elaboratetime(std::string times, std::string profid,std::vector<Prof>* profs);
	int getprofpos(std::string id, std::vector<Prof> profs);
	void addind(int pos, std::string data, std::vector<Prof>* profs);

	//aula

	std::vector<Aula>getaule(char* filename);
	std::vector<Aula>getaulefromdb(FILE* fp);
	void generetedbaule(char* filename, std::vector<Aula>listaule);

	//esami

	void generateannoesamidata(char* annoaccademico, char* data1, char* data2, char* data3);
	int datainto(std::vector<std::string>d1, std::vector<std::string> d2, std::vector<std::string> d3, std::vector<std::string> anno, std::string filename);
	std::vector<std::string> getdata(std::vector<std::string> d, int pos);
	int getdif(std::vector<std::string>d1, std::vector<std::string> d2);
	bool datavalida(int gg, int mm, int aa);
	int giornimese(int aa, int mm);
	int assoluto(int gg);
	bool bisestile(int aa);
	int calcolagiorni(int gg, int mm, int aa);
	void generatefileindisponibilita(char* filename, char* annoaccademico);
	int checkdata(std::string data, std::string anno);
	int checkdatainside(std::string data, std::string anno);
	void generateesami(std::string annoaccademico, std::string fileoutname);
	void impostaesami(Sessione* s, std::vector<Corsostudio> corsistudiolist, std::vector<Corsobig> corsi, std::vector<Prof> profs,int ns,std::string annoaccademico);
	int programmauncorsoesame(Sessione* s, Corsobig *c, std::vector<Prof> profs, std::vector<Corsostudio> corsistudio, int ns,std::string corsostudioid,std::string idcorso, std::string annoaccademico);
	int programma1(Sessione* s, Corsobig* c, std::vector<Prof> profs, std::vector<Corsostudio> corsistudio, std::string corsostudioid, std::string annoaccademico);
	int programma2(Sessione* s, Corsobig *c, std::vector<Prof> profs, std::vector<Corsostudio> corsistudio, std::string corsostudioid, std::string annoaccademico);
	int profpresente(Corsobig *c, std::vector<Prof> profs, Giorno g, std::string annoaccademico);
	int checkcollabproftime(collabprof p, std::vector<Prof> profs, Giorno g);
	int getgiornofreepos(Giorno g,Corsobig *c, std::string annoaccademico);
	int setesame1(Sessione* s, Corsobig* c, int pos, std::string corsoid, std::string corsostudioid, int i);
	int setesame2(Sessione *s, Corsobig* c, int pos, std::string corsoid, std::string corsostudioid,int i);
	void generateesamefile(Sessione s, std::string anno, int si);
	//corsistudio

	std::vector<Corsostudio> getcorsostudiolist(char* filename);
	int corsostudioidinlist(std::string id, std::vector<Corsostudio> corsiout);
	int getsem(std::string info);
	void procedeintoc(char** map, int j, int start, int end, std::string info);
	int procedec(std::string info, int parallel, Corsostudio* c, std::vector<Corsobig> *corsi, int* flag);
	int setsessioni(char* info, int sessione, Corsostudio* c, std::vector<Corsobig> *corsi, int* flag);
	int checkattivo(std::string idcorso, std::vector<Corsobig> *corsi);
	std::vector<Corsostudio> getcorsostudiolistfromdb(std::string filename, std::vector<Corsobig>* corsiout);
	void setcorsispenti(std::string info, Corsostudio* c);
	void generatedbcorsistudio(char* filename, std::vector<Corsostudio>listcorsistudio);
	int corsisetsessioni(std::vector<Corsobig> *corsi, int sessione, std::string corsoid);
	//file
	int filework(std::ifstream& file);


private:




};




#endif
