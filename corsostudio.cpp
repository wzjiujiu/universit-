#include "corsostudio.h"

void Corsostudio::generaldefine(std::string idcorsostudio, std::string tipo)
{
	this->idcorsostudio = idcorsostudio;
	this->tipo = tipo;

}

semestre Corsostudio::definesemestre(std::vector<std::string> corsivet, int sem)
{
	int i;
	semestre s;
	for (i = 0; i < corsivet.size(); i++)
	{
		s.idcorsivet.push_back(corsivet[i]);
	}
	s.sem = sem;
	return s;
}

std::string Corsostudio::generateidcorsostudio()
{
	int num1 = rand() % 10;
	int num2 = rand() % 10;
	int num3 = rand() % 10;

	std::stringstream ss, ss1, ss2;
	ss << num1;
	std::string numero1 = ss.str();
	ss1 << num2;
	std::string numero2 = ss1.str();
	ss2 << num3;
	std::string numero3 = ss2.str();


	std::string cstudioid = "C" + numero1 + numero2 + numero3;
	return cstudioid;
}

std::string Corsostudio::getid()
{
	return this->idcorsostudio;
}
std::string Corsostudio::gettipo()
{
	return this->tipo;
}

void Corsostudio::addcorsispenti(std::string id)
{
	this->corsispenti.push_back(id);

}

void Corsostudio::addcorsistudio(semestre s)
{
	this->corsistudio.push_back(s);
}

void Corsostudio::printsemestri(std::ofstream *fout)
{
	std::string dastampa;
	std::string stampa;
	int i;
	if (this->corsistudio.size() == 0)
	{
		return;
	}
	for (i = 0; i < corsistudio.size(); i++)
	{
		dastampa = returnstring(corsistudio[i])+',';
		stampa = stampa + dastampa;
	}
	char* cancelvirgola = _strdup(stampa.c_str());
	cancelvirgola[stampa.size() - 1] = '\0';
	std::string string1(cancelvirgola);
	free(cancelvirgola);
	*fout << string1;
	return;

}
void Corsostudio::printcorsispenti(std::ofstream* fout)
{
	std::string dastampa;
	std::string stampa;
	int i;
	if (this->corsispenti.size() == 0)
	{
		return;
	}
	for (i = 0; i < corsispenti.size(); i++)
	{
		dastampa = corsispenti[i] + ',';
		stampa = stampa + dastampa;
	}
	char* cancelvirgola = _strdup(stampa.c_str());
	cancelvirgola[stampa.size() - 1] = '\0';
	std::string string1(cancelvirgola);
	free(cancelvirgola);
	*fout << string1;
	return;
}

std::string Corsostudio::returnstring(semestre s)
{
	int i;
	std::string dastampa;
	std::string stampa;
	for (i = 0; i < s.idcorsivet.size(); i++)
	{
		dastampa = s.idcorsivet[i] + ',';
		stampa = stampa + dastampa;
	}
	char* cancelvirgola = _strdup(stampa.c_str());
	cancelvirgola[stampa.size() - 1] = '\0';
	std::string string1(cancelvirgola);
	free(cancelvirgola);
	std::string returnstring = "{" + string1 + "}";
	return returnstring;
}

std::vector<semestre> Corsostudio:: getcorsistudio()
{
	return this->corsistudio;
}

void Corsostudio::bringtospento(std::string id)
{
	int i;
	int j;
	for (i = 0; i < this->corsistudio.size(); i++)
	{
		int pos = checkpresente(this->corsistudio[i].idcorsivet, id);
		if (pos >= 0)
		{
			this->corsistudio[i].idcorsivet.erase(this->corsistudio[i].idcorsivet.begin() + pos);
			addcorsispenti(id);
		}
	}
}

int Corsostudio:: checkpresente(std::vector<std::string> idcorsivet, std::string id)
{
	int i;
	for (i = 0; i < idcorsivet.size(); i++)
	{
		if (idcorsivet[i] == id)
			return i;
	}
	return -1;
}