#include "aulafunctions.h"

std::vector<Aula>getaule(char* filename)
{
	int i, flag;
	std::vector<Aula> listaule;
	Aula a;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	FILE* fp, * fp1;
	std::string aulaid;
	fp1 = fopen("db_aule.txt", "r");
	if (fp1 != NULL)
	{
		listaule = getaulefromdb(fp1);
		fclose(fp1);
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		if (listaule.size() > 0)
		{
			printf("ritorno db gi¨¤ esistente\n");
			return listaule;
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
		aulaid = a.generateidaula();
		if (listaule.size() > 0)
		{
			for (i = 0; i < listaule.size() && flag == 1; i++)
			{
				if (aulaid == listaule[i].getaulaid())
				{
					flag = 0;
				}
			}
		}
		if (flag == 0)
		{
			while (flag == 0)
			{
				aulaid = a.generateidaula();
				flag = 1;
				for (i = 0; i < listaule.size(); i++)
				{
					if (aulaid == listaule[i].getaulaid())
					{
						flag = 0;
						break;
					}
				}
			}
		}
		int flag1 = 0;
		if (listaule.size() > 0)
		{
			for (i = 0; i < listaule.size(); i++)
			{
				if (vect[1] == listaule[i].getdenominazione())
				{
					flag1 = 1;
					break;
				}
			}
			if (flag1 == 1)
			{
				printf("gi¨¤ presente aula : %s \n", vect[1].c_str());
			}
			else
			{
				a.define(aulaid, vect[0], vect[1], atoi(vect[2].c_str()), atoi(vect[3].c_str()));
				listaule.push_back(a);
			}
		}
		else
		{
			a.define(aulaid, vect[0], vect[1], atoi(vect[2].c_str()), atoi(vect[3].c_str()));
			listaule.push_back(a);
		}


		vect.clear();
	}
	return listaule;
}

std::vector<Aula>getaulefromdb(FILE* fp)
{
	int i;
	std::vector<Aula> listaule;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Aula a;
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

		a.define(vect[0], vect[1], vect[2], atoi(vect[3].c_str()), atoi(vect[4].c_str()));
		listaule.push_back(a);
		vect.clear();
	}

	return listaule;
}

void generetedbaule(char* filename, std::vector<Aula>listaule)
{
	int i;
	FILE* fp;
	char* stampa;
	fp = fopen(filename, "w");
	std::string dastampare;
	int num1, num2;
	std::stringstream ss, ss1;
	for (i = 0; i < listaule.size(); i++)
	{
		num1 = listaule[i].getcapienzamax();
		num2 = listaule[i].getcapenzaexam();
		ss << num1;
		ss1 << num2;

		dastampare = listaule[i].generateidaula() + ";" + listaule[i].getaulatipo() + ";" + listaule[i].getdenominazione() + ";" + ss.str()+";" + ss1.str();
		stampa = _strdup(dastampare.c_str());
		fprintf(fp, "%s\n", stampa);
		free(stampa);
	}
	fclose(fp);
}