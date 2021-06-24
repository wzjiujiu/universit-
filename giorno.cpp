#include "giorno.h"


void Giorno::printfascie()
{

}
void Giorno::define(int anno, int mese, int giorno, std::string qualegiorno)
{
	this->anno = anno;
	this->mese = mese;
	this->giorno = giorno;
	this->qualegiorno = qualegiorno;
	return;
}

std::string Giorno::getqualegiorno()
{
	return this->qualegiorno;
}

void Giorno::initfascie()
{
	int i;
	for (i = 0; i < 6; i++)
	{
		this->fascecorsiid.push_back("Free");
		
	}
	std::vector<std::string> vector;
	for (i = 0; i < 6; i++)
	{
		this->fascecorsistudioid.push_back(vector);
	}
	return;
}

int Giorno::corsistudioidpresente(std::vector<Corsostudio> corsistudiolist)
{
	int i,j;
	for (i = 0; i < this->fascecorsistudioid.size(); i++)
	{
		for (j = 0; j < this->fascecorsistudioid[i].size(); j++)
		{
			if (presentecorsostudioid(corsistudiolist, this->fascecorsistudioid[i][j]) == 1)
			{
				return -1;
			}
		}
	}
	return 1;
}
int Giorno::presentecorsostudioid(std::vector<Corsostudio> corsistudiolist, std::string id)
{

	int i,j;
	for (i = 0; i < this->fascecorsistudioid.size(); i++)
	{
		for (j = 0; j < this->fascecorsistudioid[i].size(); j++)
		{
			if (id == this->fascecorsistudioid[i][j])
				return 1;
		}
	}
	return -1;
}

int Giorno::getanno()
{
	return this->anno;
}
int Giorno::getmese()
{
	return this->mese;
}
int Giorno::getgiorno()
{
	return this->giorno;
}

std::vector<std::string> Giorno::getfascecorsiid()
{
	return this->fascecorsiid;
}

void Giorno::addcorsiid(std::string id,int pos)
{
	this->fascecorsiid[pos]=id;
}
void Giorno::addcorsotudioid(std::string id,int pos)
{
	this->fascecorsistudioid[pos].push_back(id);
}

int Giorno::getposiid(std::string id)
{
	int i;
	for (i = 0; i < this->fascecorsiid.size(); i++)
	{
		if (this->fascecorsiid[i] == id)
		{
			return i;
		}
	}
	return -1;
}

void Giorno::initstraordinario()
{
	int i;
	for (i = 0; i < 6; i++)
	{
		this->straordinario.push_back(0);

	}
	std::vector<std::string> vector;
	for (i = 0; i < 6; i++)
	{
		this->fascecorsistudioid.push_back(vector);
	}
	return;
}

void Giorno::printgiorno(std::ofstream* fout)
{
	int i;
	for (i = 0; i < this->straordinario.size(); i++)
	{
		if (this->straordinario[i] == 0)
		{
			if (i == 0)
			{
				(*fout) << getfasciaoraria(i) + ";";
				if (this->fascecorsiid[i] != "Free")
				{
					(*fout) << this->fascecorsiid[i] + getcorsostudioidcorr(i);

				}
				else
				{
					(*fout) << "Free";
				}
				(*fout) << ";\n";
			}
			else
			{
				(*fout) << getfasciaoraria(i) + ";";
				if (this->fascecorsiid[i] != "Free")
				{
					if (this->fascecorsiid[i] != this->fascecorsiid[i - 1])
					{
						(*fout) << this->fascecorsiid[i] + getcorsostudioidcorr(i);
					}

				}
				else
				{
					(*fout) << "Free";
				}
				(*fout) << ";\n";
			}
		}
	}

}

std::string Giorno::getcorsostudioidcorr(int pos)
{
	std::string dareturn = "(";
	int i;
	for (i = 0; i < this->fascecorsistudioid[pos].size(); i++)
	{
		dareturn = dareturn + this->fascecorsistudioid[pos][i];
	}
	dareturn = dareturn + ")";
	return dareturn;
}

std::string Giorno::getfasciaoraria(int i)
{
	switch (i)
	{
	case 0:
		return "08:00-10:00";
	case 1:
		return "10:00-12:00";
	case 2:
		return "12:00-14:00";
	case 3:
		return "14:00-16:00";
	case 4:
		return "16:00-18:00";
	case 5:
		return "18:00-20:00";
	}
}

std::string Giorno::getgiornodata()
{
	std::stringstream ss1, ss2, ss3;
	ss1 << this->giorno;
	ss2 << this->mese;
	ss3 << this->anno;
	return (ss1.str() + "-" + ss2.str() + "-" + ss3.str());
}