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
	selectionsortanni(this->corsianni, 0, this->corsianni.size()-1);

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

void Corsobig::setattivo()
{
	int i;
	if (this->corsianni.size() > 0)
	{
		for (i = 0; i < this->corsianni.size(); i++)
		{
			this->corsianni[i].attivare();
		}
		printf("corso %s ии attivo\n", this->idcorso.c_str());
		return;
	}
	printf("errore\n");
	return;
}
void Corsobig::setnonattivo()
{
	int i;
	if (this->corsianni.size() > 0)
	{
		for (i = 0; i < this->corsianni.size(); i++)
		{
			this->corsianni[i].spengnere();
		}
		printf("corso %s ии spento\n", this->idcorso.c_str());
		return;
	}
	printf("errore\n");
	return;
}

int Corsobig::checkattivo()
{
	int i;
	if (this->corsianni.size() > 0)
	{
	
		if (this->corsianni[this->corsianni.size()-1].controlloattivo())
			return 1;
		else 
			return 0;
	}
	
	return 0;
}

void Corsobig::selectionsortanni(std::vector<Corso> smallcorsi, int l, int r)
{
	int i, j, min;
	Corso tmp;
	for (i = l; i < r; i++)
	{
		min = i;
		for (j = i + 1; j <= r; j++)
		{
			if (smallcorsi[j].getannoaccademico()<smallcorsi[i].getannoaccademico())
				min = j;
		}
		tmp = smallcorsi[i];
		smallcorsi[i] = smallcorsi[min];
		smallcorsi[min] = tmp;
	}
	this->corsianni = smallcorsi;
	return;
}

int Corsobig::definesessione(int sessione)
{
	if (this->sessione == -1)
	{
		this->sessione = sessione;
		return 1;
	}
	else
		return -2;
}

int Corsobig::getses()
{
	return this->sessione;
}

int Corsobig::getexamtime(std::string annoaccademico)
{
	int i;
	for (i = 0; i < this->corsianni.size(); i++)
	{
		if (this->corsianni[i].getannoaccademico() == annoaccademico)
		{
			return this->corsianni[i].getesametime();
		}
	}
	return -1;
}

void Corsobig::impostaesame()
{
	this->esameimpostato = 1;

}

int Corsobig::checkesameimpostato()
{
	if (this->esameimpostato == 1)
		return 1;
	else
		return -1;
}

int Corsobig::checkesameimpostato2()
{
	if (this->esameimpostato == 2)
	{
		return 1;
	}
	else
		return-1;
}

void Corsobig::impostaesame2()
{
	this->esameimpostato++;
}

