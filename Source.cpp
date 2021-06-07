#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "studente.h"
#include <list>
#include <vector>
#include <sstream>
#include <string>
#define N 500
#define BUF 500
#include "prof.h"
#include "aula.h"
#include <fstream>
#include "corsobig.h"
#include "corsostudio.h"
#include "studentefunctions.h"
#include "proffunctions.h"
#include "aulafunctions.h"
#include "esamefunctions.h"



using namespace std;
void getcorsi(char* filename,vector<Corsobig> *corsiout);
Corso procede(Corso small, std::string info,int parallel,std::string corsoid,vector<Prof> profs);
void procedeinto(char** map, int j, int start, int end, std::string info);
int numprofcollab(char* string);
std::string getmatricolatit(char* string);
char* getcollabprofinfo(char* string, int j,int *end);
vector<string> getcorsoidvec(std::string corsoid);
vector<Corsostudio> getcorsostudiolist(char* filename,vector<Corsobig> *corsiout);
vector<std::string> getesamiinfo(std::string esameinfo);
void selectionsort(vector<Corso> smallcorsi, int l, int r);
void generatedbcorsi(char* filename, vector<Corsobig> listcorsi);
void getcorsifromdb(FILE *fp, vector<Corsobig>* corsiout);
int idnopresente(std::string id, vector<Corsobig> corsiout);
Corso procede1(Corso small, std::string info, int parallel, std::string corsoid);



int main(int argc, char** argv)
{
	vector<Studente> listastudenti;
	char *filename;
	vector<Prof> listprofessori;
	vector<Aula> listaule;
	vector<Corsobig> listcorsi;
	vector<Corsostudio> listcorsistudio;
	
	/*if (argc <= 2)
	{
		printf("pochi argomenti.. esco\n");
		exit(0);
	}*/
	//if (argc == 3)
	//{
		//if (strcmp(argv[1], "-a:s") == 0)
		//{
	//set studenti
	filename = _strdup("studenti.txt");
    listastudenti = getstudenti(filename);
	generetedbstudenti(_strdup("db_studenti.txt"), listastudenti);
	listastudenti = updatestudent(_strdup("update_studenti.txt"));
	generetedbstudenti(_strdup("db_studenti.txt"), listastudenti);
	free(filename);
	//set prof
	filename = _strdup("professori.txt");
	listprofessori = getprofs(filename);
	generetedbprofessori(_strdup("db_professori.txt"), listprofessori);
	listprofessori = updateprof(_strdup("update_profs.txt"));
	generetedbprofessori(_strdup("db_professori.txt"), listprofessori);
	free(filename);
	//set aule
	filename = _strdup("aule.txt");
	listaule = getaule(filename);
	generetedbaule(_strdup("db_aule.txt"), listaule);
	free(filename);
	filename = _strdup("corsi.txt");
	getcorsi(filename,&listcorsi);
	generatedbcorsi(_strdup("db_corsi.txt"), listcorsi);
	free(filename);

	generateannoesamidata(_strdup("2019-2020"), _strdup("2020-1-12|2020-2-29"), _strdup("2020-6-6|2020-7-30"), _strdup("2020-9-1|2020-9-30"));
	generatefileindisponibilita(_strdup("indisponibile.txt"), _strdup("2019-2020"));
	
	
	
		//}
	//}

	
}




void getcorsi(char* filename, vector<Corsobig>* corsiout)
{
	vector<Prof> profs;
	vector<Corsobig> corsi;
	Corsobig c;
	Corsobig x;
	Corso small,small1;
	vector<Corso> corsosmall;
	vector<string> vect,vect1;
	char* res;
	char buf[BUF];
	FILE* fp,*fp1,*fp2;
	int flag = 0;
	vector<std::string> esamiinfo;
	int i;
	fp2 = fopen("db_professori.txt", "r");
	if (fp2 == NULL)
	{
		printf("database professori non presenti, impossibile definire i corsi\n");
		exit(0);
	}
	else
	{
		profs = getprofsfromdb(fp2);
		if (profs.size() == 0)
		{
			printf("database professori non presenti, impossibile definire i corsi\n");
			exit(0);
		}
	}

	fp1 = fopen("db_corsi.txt", "r");
	if (fp1 != NULL)
	{
		getcorsifromdb(fp1, &corsi);
		printf("caricato dal db\n");
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		exit(0);
	}
	while (1)
	{
		res = fgets(buf, BUF, fp);
		if (res == NULL)
			break;
		string data = res;
		std::stringstream ss(data);
		while (ss.good())
		{
			string substr;
			getline(ss, substr, ';');
			vect.push_back(substr);
		}

		std::string id;
			int i;

		
			small = small1;
			id = small.generateid();
			if (idnopresente(id, corsi))
			{
				esamiinfo = getesamiinfo(vect[8]);
				small.generaldefine(id, vect[0], vect[1], stoi(vect[2]), stoi(vect[3]), stoi(vect[4]), stoi(vect[5]), stoi(vect[6]), stoi(esamiinfo[0]), stoi(esamiinfo[1]), stoi(esamiinfo[2]), esamiinfo[3], esamiinfo[4]);
				small = procede(small, vect[7], stoi(vect[6]), id,profs);
				corsosmall.push_back(small);
			}
	
		vect.clear();
	}
	selectionsort(corsosmall, 0, corsosmall.size()-1);
	
	for (i = 0; i < corsosmall.size(); i++)
	{
		flag = 1;
		if (i == 0)
		{
			c.definegeneralinfo("c", corsosmall[i].getid(), corsosmall[i].getnome(), corsosmall[i].getcfu(), corsosmall[i].getlez(), corsosmall[i].getlab(), corsosmall[i].getes());
		}
		c.addcorso(corsosmall[i]);
		if (i + 1 < corsosmall.size() && (corsosmall[i].getid() != corsosmall[i + 1].getid()))
		{
			corsi.push_back(c);
			c = x;
			c.definegeneralinfo("c", corsosmall[i+1].getid(), corsosmall[i+1].getnome(), corsosmall[i+1].getcfu(), corsosmall[i+1].getlez(), corsosmall[i+1].getlab(), corsosmall[i+1].getes());
		}

	}
	if (flag)
	{
		corsi.push_back(c);
	}
	*corsiout = corsi;

}

Corso procede(Corso small, std::string info, int parallel,std::string corsoid,vector<Prof> profs)
{
	int i, j = 0;
	int numcollabprof = 0;
	std::string matricolatit;
	for (i = 0; i < info.size(); i++)
	{
		if (info[i] == ',')
			info[i] = ' ';
		if (info[i] == '[')
			info.insert(i + 1, " ");
		if (info[i] == '{')
			info.insert(i + 1, " ");
		if (info[i] == '}')
		{
			info.insert(i, " ");
			i++;
		}
		if (info[i] == ']')
		{
			info.insert(i, " ");
			i++;
		}

	}

	char** map = (char**)calloc(parallel, sizeof(char*));
	int start = 2;
	int end;
	while (j < parallel)
	{
		for (i = 0; i < info.length(); i++)
		{

			if (info[i] == ']')
			{
				if (parallel == 1)
				{
					if (info[i + 4] == ']')
					{
						i = i + 4;
						end = i;
						procedeinto(map, j, start, end - 2, info);
						j++;

					}
				}
				else
				{

					if (j == parallel - 1)
					{
						if (info[i + 4] == ']')
						{

							end = i + 2;
							procedeinto(map, j, start, end, info);
							j++;
							start = i;

						}
					}
					else if ((i + 3 < info.length()) && (info[i + 3] == ' '))
					{
						i = i + 4;
						end = i - 1;
						procedeinto(map, j, start, end, info);
						j++;
						start = i;
					}
				}
			}
		}
	}
	
	vector<string> vect,vect1;
	vect1 = getcorsoidvec(corsoid);
    
	for (i = 0; i < parallel; i++)
	{
		int end = 1;
		numcollabprof = numprofcollab(map[i]);
		matricolatit = getmatricolatit(map[i]);
		for (j = 0; j < numcollabprof; j++)
		{
			char* collabproinfos = getcollabprofinfo(map[i], j,&end);
			std::string collabinfo(collabproinfos);
			std::stringstream ss(collabinfo);
			while (ss.good())
			{
				string substr;
				getline(ss, substr,' ');
				if (substr != "")
				{
					vect.push_back(substr);
				}
			}
			if (profinlist(profs, matricolatit) && profinlist(profs, vect[0]))
			{
				small.addprof(small.createprof(matricolatit, vect[0], stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), vect1[0], i));

			}
			else
			{
				printf("prof non presente in db, file non conforme\n");
				exit(0);
			}
			vect.clear();
		}

	}

	return small;
}

void procedeinto(char** map, int j, int start, int end, std::string info)
{
	char* informa = _strdup(info.c_str());
	map[j] = (char*)calloc(end - start + 1 + 1, sizeof(char));
	int i, k = 0;
	for (i = start; i <= end; i++)
	{
		map[j][k++] = informa[i];
	}
	printf("%s\n", map[j]);
	free(informa);
}

int numprofcollab(char* string)
{
	int numprof = 0;
	int i;
	for (i = 1; i < strlen(string); i++)
	{
		if (string[i] == '{')
			numprof++;
	}
	return numprof;
}

std::string getmatricolatit(char* string)
{
	
	int i;
	char maticolat[N];
	sscanf(string, "%*s %s", maticolat);
	std::string matricolatit(maticolat);

	return matricolatit;
}

char* getcollabprofinfo(char* string, int j,int *end)
{
	int z = 0;
	char* collabproinfo;
	int i;
	int start=0;
	int endi=0;
	for (i = (*end); i < strlen(string); i++)
	{
		if (string[i] == '{')
			start = i;
		else if (string[i] == '}')
		{
			endi = i;
			break;
		}
	}
	collabproinfo = (char*)calloc(endi - start + 1, sizeof(char));
	for (i = start+1; i < endi; i++) 
	{
		collabproinfo[z++] = string[i];
	}
	*end = endi+1;
	return collabproinfo;
}

vector<string> getcorsoidvec(std::string corsoid)
{
	int z = 0;
	vector<string> vect;
	char* corsoidinfo = _strdup(corsoid.c_str());
	int i;
	int start = 0; //1
	int end=corsoid.size();
	for (i = 0; i < strlen(corsoidinfo); i++)
	{
		if (corsoidinfo[i] == '}')
		{
			end = i;
			break;
		}
	}
	char* newcorsoidinfo = (char*)calloc(end - start + 1, sizeof(char));
	for (i = start; i < end; i++)
	{
		newcorsoidinfo[z++] = corsoidinfo[i];
	}
	std::string corsoidi(newcorsoidinfo);
	std::stringstream ss(corsoidi);
	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		vect.push_back(substr);
	}
	return vect;
}

vector<Corsostudio> getcorsostudiolist(char* filename, vector<Corsobig>* corsiout)
{
	vector<Corsostudio> listcorsostudio;
	FILE* fp,*fp1;
	fp = fopen(filename,"r");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		exit(0);
	}
	fp1 = fopen("db_corsi.txt", "r");
	if (fp1 == NULL)
	{
		printf("database corsi non presente! impossibile definire corsi di studio\n");
		exit(0);
	}

}

vector<std::string> getesamiinfo(std::string esameinfo)
{
	std::vector<std::string> vect;
	int z = 0;
	char* esamiinfo = _strdup(esameinfo.c_str());
	int i;
	char* info = (char*)calloc(esameinfo.size() - 1, sizeof(char));
	for (i = 1; i < esameinfo.size() - 1; i++)
		info[z++] = esamiinfo[i];
	std::string infos(info);
	std::stringstream ss(infos);
	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		vect.push_back(substr);
	}
	return vect;

}

void selectionsort(vector<Corso> smallcorsi, int l, int r)
{
	int i, j,min;
	Corso tmp;
	for (i = l; i < r; i++)
	{
		min = i;
		for (j = i + 1; j <= r; j++)
		{
			if (smallcorsi[j].getid() < smallcorsi[i].getid())
				min = j;
		}
		tmp = smallcorsi[i];
		smallcorsi[i] = smallcorsi[min];
		smallcorsi[min] = tmp;
	}
	return;
}

void generatedbcorsi(char* filename, vector<Corsobig> listcorsi)
{
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		exit(0);
	}
	int i,j;
	for (i = 0; i < listcorsi.size(); i++)
	{
		fprintf(fp, "%s;%s;%s;%d;%d;%d;%d;\n", listcorsi[i].getidentifier().c_str(), listcorsi[i].getidcorso().c_str(), listcorsi[i].gettitolo().c_str(),listcorsi[i].getcfu() ,listcorsi[i].getorelezione(), listcorsi[i].getorees(), listcorsi[i].getorelab());

		for (j = 0; j < listcorsi[i].getcorsismall().size(); j++)
		{
			fprintf(fp, "%s;%s;%s;%d;", listcorsi[i].getcorsismall()[j].getidentifier().c_str(), listcorsi[i].getcorsismall()[j].getannoaccademico().c_str(), listcorsi[i].getcorsismall()[j].getattivo().c_str(), listcorsi[i].getcorsismall()[j].getverpar());
			fprintf(fp, "[");
			listcorsi[i].getcorsismall()[j].printprofs(listcorsi[i].getcorsismall()[j].getverpar(),fp);
			fprintf(fp, "];");
			fprintf(fp, "{%d,%d,%d,%s,%s};", listcorsi[i].getcorsismall()[j].getdurataesame(), listcorsi[i].getcorsismall()[j].getentro(), listcorsi[i].getcorsismall()[j].getesco(), listcorsi[i].getcorsismall()[j].getmod().c_str(), listcorsi[i].getcorsismall()[j].getluogo().c_str());
			listcorsi[i].getcorsismall()[j].printcorsiraggrupati(fp);
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void getcorsifromdb(FILE *fp, vector<Corsobig>* corsiout)
{
	vector<Corsobig> corsi;
	Corsobig c;
	Corsobig x;
	Corso small, small1;
	vector<string> vect, vect1;
	char* res;
	char buf[BUF];
	char* prev = _strdup("c");
	std::string corsoid;

	while (1)
	{
		res = fgets(buf, BUF, fp);
		if (res == NULL)
			break;
		string data = res;
		std::stringstream ss(data);
		while (ss.good())
		{
			string substr;
			getline(ss, substr, ';');
			vect.push_back(substr);
		}
		if (vect[0] == "c")
		{

			if (strcmp(prev, "c") == 0)
			{
				c.definegeneralinfo(vect[0], vect[1], vect[2], stoi(vect[3]), stoi(vect[4]), stoi(vect[5]), stoi(vect[6]));
				corsoid = vect[1];
			}
			else if (strcmp(prev, "a") == 0)
			{
				corsi.push_back(c);
				c = x;
				c.definegeneralinfo(vect[0], vect[1], vect[2], stoi(vect[3]), stoi(vect[4]), stoi(vect[5]), stoi(vect[6]));
			}
			free(prev);
			prev = _strdup(vect[0].c_str());
		}
		else
		{
			vector<string> esamiinfo;
			esamiinfo = getesamiinfo(vect[5]);
			int i;
			int attivo;
			int parallel = stoi(vect[3]);
			small = small1;
			small.generaldefinedb(vect[0], vect[1], vect[2], stoi(vect[3]),stoi(esamiinfo[0]), stoi(esamiinfo[1]), stoi(esamiinfo[2]),esamiinfo[3], esamiinfo[4]);
			small=procede1(small, vect[4], parallel, corsoid);
			c.addcorso(small);
			prev = _strdup(vect[0].c_str());
		}


		vect.clear();
	}
	corsi.push_back(c);
	*corsiout = corsi;

}

int idnopresente(std::string id, vector<Corsobig> corsiout)
{
	if (corsiout.size()==0)
		return 1;
	int i,flag=0;
	
	for (i = 0; i < corsiout.size()&&flag==0; i++)
	{
		if (id == corsiout[i].getidcorso())
			flag = 1;
	}

	if (flag == 0)
	{
		return 1;
	}
	else
		return 0;
}

Corso procede1(Corso small, std::string info, int parallel, std::string corsoid)
{
	int i, j = 0;
	int numcollabprof = 0;
	std::string matricolatit;
	for (i = 0; i < info.size(); i++)
	{
		if (info[i] == ',')
			info[i] = ' ';
		if (info[i] == '[')
			info.insert(i + 1, " ");
		if (info[i] == '{')
			info.insert(i + 1, " ");
		if (info[i] == '}')
		{
			info.insert(i, " ");
			i++;
		}
		if (info[i] == ']')
		{
			info.insert(i, " ");
			i++;
		}

	}

	char** map = (char**)calloc(parallel, sizeof(char*));
	int start = 2;
	int end;
	while (j < parallel)
	{
		for (i = 0; i < info.length(); i++)
		{

			if (info[i] == ']')
			{
				if (parallel == 1)
				{
					if (info[i + 4] == ']')
					{
						i = i + 4;
						end = i;
						procedeinto(map, j, start, end - 2, info);
						j++;

					}
				}
				else
				{

					if (j == parallel - 1)
					{
						if (info[i + 4] == ']')
						{

							end = i + 2;
							procedeinto(map, j, start, end, info);
							j++;
							start = i;

						}
					}
					else if ((i + 3 < info.length()) && (info[i + 3] == ' '))
					{
						i = i + 4;
						end = i - 1;
						procedeinto(map, j, start, end, info);
						j++;
						start = i;
					}
				}
			}
		}
	}

	vector<string> vect;
	


	for (i = 0; i < parallel; i++)
	{
		int end = 1;
		numcollabprof = numprofcollab(map[i]);
		matricolatit = getmatricolatit(map[i]);
		for (j = 0; j < numcollabprof; j++)
		{
			char* collabproinfos = getcollabprofinfo(map[i], j, &end);
			std::string collabinfo(collabproinfos);
			std::stringstream ss(collabinfo);
			while (ss.good())
			{
				string substr;
				getline(ss, substr, ' ');
				if (substr != "")
				{
					vect.push_back(substr);
				}
			}
			small.addprof(small.createprof(matricolatit, vect[0], stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), corsoid, i));
			vect.clear();
		}

	}

	return small;
}