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


using namespace std;
void getcorsi(char* filename,vector<Corsobig> *corsiout);
void procede(Corso small, std::string info,int parallel,std::string corsoid);
void procedeinto(char** map, int j, int start, int end, std::string info);
int numprofcollab(char* string);
std::string getmatricolatit(char* string);
char* getcollabprofinfo(char* string, int j,int *end);
vector<string> getcorsoidvec(std::string corsoid);
vector<Corsostudio> getcorsostudiolist(char* filename,vector<Corsobig> *corsiout);


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
	filename = _strdup("db_corsi.txt");
	getcorsi(filename,&listcorsi);
	free(filename);
	filename = _strdup("db_corsi_studio.txt");
	listcorsistudio = getcorsostudiolist(filename,&listcorsi);
	
	
		//}
	//}

	
}




void getcorsi(char* filename, vector<Corsobig>* corsiout)
{
	vector<Corsobig> corsi;
	Corsobig c;
	Corsobig x;
	Corso small,small1;
	vector<string> vect,vect1;
	char* res;
	char buf[BUF];
	FILE* fp;
	char* prev=_strdup("c");
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
		if (vect[0] == "c")
		{
			
			if (strcmp(prev,"c")==0)
			{
				c.definegeneralinfo(vect[0], vect[1], vect[2], stoi(vect[3]), stoi(vect[4]), stoi(vect[5]), stoi(vect[6]));
			}
			else if (strcmp(prev,"a")==0)
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
			int i;
			int attivo;
			int parallel = stoi(vect[3]);
			char* active = _strdup(vect[2].c_str());
			if (strcmp(active, "attivo") == 0)
				attivo = 1;
			else
				attivo = 0;
			small = small1;
			small.generaldefine(vect[0], vect[1], attivo, stoi(vect[3]));
			procede(small, vect[4], parallel,vect[6]);
			c.addcorso(small);

		}

	
		vect.clear();
	}
	corsi.push_back(c);
	*corsiout = corsi;

}

void procede(Corso small, std::string info, int parallel,std::string corsoid)
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
			small.addprof(small.createprof(matricolatit, vect[0], stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), vect1[i]));
			vect.clear();
		}

	}

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
	int start = 1;
	int end;
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
