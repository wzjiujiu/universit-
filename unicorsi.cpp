#include "uni.h"

void Uni::getcorsi(char* filename, std::vector<Corsobig>* corsiout)
{
	std::vector<Prof> profs;
	std::vector<Corsobig> corsi;
	Corsobig c;
	Corsobig x;
	Corso small, small1;
	std::vector<Corso> corsosmall;
	std::vector<std::string> vect, vect1;
	char* res;
	char buf[BUF];
	FILE* fp, * fp2;
	std::ifstream fp1("db_corsi.txt");
	int flag = 0;
	std::vector<std::string> esamiinfo;
	int i;
	std::string line;
	std::ifstream infile(filename);
	fp2 = fopen("db_professori.txt", "r");
	if (fp2 == NULL)
	{
		printf("database professori non presenti, impossibile definire i corsi\n");
		exit(0);
	}
	else
	{
		profs = getprofsfromdb(_strdup("db_professori.txt"));
		if (profs.size() == 0)
		{
			printf("database professori non presenti, impossibile definire i corsi\n");
			exit(0);
		}
	}
	if (filework(fp1)==1)
	{
		getcorsifromdb("db_corsi.txt", &corsi);
		printf("caricato dal db\n");
		fp1.close();
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		exit(0);
	}
	while (std::getline(infile, line))
	{
		std::string data = line;
		std::stringstream ss(data);
		while (ss.good())
		{
			std::string substr;
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
			small = procede(small, vect[7], stoi(vect[6]), id, profs);
			int ok = controlloraggrupamenti(vect[8], profs);
			if (ok == 1)
			{
				small = elaboracorsirag(small, vect[8]);
			}
			corsosmall.push_back(small);
		}

		vect.clear();
	}
	selectionsort(corsosmall, 0, corsosmall.size() - 1);

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
			c.definegeneralinfo("c", corsosmall[i + 1].getid(), corsosmall[i + 1].getnome(), corsosmall[i + 1].getcfu(), corsosmall[i + 1].getlez(), corsosmall[i + 1].getlab(), corsosmall[i + 1].getes());
		}

	}
	if (flag)
	{
		corsi.push_back(c);
	}
	*corsiout = corsi;

}

Corso Uni::procede(Corso small, std::string info, int parallel, std::string corsoid, std::vector<Prof> profs)
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

	char** map = new char* [parallel];
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

	std::vector<std::string> vect, vect1;
	vect1 = getcorsoidvec(corsoid);

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
				std::string substr;
				getline(ss, substr, ' ');
				if (substr != "")
				{
					vect.push_back(substr);
				}
			}
			if (profinlist(profs, matricolatit) && profinlist(profs, vect[0]))
			{
				small.addprof(small.createprof(matricolatit, vect[0], stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), vect1[0], i, j));

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

void Uni::procedeinto(char** map, int j, int start, int end, std::string info)
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

int Uni::numprofcollab(char* string)
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

std::string Uni::getmatricolatit(char* string)
{

	int i;
	char maticolat[N];
	sscanf(string, "%*s %s", maticolat);
	std::string matricolatit(maticolat);

	return matricolatit;
}

std::string Uni::getmatricolatit1(char* string)
{
	int i;
	char maticolat[N];
	sscanf(string, "%*s %*s %s", maticolat);
	std::string matricolatit(maticolat);

	return matricolatit;
}

char* Uni::getcollabprofinfo(char* string, int j, int* end)
{
	int z = 0;
	char* collabproinfo;
	int i;
	int start = 0;
	int endi = 0;
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
	for (i = start + 1; i < endi; i++)
	{
		collabproinfo[z++] = string[i];
	}
	*end = endi + 1;
	return collabproinfo;
}

std::vector<std::string> Uni::getcorsoidvec(std::string corsoid)
{
	int z = 0;
	std::vector<std::string> vect;
	char* corsoidinfo = _strdup(corsoid.c_str());
	int i;
	int start = 0; //1
	int end = corsoid.size();
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
		std::string substr;
		getline(ss, substr, ',');
		vect.push_back(substr);
	}
	return vect;
}

std::vector<std::string> Uni::getesamiinfo(std::string esameinfo)
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
		std::string substr;
		getline(ss, substr, ',');
		vect.push_back(substr);
	}
	return vect;

}

void Uni::selectionsort(std::vector<Corso> smallcorsi, int l, int r)
{
	int i, j, min;
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

void Uni::generatedbcorsi(char* filename, std::vector<Corsobig> listcorsi)
{
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		exit(0);
	}
	int i, j;
	for (i = 0; i < listcorsi.size(); i++)
	{
		fprintf(fp, "%s;%s;%s;%d;%d;%d;%d;\n", listcorsi[i].getidentifier().c_str(), listcorsi[i].getidcorso().c_str(), listcorsi[i].gettitolo().c_str(), listcorsi[i].getcfu(), listcorsi[i].getorelezione(), listcorsi[i].getorees(), listcorsi[i].getorelab());

		for (j = 0; j < listcorsi[i].getcorsismall().size(); j++)
		{
			fprintf(fp, "%s;%s;%s;%d;", listcorsi[i].getcorsismall()[j].getidentifier().c_str(), listcorsi[i].getcorsismall()[j].getannoaccademico().c_str(), listcorsi[i].getcorsismall()[j].getattivo().c_str(), listcorsi[i].getcorsismall()[j].getverpar());
			fprintf(fp, "[");
			listcorsi[i].getcorsismall()[j].printprofs(listcorsi[i].getcorsismall()[j].getverpar(), fp);
			fprintf(fp, "];");
			fprintf(fp, "{%d,%d,%d,%s,%s};", listcorsi[i].getcorsismall()[j].getdurataesame(), listcorsi[i].getcorsismall()[j].getentro(), listcorsi[i].getcorsismall()[j].getesco(), listcorsi[i].getcorsismall()[j].getmod().c_str(), listcorsi[i].getcorsismall()[j].getluogo().c_str());
			listcorsi[i].getcorsismall()[j].printcorsiraggrupati(fp);
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void Uni::getcorsifromdb(std::string filename, std::vector<Corsobig>* corsiout)
{
	std::vector<Corsobig> corsi;
	Corsobig c;
	Corsobig x;
	Corso small, small1;
	std::vector<std::string> vect, vect1;
	char* prev = _strdup("c");
	std::string corsoid;
	std::string line;
	std::ifstream infile(filename);

	while (std::getline(infile,line))
	{
		std::string data = line;
		std::stringstream ss(data);
		while (ss.good())
		{
			std::string substr;
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
			std::vector<std::string> esamiinfo;
			esamiinfo = getesamiinfo(vect[5]);
			int i;
			int attivo;
			int parallel = stoi(vect[3]);
			small = small1;
			small.generaldefinedb(vect[0], vect[1], vect[2], stoi(vect[3]), stoi(esamiinfo[0]), stoi(esamiinfo[1]), stoi(esamiinfo[2]), esamiinfo[3], esamiinfo[4]);
			small = procede1(small, vect[4], parallel, corsoid);
			small = elaboracorsirag(small, vect[6]);
			c.addcorso(small);
			prev = _strdup(vect[0].c_str());
		}


		vect.clear();
	}
	corsi.push_back(c);
	*corsiout = corsi;

}

int Uni::idnopresente(std::string id, std::vector<Corsobig> corsiout)
{
	if (corsiout.size() == 0)
		return 1;
	int i, flag = 0;

	for (i = 0; i < corsiout.size() && flag == 0; i++)
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

Corso Uni::procede1(Corso small, std::string info, int parallel, std::string corsoid)
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

	std::vector<std::string> vect;



	for (i = 0; i < parallel; i++)
	{
		int end = 1;
		numcollabprof = numprofcollab(map[i]);
		matricolatit = getmatricolatit1(map[i]);
		for (j = 0; j < numcollabprof; j++)
		{
			char* collabproinfos = getcollabprofinfo(map[i], j, &end);
			std::string collabinfo(collabproinfos);
			std::stringstream ss(collabinfo);
			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ' ');
				if (substr != "")
				{
					vect.push_back(substr);
				}
			}
			small.addprof(small.createprof(matricolatit, vect[0], stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), corsoid, i, j));
			vect.clear();
		}

	}

	return small;
}

void Uni::inseriscicorso(char* filename, std::vector<Corsobig>* corsiout, int* flag)
{
	std::vector<Corsobig> corsi;
	FILE* fp, * fp1, * fp2;
	std::vector<Corsostudio> corsistudi;
	std::vector<Prof> profs;
	fp = fopen("db_corsi.txt", "r");
	if (fp != NULL)
	{
		getcorsifromdb("db_corsi.txt", &corsi);
		if (corsi.size() == 0)
		{
			std::cout << "db corsi non presente, impossibile fare inserzione\n";
			exit(0);
		}
	}
	else
	{
		std::cout << "db corsi non presente, impossibile fare inserzione\n";
		exit(0);
	}
	fp2 = fopen("db_professori.txt", "r");
	if (fp2 != NULL)
	{
		profs = getprofsfromdb(_strdup("db_professori.txt"));
		if (profs.size() == 0)
		{
			std::cout << "db prof non presente, impossibile fare inserzione\n";
			exit(0);
		}
	}
	else
	{
		std::cout << "db prof non presente, impossibile fare inserzione\n";
		exit(0);
	}
	fp1 = fopen("db_corsi_studio.txt", "r");
	if (fp1 != NULL)
	{
		corsistudi = getcorsostudiolistfromdb(_strdup("db_corsi_studio.txt"), &corsi);
	}

	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> vect;
	int pos, posc;
	int riga = 1;
	while (std::getline(infile, line))
	{
		std::string data = line;
		std::stringstream ss(data);
		int ok;
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ';');
			vect.push_back(substr);
		}
		Corso small;
		if (idnopresente(vect[0], corsi) == 0)
		{
			pos = annopresente(vect[1], corsi, vect[0]);
			posc = getcorsopos(vect[0], corsi);
			if (pos == -1)
			{
				if (caricabile(vect[2], (vect[3]), vect[4], vect[5], vect[6], pos, posc, corsi, profs, &small, riga, vect[0])==1)
				{
					std::vector<std::string> esamiinfo;
					esamiinfo = getesamiinfo(vect[5]);
					int parallel = stoi(vect[3]);
					small.generaldefinedb("a", vect[1], vect[2], stoi(vect[3]), stoi(esamiinfo[0]), stoi(esamiinfo[1]), stoi(esamiinfo[2]), esamiinfo[3], esamiinfo[4]);
					small = procede1(small, vect[4], parallel, vect[0]);
					small = elaboracorsirag(small, vect[6]);
					corsi[posc].addcorso(small);

				}
				else
				{
					std::cout << "errore sintassi riga:: " + std::to_string(riga) + "\n";
					*flag = 0;
				}
			}
			else if (pos == -2)
			{
				std::cout << "gi¨¤ presente il corso per quest'anno riga:: " + std::to_string(riga) + "\n";
				*flag = 0;
			}
			else
			{
				ok = ereditabile(vect[2], stoi(vect[3]), vect[4], vect[5], vect[6], pos, posc, corsi, profs, &small, riga, vect[0]);
				switch (ok)
				{
				case 1:
				{

					corsi[posc].addcorso(small);
					break;
				}
				case -2:
				{
					std::cout << "errore sintassi negli esamiinfo riga " + std::to_string(riga) + "\n";
					*flag = 0;
					break;
				}
				case -3:
				{
					std::cout << "errore sintassi nei raggrupamenti riga " + std::to_string(riga) + "\n";
					*flag = 0;
					break;
				}
				case -4:
				{
					std::cout << "errore sintassi in collabprof riga " + std::to_string(riga) + "\n";
					*flag = 0;
					break;
				}
				case -5:
				{
					std::cout << "errore sintassi in attivo riga " + std::to_string(riga) + "\n";
					*flag = 0;
					break;
				}

				}


			}
			if ((*flag) == 1)
			{
				char* in = _strdup("db_corsi_studio.txt");
				corsistudi = modificacorsostudioafterinsert(small.getattivo(), vect[0], corsistudi);
				generatedbcorsistudio(in, corsistudi);
			}

		}
		else
		{
			std::cout << "id non presente riga " + std::to_string(riga) + "\n";
			*flag = 0;
		}
		vect.clear();
		riga++;
	}
	*corsiout = corsi;
	return;

}

std::vector<Corsostudio> Uni:: modificacorsostudioafterinsert(std::string attivo, std::string id, std::vector<Corsostudio> corsistudi)
{
	int i;
	int j;
	if (attivo == "non_attivo")
	{
		for (i = 0; i < corsistudi.size(); i++)
		{
			corsistudi[i].bringtospento(id);
		}
	}
	return corsistudi;
}
Corso Uni::elaboracorsirag(Corso small, std::string info)
{
	int i;
	int count = 0;
	char* cinfo = (char*)calloc(info.size() + 1, sizeof(char));
	
	for (i = 1; i < info.size() - 1; i++)
	{
		cinfo[count++] = info[i];
	}
	std::string infos(cinfo);
	free(cinfo);
	if (infos == "" || infos == " ")
	{
		return small;
	}
	std::vector<std::string> vect;
	std::string raggrupamento(infos);

	std::stringstream ss(raggrupamento);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		if (substr != "" && substr != " ")
		{
			vect.push_back(substr);
		}
	}
	for (i = 0; i < vect.size(); i++)
	{
		small.addcorsirag(vect[i]);
	}
	return small;
}

int Uni::caricabile(std::string attivo, std::string parallelo, std::string collabproinfo, std::string esamiinfo, std::string raggrupamento, int pos, int posc, std::vector<Corsobig> corsi, std::vector<Prof> profs, Corso* small, int riga, std::string corsoid)
{
	int flag1, flag2,flag3,flag4;
	if (attivo != "attivo" && attivo != "non_attivo")
	{
		return -1;
	}
	if (parallelo.size() != 1)
		return -1;
	if (is_number(parallelo))
	{
		if (stoi(parallelo) <= 0)
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	flag1 = controlloparallel(stoi(parallelo), collabproinfo);
	if (flag1 == -1)
	{
		return -1;
	}
	flag2 = controllocollabprof(collabproinfo, stoi(parallelo), profs);
	if (flag2 == -1)
	{
		return -1;
	}
	flag3 = controlloesami(esamiinfo);
	if (flag3 == -1)
	{
		return -1;
	}
	flag4 = controlloraggrupamenti(raggrupamento, profs);
	if (flag4 == -1)
	{
		return -1;
	}
	return 1;

}
int Uni::controlloraggrupamenti(std::string raggrupamentiinfo, std::vector<Prof> profs)
{
	char* cinfo = (char*)calloc(raggrupamentiinfo.size(), sizeof(char));
	int z = 0;
	int count = 0;
	int i;
	for (i = 0; i < raggrupamentiinfo.size(); i++)
	{
		if (raggrupamentiinfo[i] == '{' || raggrupamentiinfo[i] == '}')
			count++;
	}
	if (count != 2)
	{
		return -1;
	}
	count = 0;
	for (i = 0; i < raggrupamentiinfo.size(); i++)
	{
		if (raggrupamentiinfo[i] == ',')
			count++;
	}
	if (count == 0)
	{
		
		for (i = 1; i < raggrupamentiinfo.size() - 1; i++)
		{
			cinfo[z++] = raggrupamentiinfo[i];
		}
		std::string id(cinfo);
		free(cinfo);
		if (id == ""||id == " ")
		{
			return 1;
		}
		if (profinlist(profs, id) == true)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
		for (i = 1; i < raggrupamentiinfo.size() - 1; i++)
		{
			cinfo[z++] = raggrupamentiinfo[i];
		}
		std::string id(cinfo);
		free(cinfo);
		std::vector<std::string> vect;
		std::stringstream ss(id);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');
			if (substr != "")
				vect.push_back(substr);
		}
		for (i = 0; i < vect.size(); i++)
		{
			if (profinlist(profs, vect[i]) != true)
			{
				return -1;
			}
		}
		return 1;
	}

}

int Uni::controlloesami(std::string esaminfo)
{
	char* cinfo = (char*)calloc(esaminfo.size(), sizeof(char));
	int count = 0;
	int i;
	for (i = 0; i < esaminfo.size(); i++)
	{
		if (esaminfo[i] == '{' || esaminfo[i] == '}')
			count++;
	}
	if (count != 2)
	{
		return -1;
	}
	count = 0;
	for (i = 0; i < esaminfo.size(); i++)
	{
		if (esaminfo[i] == ',')
			count++;
	}
	if (count != 4)
		return -1;
	count = 0;
	
	for (i = 1; i < esaminfo.size() - 1; i++)
	{
		cinfo[count++] = esaminfo[i];
	}
	std::string elab(cinfo);
	std::vector<std::string> vect;
	std::stringstream ss(elab);
	free(cinfo);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		if (substr != "")
		{
			if (substr != " " && substr != "")
			{
				vect.push_back(substr);
			}
		}
	}
	if (vect.size() != 5)
	{
		return -1;
	}
	for (i = 0; i < vect.size(); i++)
	{
		if (i == 0)
		{
			if (is_number(vect[0]) == true)
			{
				if (stoi(vect[0]) < 0)
					return -1;
			}
			else
				return -1;
		}
		else if (i == 1)
		{
			if (is_number(vect[1]) == true)
			{
				if (stoi(vect[1]) < 0)
					return -1;
			}
			else
				return -1;
		}
		else if (i == 2)
		{
			if (is_number(vect[2]) == true)
			{
				if (stoi(vect[2]) < 0)
					return -1;
			}
			else
				return -1;
		}
		else if (i == 3)
		{
			if (vect[3] != "SO" && vect[3] != "S" && vect[3] != "O")
			{
				return -1;
			}
		}
		else if (i == 4)
		{
			if (vect[4] != "A" && vect[4] != "L")
			{
				return -1;
			}
		}
		else
			return -1;
	}
	return 1;

}

int Uni::controllocollabprof(std::string info, int parallel, std::vector<Prof> profs)
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

	char** map = new char* [parallel];
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
	std::vector<std::string> vect;
	int ok = 1;
	for (i = 0; i < parallel; i++)
	{
		int end = 1;
		numcollabprof = numprofcollab(map[i]);
		matricolatit = getmatricolatit1(map[i]);
		if (matricolatit == "{" || matricolatit == "[")
		{
			return -1;
		}
		else
		{
			if (profinlist(profs, matricolatit) == false)
			{
				return -1;
			}
		}
		for (j = 0; j < numcollabprof; j++)
		{
			char* collabproinfos = getcollabprofinfo(map[i], j, &end);
			std::string collabinfo(collabproinfos);
			std::stringstream ss(collabinfo);
			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ' ');
				if (substr != "")
				{
					if (substr != " " && substr != "")
					{
						vect.push_back(substr);
					}
				}
			}
			if (vect.size() != 4)
			{
				return -1;
			}
			if (profinlist(profs, vect[0]) == false)
			{
				return -1;
			}
			if (is_number(vect[1]) == false || is_number(vect[2]) == false || is_number(vect[3]) == false)
			{
				return -1;
			}
			if (stoi(vect[1]) < 0 || stoi(vect[2]) < 0 || stoi(vect[3]) < 0)
			{
				return -1;
			}
			
			vect.clear();
		}

	}
	return 1;
}

bool Uni::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int Uni::controlloparallel(int parallel, std::string collabprofinfo)
{
	int count = 0;
	int i;
	for (i = 1; i < collabprofinfo.size() - 1; i++)
	{
		if (collabprofinfo[i] == ']')
			count++;
	}
	if (count == parallel)
	{
		return 1;
	}
	else
		return -1;
}

int Uni::ereditabile(std::string attivo, int parallelo, std::string collabproinfo, std::string esamiinfo, std::string raggrupamento, int pos, int posc, std::vector<Corsobig> corsi, std::vector<Prof> profs, Corso* small, int riga, std::string corsoid)
{
	bool flag, flag1, flag2;
	int vuoto = 0;
	if (parallelo != corsi[posc].getcorsismall()[pos].getverpar())
		return -1;
	flag = checkprofcollab(collabproinfo, parallelo, pos, posc, corsi, profs, small, corsoid);
	if (flag == true)
	{
		flag1 = checkraggruppamenti(raggrupamento, corsi, &vuoto, small);
		if (flag1 == true)
		{
			if (vuoto == 1)
			{
				std::cout << "raggrupamenti vuoto";
			}
			flag2 = ereditaesami(small, esamiinfo, pos, posc, corsi);
			if (flag2 == true)
			{
				if (attivo == "" || attivo == " ")
				{
					small->defineattivo(corsi[posc].getcorsismall()[pos].getattivo());
					return 1;
				}
				else
				{
					if (attivo != "attivo" && attivo != "non_attivo")
					{
						return -5;
					}
				}
				return 1;
			}
			else
			{
				return -2;
			}

		}
		else
		{
			return -3;
		}
	}
	else
	{
		return -4;
	}

}

bool Uni::ereditaesami(Corso* small, std::string esamiinfo, int pos, int posc, std::vector<Corsobig> corsi)
{
	char* info = (char*)calloc(esamiinfo.size(), sizeof(char));
	int count = 0;
	int i;
	for (i = 0; i < esamiinfo.size(); i++)
	{
		if (esamiinfo[i] == '{' || esamiinfo[i] == '}')
			count++;
	}
	if (count != 2)
	{
		return false;
	}
	count = 0;
	for (i = 0; i < esamiinfo.size(); i++)
	{
		if (esamiinfo[i] == ',')
			count++;
	}
	if (count != 4)
	{
		return false;
	}
	std::vector<std::string> vect;
	std::string esami(info);
	free(info);
	std::stringstream ss(esami);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		vect.push_back(substr);
	}
	for (i = 0; i < vect.size(); i++)
	{
		if (i == 0)
		{
			if (vect[i] == "" || vect[i] == " ")
			{
				vect[i] = std::to_string(corsi[posc].getcorsismall()[pos].getdurataesame());
			}
			else
			{
				if (stoi(vect[i]) < 0)
				{
					return false;
				}
			}
		}
		else if (i == 1)
		{
			if (vect[i] == "" || vect[i] == " ")
			{
				vect[i] = std::to_string(corsi[posc].getcorsismall()[pos].getentro());
			}
			else
			{
				if (stoi(vect[i]) < 0)
				{
					return false;
				}
			}
		}
		else if (i == 2)
		{
			if (vect[i] == "" || vect[i] == " ")
			{
				vect[i] = std::to_string(corsi[posc].getcorsismall()[pos].getesco());
			}
			else
			{
				if (stoi(vect[i]) < 0)
				{
					return false;
				}
			}
		}
		else if (i == 3)
		{
			if (vect[i] == "" || vect[i] == " ")
			{
				vect[i] = corsi[posc].getcorsismall()[pos].getmod();
			}
			else
			{
				if (vect[i] != "SO" && vect[i] != "S" && vect[i] != "O")
				{
					return false;
				}
			}
		}
		else if (i == 4)
		{
			if (vect[i] == "" || vect[i] == " ")
			{
				vect[i] = corsi[posc].getcorsismall()[pos].getluogo();
			}
			else
			{
				if (vect[i] != "A" && vect[i] != "L")
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}

	}
	small->definedurata(stoi(vect[0]));
	small->definet_entro(stoi(vect[1]));
	small->definet_esco(stoi(vect[2]));
	small->definemod(vect[3]);
	small->defineluogo(vect[4]);

	return true;

}

bool Uni::checkraggruppamenti(std::string raggrupamenti, std::vector<Corsobig> corsi, int* vuoto, Corso* small)
{
	char* info = (char*)calloc(raggrupamenti.size(), sizeof(char));

	int count = 0;
	int i;
	for (i = 0; i < raggrupamenti.size(); i++)
	{
		if (raggrupamenti[i] == '{' || raggrupamenti[i] == '}')
		{
			count++;
		}
	}
	if (count != 2)
	{
		return false;
	}
	count = 0;
	for (i = 0; i < raggrupamenti.size(); i++)
	{
		if (raggrupamenti[i] == ',')
		{
			count++;
		}
	}
	if (count == 0)
	{
		*vuoto = 1;
		return true;
	}

	count = 0;
	for (i = 1; i < raggrupamenti.size() - 1; i++)
	{
		info[count++] = raggrupamenti[i];
	}
	std::vector<std::string> vect;
	std::string raggrupamento(info);
	free(info);
	std::stringstream ss(raggrupamento);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		if (substr != "" && substr != " ")
		{
			vect.push_back(substr);
		}
	}
	std::vector<int> okvet;
	for (i = 0; i < vect.size(); i++)
	{
		okvet.push_back(idnopresente(vect[i], corsi));
	}
	for (i = 0; i < okvet.size(); i++)
	{
		if (okvet[i] == 1)
		{
			return false;
		}
	}
	for (i = 0; i < vect.size(); i++)
	{
		small->addcorsirag(vect[i]);
	}
	return true;

}

int Uni::annopresente(std::string anno, std::vector<Corsobig> corsi, std::string id)
{
	int i, j;
	for (i = 0; i < corsi.size(); i++)
	{
		if (corsi[i].getidcorso() == id)
		{
			for (j = 0; j < corsi[i].getcorsismall().size(); j++)
			{
				if (corsi[i].getcorsismall()[j].getannoaccademico() == anno)
					return -2;
			}

		}
	}
	std::vector<std::string> anni;
	for (i = 0; i < corsi.size(); i++)
	{
		if (corsi[i].getidcorso() == id)
		{
			for (j = 0; j < corsi[i].getcorsismall().size(); j++)
			{
				anni.push_back(corsi[i].getcorsismall()[j].getannoaccademico());
			}
		}
	}
	for (i = 0; i < anni.size(); i++)
	{
		if (anno > anni[i])
			return i;
	}
	return -1;
}

int Uni::getcorsopos(std::string id, std::vector<Corsobig> corsi)
{
	int i;
	for (i = 0; i < corsi.size(); i++)
	{
		if (id == corsi[i].getidcorso())
			return i;
	}
	return -1;
}

bool Uni::checkprofcollab(std::string info, int parallel, int pos, int posc, std::vector<Corsobig> corsi, std::vector<Prof> profs, Corso* small, std::string corsoid)
{
	int i, j = 0;
	int numcollabprof = 0;
	std::string matricolatit;
	for (i = 0; i < info.size(); i++)
	{

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

	char** map = new char* [parallel];
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
	std::vector<std::string> vect;
	int ok = 1;
	for (i = 0; i < parallel; i++)
	{
		int end = 1;
		numcollabprof = numprofcollab(map[i]);
		matricolatit = getmatricolatit(map[i]);
		if (matricolatit == ",[")
			matricolatit = "";
		for (j = 0; j < numcollabprof; j++)
		{
			char* collabproinfos = getcollabprofinfo(map[i], j, &end);
			std::string collabinfo(collabproinfos);
			std::stringstream ss(collabinfo);
			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ',');
				vect.push_back(substr);

			}
			setokvet(&ok, &matricolatit, &vect, numcollabprof, pos, posc, corsi, i, profs, j);
			if (ok)
			{
				small->addprof(small->createprof(matricolatit, vect[0], stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), corsoid, i, j));
			}
			else
			{
				return false;
			}
			ok = 1;
			vect.clear();
		}

	}
	return true;
}

void Uni::setokvet(int* ok, std::string* matricolatit, std::vector<std::string>* vect, int numcollabprof, int pos, int posc, std::vector<Corsobig> corsi, int set, std::vector<Prof> profs, int j)
{
	int num;
	char* intstr;
	bool flag;
	int i;
	if (numcollabprof != corsi[posc].getcorsismall()[pos].getnumprofinoneset(set))
	{
		*ok = 0;
		return;
	}
	if (*matricolatit == "" || *matricolatit == " ")
	{
		*matricolatit = corsi[posc].getcorsismall()[pos].getidtit(set);
	}
	else
	{
		flag = profinlist(profs, *matricolatit);
		if (flag == false)
		{
			*ok = 0;
			return;
		}
	}
	for (i = 0; i < (*vect).size(); i++)
	{
		if (i == 0)
		{
			if ((*vect)[i] == "" || (*vect)[i] == " ")
			{
				(*vect)[i] = corsi[posc].getcorsismall()[pos].getmatricolaprofcollab(set, j);
				if ((*vect)[i] == "")
				{
					*ok = 0;
					return;
				}
			}
			else
			{
				flag = profinlist(profs, (*vect)[i]);
				if (flag == false)
				{
					*ok = 0;
					return;
				}
			}
		}
		else if (i == 1)
		{
			if ((*vect)[i] == "" || (*vect)[i] == " ")
			{
				(*vect)[i] = std::to_string(corsi[pos].getcorsismall()[posc].getlezprofcollab(set, j));

			}
		}
		else if (i == 2)
		{
			if ((*vect)[i] == "" || (*vect)[i] == " ")
			{
				(*vect)[i] = std::to_string(corsi[posc].getcorsismall()[pos].getesprofcollab(set, j));

			}
		}
		else if (i == 3)
		{
			if ((*vect)[i] == "" || (*vect)[i] == " ")
			{
				(*vect)[i] = std::to_string(corsi[posc].getcorsismall()[pos].getlabprofcollab(set, j));

			}


		}
		else
		{
			*ok = 0;
			return;
		}


	}
	return;
}
