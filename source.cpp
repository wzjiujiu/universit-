#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "studente.h"
#include <list>
#include <vector>
#include <sstream>
#include <string>
#define N 50
#define BUF 200


using namespace std;
list <Studente> getstudenti(char* filename);

int main(int argc, char** argv)
{
	list<Studente> listastudenti;
	char *filename;
	
	/*if (argc <= 2)
	{
		printf("pochi argomenti.. esco\n");
		exit(0);
	}*/
	//if (argc == 3)
	//{
		//if (strcmp(argv[1], "-a:s") == 0)
		//{
	filename = _strdup("db_studenti.txt");
    listastudenti = getstudenti(filename);
		//}
	//}

	
}

list <Studente> getstudenti(char* filename)
{
	int count = 0,i,matricolanum;
	list<Studente> listastudenti;
	vector<string> vect;
	char* res;
	char buf[BUF];
	char* matricola;
	Studente s;
	FILE* fp;
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
		matricola = _strdup(vect[0].c_str());
		matricolanum = atoi(matricola + 1);
		if (matricolanum % 2 != 0)
		{
			free(matricola);
			printf("trovato matricola con numero dispari, nome studente : %s, per favore ricontrolla il file", vect[1].c_str());
			exit(0);
		}
		s.define(vect[0], vect[1], vect[2], vect[3]);
		listastudenti.push_back(s);
		vect.clear();
	}

	return listastudenti;
}
