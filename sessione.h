#ifndef SESSIONE_H
#define SESSIONE_H
#include "giorno.h"

class Sessione
{
public:
	void initsessione(int giorni);
	void definetime(int annostart, int mesestart, int giornostart, int annoend, int meseend, int giornoend);
	void definegiornitot(int giornitot);
	std::string calcolagiorno(int gg, int mm, int aa);
	void definesesgiorni();
	bool bisestiles(int aa);
	void addgiorno(Giorno g);
	std::vector<Giorno> getsessgiornivec();
	void initsesgiornifascie();
	void initgiornistraordinario();
	std::string getanno();
	void setesameaddcorsotudioid(int i, int posi, std::string corsostudioid);
	void setesameaddcorsoid(int i, int j, std::string corsoid);

private:
	std::vector<Giorno> sesgiorni;
	int annostart;
	int annoend;
	int mesestart;
	int meseend;
	int giornostart;
	int giornoend;
	int giornitot;

};

#endif
