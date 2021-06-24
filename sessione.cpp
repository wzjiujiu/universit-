#include "sessione.h"

void Sessione::initsessione(int giorni)
{
	
}
void Sessione::definetime(int annostart, int mesestart, int giornostart, int annoend, int meseend, int giornoend)
{
	this->annostart = annostart;
	this->mesestart = mesestart;
	this->giornostart = giornostart;
	this->annoend = annoend;
	this->meseend = meseend;
	this->giornoend = giornoend;
}

void Sessione::definegiornitot(int giornitot)
{
	this->giornitot = giornitot;
}

std::string Sessione::calcolagiorno(int gg, int mm, int aa)
{
	int n1, n2, n3, x = 0, t;
	int mesi[13] = { 1,31,59,90,120,151,181,212,243,273,304,334,365 };
	n1=gg;
	n2=mm;
	n3=aa;

	if (n3 > 1582)
	{
		x = n3 + (n3 - 1) / 4 - (n3 - 1) / 100 + (n3 - 1) / 400;
		t = n1 + mesi[n2 - 1];

		if (n2 > 2 && n3 % 4 == 0 && (n3 % 100 != 0 || n3 % 400 == 0)) {
			t += 1;
		}
	}
	else
	{
		x = n3 + (n3 - 1) / 4;
		t = n1 + mesi[n2 - 1];
		t -= 2;
		if (n2 > 2 && n3 % 4 == 0 && (n3 % 100 != 0 || n3 % 400 == 0)) {
			t += 1;
		}
	}

	x += t;
	x %= 7;
	if (bisestiles(aa) == false)
	{
		switch (x) {
		case 0:
			return "Sabato";
		case 1:
			return "Domenica";
		case 2:
			return "Lunedi";
		case 3:
			return "Martedi";
		case 4:
			return "Mercoledi";
		case 5:
			return "Giovedi";
		case 6:
			return "Venerdi";
		}
	}
	else
	{
		switch (x) {
		case 0:
			return "Venerdi";
		case 1:
			return "Sabato";
		case 2:
			return "Domenica";
		case 3:
			return "Lunedi";
		case 4:
			return "Martedi";
		case 5:
			return "Mercoledi";
		case 6:
			return "Giovedi";
		}
	}
	return "";
}
bool Sessione::bisestiles(int aa)
{
	if (aa % 400 == 0 || (aa % 4 == 0 && aa % 100 != 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Sessione::definesesgiorni()
{
	int mesenb[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int meseb[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int i=0,j,k;
	int anno = this->annostart;
	int mese = this->mesestart;
	int giorno = this->giornostart;
	int z=0;
	if (bisestiles(anno) == true)
	{
			for (j = mese; j <= this->meseend; j++)
			{
				if (j == this->meseend)
				{
					for (k = giorno; k <= this->giornoend; k++)
					{
						Giorno g;
						g.define(this->annostart, j, k, calcolagiorno(k, j, this->annostart));
						this->addgiorno(g);
						z++;
					}
					giorno = 1;
					mese++;
				}
				else
				{
					for (k = giorno; k <= meseb[j - 1]; k++)
					{
						Giorno g;
						g.define(this->annostart, j, k, calcolagiorno(k, j, this->annostart));
						this->addgiorno(g);
					}
					giorno = 1;
					mese++;
				}
			}
	}
	else
	{
			for (j = mese; j < this->meseend; j++)
			{
				if (j == this->meseend)
				{
					for (k = giorno; k <= this->giornoend; k++)
					{
						Giorno g;
						g.define(this->annostart, j, k, calcolagiorno(k, j, this->annostart));
						this->addgiorno(g);
					}
					giorno = 1;
					mese++;

				}
				else
				{
					for (k = giorno; k <= mesenb[j - 1]; k++)
					{
						Giorno g;
						g.define(this->annostart, j, k, calcolagiorno(k, j, this->annostart));
						this->addgiorno(g);
					}
					giorno = 1;
					mese++;

				}
			}
	}

}

void Sessione::addgiorno(Giorno g)
{
	 this->sesgiorni.push_back(g);
}

std::vector<Giorno> Sessione:: getsessgiornivec()
{
	return this->sesgiorni;
}

void Sessione::initsesgiornifascie()
{
	int i;
	for (i = 0; i < this->sesgiorni.size(); i++)
	{
		this->sesgiorni[i].initfascie();
	}
	return;
}

void Sessione::initgiornistraordinario()
{
	int i;
	for (i = 0; i < this->sesgiorni.size(); i++)
	{
		this->sesgiorni[i].initstraordinario();
	}
	return;
}

std::string Sessione::getanno()
{
	std::stringstream ss;
	ss << this->annoend;
	return ss.str();
}

void Sessione::setesameaddcorsotudioid(int i, int posi,std::string corsostudioid)
{
	this->sesgiorni[i].addcorsotudioid(corsostudioid, posi);
}

void Sessione:: setesameaddcorsoid(int i, int j, std::string corsoid)
{
	this->sesgiorni[i].addcorsiid(corsoid, j);
}