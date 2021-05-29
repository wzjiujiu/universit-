#include "proffunctions.h"

std::vector<Prof>getprofs(char* filename)
{
	int i, matricolanum;
	int flag;
	std::vector<Prof> listaprofessori;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Prof p;
	FILE* fp,*fp1;
	fp1 = fopen("db_professori.txt", "r");
	if (fp1 != NULL)
	{
		listaprofessori = getprofsfromdb(fp1);
		fclose(fp1);
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		if (listaprofessori.size() > 0)
		{
			printf("ritorno db gi¨¤ esistente\n");
			return listaprofessori;
		}
		exit(0);
	}
	while (1)
	{
		flag = 1;
		res = fgets(buf, BUF, fp);
		if (res == NULL)
			break;
		std::string data = res;
		std::stringstream ss(data);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ';');
			vect.push_back(substr);
		}
		matricola = p.generatematricola();
		if (listaprofessori.size() > 0)
		{
			for (i = 0; i < listaprofessori.size()&&flag==1; i++)
			{
				if (matricola == listaprofessori[i].getmatricola())
				{
					flag = 0;
				}
			}
		}
		if (flag == 0)
		{
			while (flag == 0)
			{
				matricola = p.generatematricola();
				flag = 1;
				for (i = 0; i < listaprofessori.size(); i++)
				{
					if (matricola == listaprofessori[i].getmatricola())
					{
						flag = 0;
						break;
					}
				}
			}
		}
		int flag1 = 0;

		if (listaprofessori.size() > 0)
		{
			for (i = 0; i < listaprofessori.size(); i++)
			{
				if (vect[2] == listaprofessori[i].getemail())
				{
					flag1 = 1;
					break;
				}
			}
			if (flag1 == 1)
			{
				printf("gi¨¤ presente prof : %s %s \n", vect[0].c_str(), vect[1].c_str());
			}
			else
			{
				p.define(matricola, vect[0], vect[1], vect[2]);
				listaprofessori.push_back(p);
			}
		}
		else
		{
			p.define(matricola, vect[0], vect[1], vect[2]);
			listaprofessori.push_back(p);
		}
		
		vect.clear();
	}

	return listaprofessori;
}

void generetedbprofessori(char* filename, std::vector<Prof>listaprofessori)
{
	int i;
	FILE* fp;
	char* stampa;
	fp = fopen(filename, "w");
	std::string dastampare;
	for (i = 0; i < listaprofessori.size(); i++)
	{
		dastampare = listaprofessori[i].getmatricola() + ";" + listaprofessori[i].getname() + ";" + listaprofessori[i].getsurname() + ";" + listaprofessori[i].getemail();
		stampa = _strdup(dastampare.c_str());
		fprintf(fp, "%s", stampa);
		free(stampa);
	}
	fclose(fp);
}

std::vector<Prof>getprofsfromdb( FILE* fp)
{
	int i;
	std::vector<Prof> listaprofessori;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Prof p;
	while (1)
	{
		res = fgets(buf, BUF, fp);
		if (res == NULL)
			break;
		std::string data = res;
		std::stringstream ss(data);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ';');
			vect.push_back(substr);
		}
		
		p.define(vect[0], vect[1], vect[2], vect[3]);
		listaprofessori.push_back(p);
		vect.clear();
	}

	return listaprofessori;
}

std::vector<Prof> updateprof(char* filename)
{
	int i, j;
	std::vector<Prof> listprofs;
	FILE* fp, * fp1;
	fp1 = fopen("db_professori.txt", "r");
	if (fp1 != NULL)
	{
		listprofs = getprofsfromdb(fp1);
	}
	else
	{
		printf("database non presente, impossibile aggiornare\n");
		exit(0);
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("impossibile aprire il file di aggionamento, esco\n");
		exit(0);
	}
	if (listprofs.size() == 0)
	{
		printf("database non presente, impossibile aggiornare\n");
		exit(0);
	}
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	while (1)
	{
		res = fgets(buf, BUF, fp);
		if (res == NULL)
			break;
		std::string data = res;
		std::stringstream ss(data);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ';');
			vect.push_back(substr);
		}
		for (i = 0; i < listprofs.size(); i++)
		{
			if (vect[0] == listprofs[i].getmatricola())
			{
				for (j = 1; j < vect.size(); j++)
				{
					if (vect[j] != "")
					{
						if (j == 1)
						{
							listprofs[i].updatename(vect[j]);
							printf("prof %s: nome aggiornato->%s\n", vect[0].c_str(),vect[j].c_str());
						}

						if (j == 2)
						{
							listprofs[i].updatesurname(vect[j]);
							printf("prof %s: cognome aggiornato->%s\n", vect[0].c_str(),vect[j].c_str());
						}
						if (j == 3)
						{
							listprofs[i].updateemail(vect[j]);
							printf("prof %s: email aggiornato->%s\n", vect[0].c_str(),vect[j].c_str());
						}
					}
				}
			}
		}
		vect.clear();

	}
	return listprofs;

}