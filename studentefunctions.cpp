#include "studentefunctions.h"

std::vector <Studente> getstudenti(char* filename)
{
	int i;
	int flag;
std::vector<Studente> listastudenti;
std::vector<std::string> vect;
char* res;
char buf[BUF];
std::string matricola;
Studente s;
FILE* fp,*fp1;
fp1 = fopen("db_studenti.txt", "r");
if (fp1 != NULL)
{
	listastudenti = getstudentsfromdb(fp1);
	fclose(fp1);
}
fp = fopen(filename, "r");
if (fp == NULL)
{
	printf("apertura file fallito\n");
	if (listastudenti.size() > 0)
	{
		printf("ritorno db gi¨¤ esistente\n");
		return listastudenti;
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
	matricola = s.generatematricola();
	if (listastudenti.size() > 0)
	{
		for (i = 0; i < listastudenti.size() && flag == 1; i++)
		{
			if (matricola == listastudenti[i].getmatricola())
			{
				flag = 0;
			}
		}
	}
	if (flag == 0)
	{
		while (flag == 0)
		{
			matricola = s.generatematricola();
			flag = 1;
			for (i = 0; i < listastudenti.size(); i++)
			{
				if (matricola == listastudenti[i].getmatricola())
				{
					flag = 0;
					break;
				}
			}
		}
	}
	int flag1 = 0;
	if (listastudenti.size() > 0)
	{
		for (i = 0; i < listastudenti.size(); i++)
		{
			if (vect[2] == listastudenti[i].getemail())
			{
				flag1 = 1;
				break;
			}
		}
		if (flag1 == 1)
		{
			printf("gi¨¤ presente studente : %s %s \n", vect[0].c_str(), vect[1].c_str());
		}
		else
		{
			s.define(matricola, vect[0], vect[1], vect[2]);
			listastudenti.push_back(s);
		}
	}
	else
	{
		s.define(matricola, vect[0], vect[1], vect[2]);
		listastudenti.push_back(s);
	}
	vect.clear();
}

return listastudenti;
}

void generetedbstudenti(char* filename, std::vector<Studente>listastudenti)
{
	int i;
	FILE* fp;
	char* stampa;
	fp = fopen(filename, "w");
	std::string dastampare;
	for (i = 0; i < listastudenti.size(); i++)
	{
		dastampare = listastudenti[i].getmatricola() + ";" + listastudenti[i].getname() + ";" + listastudenti[i].getsurname() + ";" + listastudenti[i].getemail();
		stampa = _strdup(dastampare.c_str());
		fprintf(fp, "%s", stampa);
		free(stampa);
	}
	fclose(fp);
}

std::vector<Studente>getstudentsfromdb(FILE* fp)
{
	int i;
	std::vector<Studente> listastudenti;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Studente s;
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

		s.define(vect[0], vect[1], vect[2], vect[3]);
		listastudenti.push_back(s);
		vect.clear();
	}

	return listastudenti;
}

std::vector<Studente> updatestudent(char* filename)
{
	int i, j,k,flag;
	std::vector<Studente> listastudent;
	FILE* fp,*fp1;
	fp1 = fopen("db_studenti.txt", "r");
	if (fp1 != NULL)
	{
		listastudent = getstudentsfromdb(fp1);
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
	if (listastudent.size() == 0)
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
		for (i = 0; i < listastudent.size(); i++)
		{
			if (vect[0] == listastudent[i].getmatricola())
			{
				for (j = 1; j < vect.size(); j++)
				{
					flag = 1;
					if (vect[j] != "")
					{
						if (j == 1)
						{
							listastudent[i].updatename(vect[j]);
							printf("studente %s: nome aggiornato->%s\n", vect[0].c_str(),vect[j].c_str());
						}
						
						if (j == 2)
						{
							listastudent[i].updatesurname(vect[j]);
							printf("studente %s: cognome aggiornato->%s\n", vect[0].c_str(),vect[j].c_str());
						}
						if (j == 3)
						{
							for (k = 0; k < listastudent.size(); k++)
							{
								if (listastudent[k].getemail() == vect[j])
								{
									flag = 0;
									break;
								}
							}
							if (flag)
							{
								listastudent[i].updteemail(vect[j]);
								printf("studente %s: email aggiornato->%s\n", vect[0].c_str(), vect[j].c_str());
							}
							else
							{
								printf("impossibile aggiornare email, uno stesso gi¨¤ presente in db\n");
							}
						}
					}
				}
			}
		}
		vect.clear();
		
	}
	fclose(fp1);
	fclose(fp);
	return listastudent;

}