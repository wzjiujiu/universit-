#ifndef GIORNO_H
#define GIORNO_H
#include <iostream>
#include<sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include<string>
#include "corsostudio.h"
#include "corso.h"


class Giorno
{
public:
	void printfascie();
	void define(int anno, int mese, int giorno, std::string qualegiorno);
	std::string getqualegiorno();
	void initfascie();
	int corsistudioidpresente(std::vector<Corsostudio> corsistudiolist);
	int presentecorsostudioid(std::vector<Corsostudio> corsistudiolist, std::string id);
	int getanno();
	int getmese();
	int getgiorno();
	std::vector<std::string> getfascecorsiid();
	void addcorsiid(std::string id,int pos);
	void addcorsotudioid(std::string id,int pos);
	int getposiid(std::string id);
	void initstraordinario();
	void printgiorno(std::ofstream *fout);
	std::string getgiornodata();
private:
	int anno;
	int mese;
	int giorno;
	std::string qualegiorno;
	std::vector<std::string> fascecorsiid;
	std::vector<std::vector<std::string>> fascecorsistudioid;
	std::vector<int> straordinario;
	std::vector<std::vector<std::string>> motivostraordinario;
	std::string getfasciaoraria(int i);
	std::string getcorsostudioidcorr(int pos);

};

#endif
