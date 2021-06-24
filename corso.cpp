#include "corso.h"


collabprof Corso::createprof(std::string matricolatit, std::string matricola, int lezione, int es, int lab, std::string idcorso,int set,int j)
{
	collabprof p;
	p.es = es;
	p.idcorso = idcorso;
	p.lab = lab;
	p.matricola = matricola;
	p.lezione = lezione;
	p.matricolatit = matricolatit;
	p.set = set;
	p.num = j;
	return p;
	
}

void Corso::addprof(collabprof p)
{
	this->collabprofs.push_back(p);

}

void Corso::generaldefine( std::string id,std::string annoaccademico,std::string nome, int cfu,int lez,int es,int lab, int verspar, int durataesame, int t_entro, int t_esco, std::string modalita, std::string luogo)
{
	
	this->annoaccademico = annoaccademico;
	this->verspar = verspar;
	this->id = id;
	this->nome = nome;
	this->lez = lez;
	this->es = es;
	this->lab = lab;
	this->durataesame = durataesame;
	this->t_entro = t_entro;
	this->t_esco = t_esco;
	this->modalita = modalita;
	this->luogo = luogo;
	this->cfu = cfu;
	this->attivo = "attivo";
}

std::string Corso::generateid()
{
	int num1 = rand() % 10;
	int num2 = rand() % 10;
	int num3 = rand() % 10;
	char alpha = 'A' + rand() % 26;
	char alpha1 = 'A' + rand() % 26;
	char alpha2 = 'A' + rand() % 26;
	std::stringstream ss, ss1,ss2;
	ss << num1;
	std::string numero1 = ss.str();
	ss1 << num2;
	std::string numero2 = ss1.str();
	ss2 << num3;
	std::string numero3 = ss2.str();
	std::string let1(1, alpha);
	std::string let2(1, alpha1);
	std::string let3(1, alpha2);

	std::string corsoid =  let1 + let2 + numero2+numero1+numero3;
	return corsoid;
}

std::string Corso::getidentifier()
{
	return this->identifier;
}
std::string Corso:: getnome()
{
	return this->nome;
}
std::string Corso::getannoaccademico()
{
	return this->annoaccademico;
}
int Corso::getdurataesame()
{
	return this->durataesame;
}

std::string Corso::getid()
{
	return this->id;
}

int Corso::getcfu()
{
	return this->cfu;
}
int Corso::getlez()
{
	return this->lez;
}
int Corso::getes()
{
	return this->es;
}
int Corso::getlab()
{
	return this->lab;
}

void Corso::printprofs(int verspar,FILE *fp)
{
	std::string dastampa;
	std::string stampa;
	std::string id;
	int i;
	if (this->collabprofs.size() == 0)
	{
		return;
	}
	for (i = 0; i < verspar; i++)
	{
		id = getidtit(i);
		dastampa = getcollabprof(i)+"},";
		stampa = stampa + dastampa;
		
	}
	char* cancelvirgola = _strdup(stampa.c_str());
	cancelvirgola[stampa.size() - 1] = '\0';
	std::string returnstring(cancelvirgola);
	free(cancelvirgola);
	fprintf(fp,"%s", returnstring.c_str());
}

std::string Corso::getcollabprof(int set)
{
	std::string stampa = "[";
	std::string singleprof;
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (this->collabprofs[i].set == set)
		{
			singleprof = getsingleprof(this->collabprofs[i]);
			stampa = stampa + singleprof+",";
		}
	}
	char* cancelvirgola = _strdup(stampa.c_str());
	cancelvirgola[stampa.size() - 1] = '\0';
	std::string returnstring(cancelvirgola);
	free(cancelvirgola);
	returnstring = returnstring + "]";
	return returnstring;
}

std::string Corso::getsingleprof(collabprof p)
{
	std::stringstream ss, ss1, ss2;
	int num1, num2, num3;
	num1 = p.lezione;
	num2 = p.es;
	num3 = p.lab;
	ss << num1;
	ss1 << num2;
	ss2 << num3;
	std::string lez=ss.str();
	std::string es=ss1.str();
	std::string lab=ss2.str();
	std::string stamp = "{" + p.matricola + "," + lez + "," + es + "," + lab + "}";
	return stamp;
}

int Corso::getverpar()
{
	return this->verspar;
}

std::string Corso::getattivo()
{
	return this->attivo;
}

void Corso::printcorsiraggrupati( FILE* fp)
{
	int i;
	std::string dastampa="{";
	if (this->corsiragruppati.size() == 0)
	{
		fprintf(fp, "{}");
	}
	else
	{
		for (i = 0; i < this->corsiragruppati.size(); i++)
		{
			dastampa = dastampa + this->corsiragruppati[i] + ",";
		}
		char* cancelvirgola = _strdup(dastampa.c_str());
		cancelvirgola[dastampa.size() - 1] = '\0';
		std::string returnstring(cancelvirgola);
		free(cancelvirgola);
		returnstring = returnstring + "}";
		fprintf(fp, "%s", returnstring.c_str());
	}
}

std::string Corso::getmod()
{
	return this->modalita;
}
std::string Corso::getluogo()
{
	return this->luogo;
}

void Corso::generaldefinedb(std::string identifier, std::string annoaccademico, std::string attivo, int verspar, int durataesame, int t_entro, int t_esco, std::string modalita, std::string luogo)
{
	this->attivo = attivo;
	this->annoaccademico = annoaccademico;
	this->identifier = identifier;
	this->verspar = verspar;
	this->durataesame = durataesame;
	this->t_entro = t_entro;
	this->t_esco = t_esco;
	this->modalita = modalita;
	this->luogo = luogo;

}

std::string Corso::getidtit(int verpar)
{
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (this->collabprofs[i].set == verpar)
		{
			return this->collabprofs[i].matricolatit;
		}
	}
	return "";
}

int Corso::getentro()
{
	return this->t_entro;
}
int Corso::getesco()
{
	return this->t_esco;
}

void Corso::attivare()
{
	this->attivo = "attivo";
}
void Corso::spengnere()
{
	this->attivo = "non_attivo";
}

int Corso::controlloattivo()
{
	if (this->attivo == "attivo")
		return 1;
	else
		return 0;
}

int Corso::getnumprofinoneset(int set)
{
	int count = 0;
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (set == this->collabprofs[i].set)
			count++;
	}
	return count;
}

std::string Corso::getmatricolaprofcollab(int set, int num)
{
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (this->collabprofs[i].set == set)
		{
			if (this->collabprofs[i].num == num)
			{
				return this->collabprofs[i].matricola;
			}
		}
	}
	return "";
}

int Corso::getlezprofcollab(int set, int num)
{
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (this->collabprofs[i].set == set)
		{
			if (this->collabprofs[i].num == num)
			{
				return this->collabprofs[i].lezione;
			}
		}
	}
	return -1;
}
int Corso::getesprofcollab(int set, int num)
{
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (this->collabprofs[i].set == set)
		{
			if (this->collabprofs[i].num == num)
			{
				return this->collabprofs[i].es;
			}
		}
	}
	return -1;
}
int Corso::getlabprofcollab(int set, int num)
{
	int i;
	for (i = 0; i < this->collabprofs.size(); i++)
	{
		if (this->collabprofs[i].set == set)
		{
			if (this->collabprofs[i].num == num)
			{
				return this->collabprofs[i].lab;
			}
		}
	}
	return -1;
}

void Corso::addcorsirag(std::string corsoid)
{
	this->corsiragruppati.push_back(corsoid);
	return;
}

void Corso::defineluogo(std::string luogo)
{
	this->luogo = luogo;
}
void Corso::definemod(std::string mod)
{
	this->modalita = mod;
}
void Corso::definedurata(int durataesame)
{
	this->durataesame=durataesame;
}
void Corso::definet_entro(int t_entro)
{
	this->t_entro = t_entro;
}
void Corso::definet_esco(int t_esco)
{
	this->t_esco = t_esco;
}

void Corso::defineattivo(std::string attivo)
{
	this->attivo = attivo;
}

std::vector<collabprof> Corso::getcollabprofvec()
{
	return this->collabprofs;
}

int Corso::getesametime()
{
	return this->t_entro + this->t_esco + this->durataesame;
}