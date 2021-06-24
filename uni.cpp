#include "uni.h"

// prof

std::vector<Prof> Uni::getprofs(char* filename)
{
	int i, matricolanum;
	int flag;
	std::vector<Prof> listaprofessori;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Prof p;
	FILE* fp, * fp1;
	std::string line;
	std::ifstream infile(filename);
	fp1 = fopen("db_professori.txt", "r");
	if (fp1 != NULL)
	{
		listaprofessori = getprofsfromdb(_strdup("db_professori.txt"));
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
	while (std::getline(infile, line))
	{
		flag = 1;
		std::string data = line;
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
			for (i = 0; i < listaprofessori.size() && flag == 1; i++)
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

void Uni::generetedbprofessori(char* filename, std::vector<Prof>listaprofessori)
{
	int i;
	FILE* fp;
	char* stampa;
	fp = fopen(filename, "w");
	std::string dastampare;
	for (i = 0; i < listaprofessori.size(); i++)
	{
		dastampare = listaprofessori[i].getmatricola() + ";" + listaprofessori[i].getname() + ";" + listaprofessori[i].getsurname() + ";" + listaprofessori[i].getemail() + "\n";
		stampa = _strdup(dastampare.c_str());
		fprintf(fp, "%s", stampa);
		free(stampa);
	}
	fclose(fp);
}

std::vector<Prof> Uni::getprofsfromdb(char* filename)
{
	int i;
	std::vector<Prof> listaprofessori;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Prof p;
	std::ifstream infile(filename);
	std::string line;
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

		p.define(vect[0], vect[1], vect[2], vect[3]);
		listaprofessori.push_back(p);
		vect.clear();
	}

	return listaprofessori;
}

std::vector<Prof> Uni::updateprof(char* filename)
{
	int i, j, k, flag;
	std::vector<Prof> listprofs;
	FILE* fp, * fp1;
	fp1 = fopen("db_professori.txt", "r");
	if (fp1 != NULL)
	{
		listprofs = getprofsfromdb(_strdup("db_professori.txt"));
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
	std::ifstream infile(filename);
	std::string line;
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
		for (i = 0; i < listprofs.size(); i++)
		{
			if (vect[0] == listprofs[i].getmatricola())
			{
				for (j = 1; j < vect.size(); j++)
				{
					if (vect[j] != "")
					{
						flag = 1;
						if (j == 1)
						{
							listprofs[i].updatename(vect[j]);
							printf("prof %s: nome aggiornato->%s\n", vect[0].c_str(), vect[j].c_str());
						}

						if (j == 2)
						{
							listprofs[i].updatesurname(vect[j]);
							printf("prof %s: cognome aggiornato->%s\n", vect[0].c_str(), vect[j].c_str());
						}
						if (j == 3)
						{
							for (k = 0; k < listprofs.size(); k++)
							{
								if (listprofs[k].getemail() == vect[j])
								{
									flag = 0;
									break;
								}
							}
							if (flag)
							{
								listprofs[i].updateemail(vect[j]);
								printf("prof %s: email aggiornato->%s\n", vect[0].c_str(), vect[j].c_str());
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
	return listprofs;

}

bool Uni::profinlist(std::vector<Prof>listaprofessori, std::string matricola)
{
	int ok = 0;
	int i;
	for (i = 0; i < listaprofessori.size() && ok == 0; i++)
	{
		if (matricola == listaprofessori[i].getmatricola())
		{
			ok = 1;
		}
	}
	if (ok)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Uni::chargeindtime(std::string filename, std::vector<Prof>* profs)
{
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> vect;
	while (getline(infile, line))
	{
		std::string data = line;
		std::stringstream ss(data);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ' ');
			vect.push_back(substr);
		}
		elaboratetime(vect[1], vect[0], profs);
	}
	return;
}
void Uni::elaboratetime(std::string times, std::string profid, std::vector<Prof>* profs)
{
	int i;
	int pos = getprofpos(profid, *profs);
	std::vector<std::string> vect;
	std::stringstream ss(times);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, '|');
		vect.push_back(substr);
	}
	for (i = 0; i < vect.size(); i++)
	{
		addind(pos, vect[i], profs);
	}
}

void Uni::addind(int pos, std::string data, std::vector<Prof>* profs)
{
	std::vector<std::string> vect;
	std::stringstream ss(data);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, '-');
		vect.push_back(substr);
	}
	(*profs)[pos].addindtime((*profs)[pos].createind(stoi(vect[0]), stoi(vect[1]), stoi(vect[2])));
}

int Uni::getprofpos(std::string id, std::vector<Prof> profs)
{
	int i;
	for (i = 0; i < profs.size(); i++)
	{
		if (profs[i].getmatricola() == id)
			return i;
	}
	return -1;
}

//student

std::vector <Studente> Uni:: getstudenti(char* filename)
{
	int i;
	int flag;
	std::vector<Studente> listastudenti;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Studente s;
	std::ifstream fp(filename);
	std::string line;
	std::fstream infile(filename);
	std::ifstream fp1("db_studenti.txt");
	if (filework(fp1)==1)
	{
		listastudenti = getstudentsfromdb(_strdup("db_studenti.txt"));
		fp1.close();
	
	}
	
	if (filework(fp)==-1)
	{
		printf("apertura file fallito\n");
		if (listastudenti.size() > 0)
		{
			printf("ritorno db gi¨¤ esistente\n");
			return listastudenti;
		}
		exit(0);
	}
	while (std::getline(infile, line))
	{
		flag = 1;
		std::string data = line;
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
				for (i = 0; i < listastudenti.size() && flag != 0; i++)
				{
					if (matricola == listastudenti[i].getmatricola())
					{
						flag = 0;

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
				std::cout << "gi¨¤ presente studente : " + vect[0] + " " + vect[1] << "\n";
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

void Uni::generetedbstudenti(char* filename, std::vector<Studente>listastudenti)
{
	int i;
	FILE* fp;
	char* stampa;
	fp = fopen(filename, "w");
	std::string dastampare;
	for (i = 0; i < listastudenti.size(); i++)
	{
		dastampare = listastudenti[i].getmatricola() + ";" + listastudenti[i].getname() + ";" + listastudenti[i].getsurname() + ";" + listastudenti[i].getemail() + "\n";
		stampa = _strdup(dastampare.c_str());
		fprintf(fp, "%s", stampa);
		free(stampa);
	}
	fclose(fp);
}

std::vector<Studente> Uni::getstudentsfromdb(char* filename)
{
	int i;
	std::vector<Studente> listastudenti;
	std::vector<std::string> vect;
	char* res;
	char buf[BUF];
	std::string matricola;
	Studente s;
	std::fstream infile(filename);
	std::string line;
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

		s.define(vect[0], vect[1], vect[2], vect[3]);
		listastudenti.push_back(s);
		vect.clear();
	}

	return listastudenti;
}

std::vector<Studente> Uni::updatestudent(char* filename)
{
	int i, j, k, flag;
	std::vector<Studente> listastudent;
	FILE* fp, * fp1;
	std::string line;
	std::fstream infile(filename);
	fp1 = fopen("db_studenti.txt", "r");
	if (fp1 != NULL)
	{
		listastudent = getstudentsfromdb(_strdup("db_studenti.txt"));
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
							printf("studente %s: nome aggiornato->%s\n", vect[0].c_str(), vect[j].c_str());
						}

						if (j == 2)
						{
							listastudent[i].updatesurname(vect[j]);
							printf("studente %s: cognome aggiornato->%s\n", vect[0].c_str(), vect[j].c_str());
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

//aula

std::vector<Aula> Uni::getaule(char* filename)
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

std::vector<Aula> Uni::getaulefromdb(FILE* fp)
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

void Uni::generetedbaule(char* filename, std::vector<Aula>listaule)
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

		dastampare = listaule[i].generateidaula() + ";" + listaule[i].getaulatipo() + ";" + listaule[i].getdenominazione() + ";" + ss.str() + ";" + ss1.str();
		stampa = _strdup(dastampare.c_str());
		fprintf(fp, "%s\n", stampa);
		free(stampa);
	}
	fclose(fp);
}

//corsistudio

std::vector<Corsostudio> Uni::getcorsostudiolist(char* filename)
{
	std::vector<Corsostudio> listcorsostudio;
	std::vector<Corsobig> listcorsi;
	std::vector<std::string> vect;
	Corsostudio cs, cs1;
	std::string idcorsostudio;
	FILE* fp, * fp1, * fp2;
	int flag = 1;
	int i;
	fp = fopen(filename, "r");
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
	else
	{
		getcorsifromdb("db_corsi.txt", &listcorsi);
		if (listcorsi.size() == 0)
		{
			printf("database corsi non presente! impossibile definire corsi di studio\n");
			exit(0);
		}
		printf("dbcorsi caricato con successo!\n");
	}
	fp2 = fopen(_strdup("db_corsi_studio.txt"), "r");
	if (fp2 != NULL)
	{
		listcorsostudio = getcorsostudiolistfromdb("db_corsi_studio.txt", &listcorsi);
	}
	std::string line;
	std::fstream infile(filename);

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
		idcorsostudio = cs.generateidcorsostudio();
		if (corsostudioidinlist(idcorsostudio, listcorsostudio) == 0)
		{
			int ok;
			cs = cs1;
			cs.generaldefine(idcorsostudio, vect[0]);
			int sem = getsem(vect[1]);
			ok=procedec(vect[1], sem, &cs, &listcorsi, &flag);
			if (flag==1&&ok==1)
			{
				listcorsostudio.push_back(cs);

			}
			else
			{
				std::cout << "errore nel file,esco" << std::endl;
				exit(0);
			}

		}
		else
		{
			printf("corso studio di id %s gi¨¤ in db\n", idcorsostudio.c_str());

		}

		vect.clear();
	}

	return listcorsostudio;

}
int Uni::corsostudioidinlist(std::string id, std::vector<Corsostudio> corsiout)
{
	if (corsiout.size() == 0)
	{
		return 0;
	}
	int i, flag = 0;
	for (i = 0; i < corsiout.size() && flag == 0; i++)
	{
		if (corsiout[i].getid() == id)
		{
			flag = 1;
		}
	}
	if (flag)
	{
		return 1;
	}
	else
		return 0;
}

int Uni:: procedec(std::string info, int parallel, Corsostudio* c, std::vector<Corsobig> *corsi, int* flag)
{
	int i, j = 0;
	int numsem = 0;
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
	int start = 0;
	int end;
	int count = 0;
	for (i = 0; i < info.length() && count < parallel; i++)
	{
		if (info[i] == '{')
		{
			start = i;
		}
		else if (info[i] == '}')
		{
			end = i;
			procedeintoc(map, count++, start, end, info);
		}

	}
	int ok;
	for (i = 0; i < parallel; i++)
	{
		ok=setsessioni(map[i], i + 1, c, corsi, flag);
		if (ok == -1)
		{
			return -1;
		}
	}

	return 1;

}

int Uni::getsem(std::string info)
{
	int i;
	int count = 0;
	for (i = 0; i < info.size(); i++)
	{
		if (info[i] == '}')
			count++;
	}
	return count;
}

void Uni::procedeintoc(char** map, int j, int start, int end, std::string info)
{
	char* informa = _strdup(info.c_str());
	map[j] = (char*)calloc(end - start + 1 + 1, sizeof(char));
	int i, k = 0;
	for (i = start + 1; i < end; i++)
	{
		map[j][k++] = informa[i];
	}
	printf("%s\n", map[j]);
	free(informa);
}

int Uni::setsessioni(char* info, int sessione, Corsostudio* c, std::vector<Corsobig> *corsi, int* flag)
{
	int i, j;
	int ok = 0;
	std::vector<std::string> vect;
	std::string data(info);
	std::stringstream ss(data);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ' ');
		if (substr != "")
		{
			vect.push_back(substr);
		}
	}
	std::vector<int> okvet;
	for (i = 0; i < vect.size(); i++)
	{
		for (j = 0; j < (*corsi).size() && ok == 0; j++)
		{
			if (vect[i] == (*corsi)[j].getidcorso())
			{
				ok = 1;
				okvet.push_back(1);
			}
		}
		if (ok == 1)
		{
			ok = 0;
		}
		else
		{
			okvet.push_back(0);
		}
	}
	for (i = 0; i < okvet.size(); i++)
	{
		if (okvet[i] == 0)
		{
			(*flag) = 0;
		}
	}
	if ((*flag) == 0)
	{
		return -1;
	}
	std::vector<std::string> dadd;
	for (i = 0; i < vect.size(); i++)
	{
		if (checkattivo(vect[i], corsi))
		{
			int oki = corsisetsessioni(corsi, sessione, vect[i]);
			if (oki == 1)
			{
				dadd.push_back(vect[i]);
			}
			else
			{
				return -1;
			}
		}
		else
		{
			c->addcorsispenti(vect[i]);
		}
	}
	if (dadd.size() >= 0)
	{
		c->addcorsistudio(c->definesemestre(dadd, sessione));
	}


	return 1;

}

int Uni::checkattivo(std::string idcorso, std::vector<Corsobig> *corsi)
{
	int i;
	for (i = 0; i < (*corsi).size(); i++)
	{
		if ((*corsi)[i].getidcorso() == idcorso)
		{
			if ((*corsi)[i].checkattivo())
				return 1;
		}
	}
	return 0;
}

int Uni::corsisetsessioni(std::vector<Corsobig> *corsi, int sessione, std::string corsoid)
{
	int pos = getcorsopos(corsoid, *corsi);
	if (pos == -1)
	{
		return -1;
	}
	if ((*corsi)[pos].definesessione(sessione) == 1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

std::vector<Corsostudio> Uni::getcorsostudiolistfromdb(std::string filename, std::vector<Corsobig> *corsiout)
{
	std::vector<Corsostudio> listcorsostudio;
	std::vector<std::string> vect;
	Corsostudio cs, cs1;
	std::string line;
	std::fstream infile(filename);
	int flag = 1;
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
		cs = cs1;
		cs.generaldefine(vect[0], vect[1]);
		int sem = getsem(vect[2]);
		procedec(vect[2], sem, &cs, corsiout, &flag);
		listcorsostudio.push_back(cs);

		vect.clear();
	}
	return listcorsostudio;
}
void Uni::setcorsispenti(std::string info, Corsostudio* c)
{
	int i;
	int z = 0;
	char* data = (char*)calloc(info.size(), sizeof(char));
	for (i = 1; i < info.size() - 1; i++)
	{
		data[z++] = info[i];
	}
	std::vector<std::string> vect;
	std::string realdata(data);
	std::stringstream ss(realdata);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ' ');
		if (substr != "")
		{
			vect.push_back(substr);
		}
	}
	for (i = 0; i < vect.size(); i++)
	{
		c->addcorsispenti(vect[i]);
	}
	return;
}

void Uni::generatedbcorsistudio(char* filename, std::vector<Corsostudio>listcorsistudio)
{
	std::ofstream fout(filename);
	int i, j;
	for (i = 0; i < listcorsistudio.size(); i++)
	{
		fout << listcorsistudio[i].getid() + ";";
		fout << listcorsistudio[i].gettipo() + ";";
		fout << "[";
		listcorsistudio[i].printsemestri(&fout);
		fout << "];";
		fout << "[";
		listcorsistudio[i].printcorsispenti(&fout);
		fout << "]" << std::endl;
	}
	return;

}

//esami

void Uni::generateannoesamidata(char* annoaccademico, char* data1, char* data2, char* data3)
{
	FILE* fp;
	std::string filename;
	std::string acca(annoaccademico);
	filename = acca + "_esami.txt";
	int ok;
	std::vector<std::string> d1, d2, d3, anno;
	std::string dat1(data1);
	std::string dat2(data2);
	std::string dat3(data3);
	std::string annoacc(annoaccademico);
	std::stringstream s1(dat1);
	while (s1.good())
	{
		std::string substr;
		getline(s1, substr, '|');
		d1.push_back(substr);
	}
	std::stringstream s2(dat2);
	while (s2.good())
	{
		std::string substr;
		getline(s2, substr, '|');
		d2.push_back(substr);
	}
	std::stringstream s3(dat3);
	while (s3.good())
	{
		std::string substr;
		getline(s3, substr, '|');
		d3.push_back(substr);
	}
	std::stringstream s4(annoaccademico);
	while (s4.good())
	{
		std::string substr;
		getline(s4, substr, '-');
		anno.push_back(substr);
	}

	ok = datainto(d1, d2, d3, anno, filename);
	if (ok)
	{
		printf("salvato file dati esami con successo\n");
	}
	else
	{
		printf("salvato file con insuccesso, date non vanno bene\n");
	}
	return;

}

int Uni::datainto(std::vector<std::string>d1, std::vector<std::string> d2, std::vector<std::string> d3, std::vector<std::string> anno, std::string filename)
{
	FILE* fp;
	int ok1 = 0, ok2 = 0, ok3 = 0;
	std::vector<std::string> d1i, d1f;
	std::vector<std::string> d2i, d2f;
	std::vector<std::string> d3i, d3f;
	int dif1, dif2, dif3;
	d1i = getdata(d1, 0);
	d1f = getdata(d1, 1);
	d2i = getdata(d2, 0);
	d2f = getdata(d2, 1);
	d3i = getdata(d3, 0);
	d3f = getdata(d3, 1);
	if (d1i[0] != anno[1] || d1f[0] != anno[1] || d2i[0] != anno[1] || d2f[0] != anno[1] || d3i[0] != anno[1] || d3f[0] != anno[1])
	{
		printf("data non va bene, tutti gli esami devono stare nell'anno %s\n", anno[1].c_str());
		return 0;
	}
	dif1 = getdif(d1i, d1f);
	if (dif1 >= 42)
		ok1 = 1;
	dif2 = getdif(d2i, d2f);
	if (dif2 >= 42)
		ok2 = 1;
	dif3 = getdif(d3i, d3f);
	if (dif3 >= 28)
		ok3 = 1;
	if (ok1 == 1 && ok2 == 1 && ok3 == 1)
	{
		fp = fopen(filename.c_str(), "w");
		fprintf(fp, "%d %d %d %d %d %d\n", stoi(d1i[0]), stoi(d1i[1]), stoi(d1i[2]), stoi(d1f[0]), stoi(d1f[1]), stoi(d1f[2]));
		fprintf(fp, "%d %d %d %d %d %d\n", stoi(d2i[0]), stoi(d2i[1]), stoi(d2i[2]), stoi(d2f[0]), stoi(d2f[1]), stoi(d2f[2]));
		fprintf(fp, "%d %d %d %d %d %d\n", stoi(d3i[0]), stoi(d3i[1]), stoi(d3i[2]), stoi(d3f[0]), stoi(d3f[1]), stoi(d3f[2]));
		fclose(fp);
		return 1;

	}
	else
	{
		printf("range tempi non rispettati\n");
		return 0;
	}
}
std::vector<std::string> Uni::getdata(std::vector<std::string> d, int pos)
{
	std::vector<std::string> data;
	std::stringstream ss(d[pos]);
	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, '-');
		data.push_back(substr);
	}
	return data;
}

int Uni::getdif(std::vector<std::string>d1, std::vector<std::string> d2)
{
	bool ok1;
	bool ok2;
	ok1 = datavalida(stoi(d1[2]), stoi(d1[1]), stoi(d1[0]));
	ok2 = datavalida(stoi(d2[2]), stoi(d2[1]), stoi(d2[0]));
	if (ok1 & ok2)
	{
		return assoluto(calcolagiorni(stoi(d1[2]), stoi(d1[1]), stoi(d1[0])) - calcolagiorni(stoi(d2[2]), stoi(d2[1]), stoi(d2[0])));
	}
	else
		return 0;

}

int Uni::giornimese(int aa, int mm)
{
	switch (mm)
	{
	case 2:
		if (bisestile(aa) == true)
		{
			return 29;
		}
		else
		{
			return 28;
		}
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default: return 31;
	}
}

bool Uni::datavalida(int gg, int mm, int aa)
{
	if (aa >= 1900 && aa < 2050 && mm>0 && mm < 13 && gg>0 && gg <= giornimese(aa, mm))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Uni::calcolagiorni(int gg, int mm, int aa)//calcola i giorni dal 01011900 fino al ggmmaa
{
	int value = 0;
	for (int i = 1900; i <= aa - 1; i++)// somma i giorni fino al 3112 dell'anno precedente
	{
		if (bisestile(i))
			value += 366;
		else
			value += 365;
	}
	for (int i = 1; i <= mm - 1; i++) //somma i giorni fino all'ultimo giorno del mese precedente
	{
		value += giornimese(aa, i);
	}
	value += gg;// somma i giorni del mese corrente 
	return value;
}
bool Uni::bisestile(int aa)
{/* bisestile: se l'anno ¨¨ divisibile x 400 oppure divisibile x 4 ma non x 100
*/
	if (aa % 400 == 0 || (aa % 4 == 0 && aa % 100 != 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Uni::assoluto(int gg)
{
	if (gg < 0)
		return -gg;
	else
		return gg;
}

void Uni::generatefileindisponibilita(char* filename, char* annoaccademico)
{
	int i, ok1;
	bool ok;
	std::vector<std::string> vect, anni;
	char* res;
	char buf[BUF];
	std::vector<Prof> listaprofs;
	std::string annoacca(annoaccademico);
	std::string name = annoacca + "_indisponibilit¨¤.txt";
	FILE* fp, * fp1;
	fp = fopen("db_professori.txt", "r");
	if (fp == NULL)
	{
		printf("non c'¨¨ database dei prof, non posso avere file di indisponibilit¨¤\n");
		exit(0);
	}
	else
	{
		listaprofs = getprofsfromdb(_strdup("db_professori.txt"));
		if (listaprofs.size() == 0)
		{
			printf("non c'¨¨ database dei prof, non posso avere file di indisponibilit¨¤\n");
			fclose(fp);
			exit(0);
		}
	}
	fclose(fp);
	fp1 = fopen(filename, "r");
	if (fp1 == NULL)
	{
		printf("apertura file fallito,esco\n");
		exit(0);

	}
	fp = fopen(name.c_str(), "w");
	std::stringstream ss1(annoacca);
	while (ss1.good())
	{
		std::string substr;
		getline(ss1, substr, '-');
		anni.push_back(substr);
	}
	while (1)
	{
		res = fgets(buf, BUF, fp1);
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
		ok = profinlist(listaprofs, vect[0]);
		if (ok == false)
		{
			printf("prof %s non presente in db, file non conforme, esco\n", vect[0].c_str());
			fclose(fp1);
			remove(name.c_str());
			exit(0);
		}
		fprintf(fp, "%s ", vect[0].c_str());
		for (i = 1; i < vect.size(); i++)
		{
			ok1 = checkdata(vect[i], anni[1]);
			if (ok1 == 1)
				fprintf(fp, "%s ", vect[i].c_str());
		}
		fprintf(fp, "\n");
		vect.clear();

	}
	fclose(fp);
	return;

}

int Uni::checkdata(std::string data, std::string anno)
{
	std::vector<std::string> datai;
	std::stringstream ss1(data);
	while (ss1.good())
	{
		std::string substr;
		getline(ss1, substr, '|');
		datai.push_back(substr);
	}
	int ok = checkdatainside(datai[0], anno);
	int ok1 = checkdatainside(datai[1], anno);
	if (ok == 1 && ok1 == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}

int Uni::checkdatainside(std::string data, std::string anno)
{
	std::vector<std::string> datai;
	std::stringstream ss1(data);
	while (ss1.good())
	{
		std::string substr;
		getline(ss1, substr, '-');
		datai.push_back(substr);
	}
	if (datai[0] == anno)
		return 1;
	else
		return 0;
}

void Uni::generateesami(std::string annoaccademico, std::string fileoutname)
{
	std::vector<Corsobig> corsi;
	std::vector<Prof> profs;
	std::vector<Corsostudio> corsistudio;
	std::ifstream fp3("db_corsi_studio.txt");
	std::ifstream fp1("db_corsi.txt");
	FILE* fp2;
	if (filework(fp1) == 1)
	{
		 getcorsifromdb("db_corsi.txt",&corsi);
		 fp1.close();
	}
	if (filework(fp3) == 1)
	{
		corsistudio = getcorsostudiolistfromdb("db_corsi_studio.txt", &corsi);
		fp3.close();
	}
	fp2 = fopen("db_professori.txt", "r");
	if (fp2 != NULL)
	{
		char* filename = _strdup("db_professori.txt");
		profs = getprofsfromdb(filename);
		free(filename);
		fclose(fp2);
	}
	else
	{
		std::cout << "apertura file fallito, esco \n";
		exit(0);
	}
	std::string inddata = annoaccademico + "_indisponibilit¨¤.txt";
	std::ifstream fp5(inddata);
	if (filework(fp5) == 1)
	{
		chargeindtime(inddata, &profs);
		fp5.close();
	}
	std::string filedata = annoaccademico + "_esami.txt";
	std::ifstream fp4(filedata);
	std::string line;
	int i = 0;
    std::vector<std::string> vect;
	std::vector<Sessione> sessioni;
	if (filework(fp4) == 1)
	{
		while (std::getline(fp4, line))
		{
			std::string data = line;
			std::stringstream ss(data);
			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ' ');
				vect.push_back(substr);
			}
			Sessione s;
			s.definetime(stoi(vect[0]), stoi(vect[1]), stoi(vect[2]), stoi(vect[3]), stoi(vect[4]), stoi(vect[5]));
			int giornitot = assoluto(calcolagiorni(stoi(vect[2]), stoi(vect[1]), stoi(vect[0])) - calcolagiorni(stoi(vect[5]), stoi(vect[4]), stoi(vect[3])));
			s.definegiornitot(giornitot);
			s.definesesgiorni();
			s.initsesgiornifascie();
			s.initgiornistraordinario();
			impostaesami(&s, corsistudio, corsi, profs, i + 1,annoaccademico);
			i++;
			sessioni.push_back(s);
			vect.clear();
		}
		if (sessioni.size() == 3)
		{
			for (i = 0; i < sessioni.size(); i++)
			{
				generateesamefile(sessioni[i], sessioni[i].getanno(), i + 1);
			}
		}
		else
		{
			fp4.close();
			std::cout << "impossibile generare esami\n";
			exit(0);
		}
	}
	else
	{
		std::cout << "impossibile aprire file\n";
		exit(0);
	}

}
void Uni::generateesamefile(Sessione s, std::string anno, int si)
{
	std::stringstream ss;
	ss << si;
	std::string filename = "sessione_esame_" + anno + "_" + ss.str() + ".txt";
	std::ofstream fout(filename);
	int i, j;
	for (i = 0; i < s.getsessgiornivec().size(); i++)
	{
		if (s.getsessgiornivec()[i].getqualegiorno() != "Domenica")
		{
			fout << s.getsessgiornivec()[i].getgiornodata() + "\n";
			s.getsessgiornivec()[i].printgiorno(&fout);
			fout << "\n";
		}
	}
	fout.close();
	return;

}

void Uni::impostaesami(Sessione* s, std::vector<Corsostudio> corsistudiolist, std::vector<Corsobig> corsi, std::vector<Prof> profs,int ns, std::string annoaccademico)
{
	int i,j,k;
	int posi;
	for (i = 0; i < corsistudiolist.size(); i++)
	{
		for (j = 0; j < corsistudiolist[i].getcorsistudio().size(); j++)
		{
			for (k = 0; k < corsistudiolist[i].getcorsistudio()[j].idcorsivet.size(); k++)
			{
				std::string corsostudioid = corsistudiolist[i].getid();
				int pos = getcorsopos(corsistudiolist[i].getcorsistudio()[j].idcorsivet[k], corsi);
				posi=programmauncorsoesame(s, &corsi[pos], profs, corsistudiolist, ns,corsostudioid,corsi[pos].getidcorso(),annoaccademico);
			}
		}
		
	}
}


int Uni::programmauncorsoesame(Sessione* s, Corsobig *c, std::vector<Prof> profs, std::vector<Corsostudio> corsistudio, int ns,std::string corsostudioid,std::string idcorso, std::string annoaccademico)
{
	int ses;
	int ok;
	if (c->getses() % 2 == 0)
	{
		ses = 2;
	}
	else
	{
		ses = 1;
	}
	switch (ns)
	{
	case 1:
	{
		if (ns == ses)
		{
			ok=programma2(s, c, profs, corsistudio,corsostudioid,annoaccademico);
			if (ok != 1)
			{
				;
			}

		}
		else
		{
			ok=programma1(s, c, profs, corsistudio, corsostudioid, annoaccademico);
			if (ok != 1)
			{
				;
			}
		}
		break;
	}
	case 2:
	{
		if (ns == ses)
		{
			ok = programma2(s, c, profs, corsistudio, corsostudioid, annoaccademico);
			if (ok != 1)
			{
				;
			}
		}
		else
		{
			ok = programma1(s, c, profs, corsistudio, corsostudioid, annoaccademico);
			if (ok != 1)
			{
				;
			}
		}
		break;
	}

	case 3:
	{
		ok = programma1(s, c, profs, corsistudio, corsostudioid, annoaccademico);
		if (ok != 1)
		{
			;
		}
		break;
	}
	}
	return 1;
}

int Uni::programma1(Sessione* s, Corsobig* c, std::vector<Prof> profs, std::vector<Corsostudio> corsistudio, std::string corsostudioid, std::string annoaccademico)
{
	int count = 0;
	int i = 0;
	Sessione s1 = *s;
	int flag = 0;
	int flag1 = 1, flag2 = 2, flag3 = 3;
	while (i < s->getsessgiornivec().size() && flag == 0)
	{
		if (i == 0)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame1(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else if (i == 1)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame1(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else if (i == s1.getsessgiornivec().size() - 1)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame1(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else if (i == s1.getsessgiornivec().size() - 2)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame1(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame1(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}

		}
		i++;
	}
	if (flag == 1)
	{
		*s = s1;
		return 1;
	}
	else
	{
		return -1;
	}
}
int Uni:: programma2(Sessione* s, Corsobig *c, std::vector<Prof> profs, std::vector<Corsostudio> corsistudio,std::string corsostudioid, std::string annoaccademico)
{
	int count = 0;
	int i=0;
	Sessione s1 = *s;
	int flag = 0;
	while(i < s->getsessgiornivec().size()&&flag==0)
	{
		if (i == 0)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else if (i == 1)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i -1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
							
						}
						else if (pos == -2)
						{
							std::cout << "non esiste il corso a questo anno,impossibile programmare esame " + c->getidcorso() + "\n";
							return -1;
						}
						
					}
				}
			}
		}
		else if (i == s1.getsessgiornivec().size() - 1)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i -2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i -1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else if (i == s1.getsessgiornivec().size() - 2)
		{
			if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
			{
				if (s1.getsessgiornivec()[i -2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
				{
					if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
					{
						int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
						if (pos > 0)
						{
							int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
							if (ok == 1)
							{
								std::cout << "esame settato con successo" + c->getidcorso() + "\n";
								flag = 1;
							}
							else if(ok==-1)
							{
								std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
								flag = 1;
							}
						}
					}
				}
			}
		}
		else
		{
		if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
		{
			if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
			{
				if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
				{
					int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
					if (pos > 0)
					{
						int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
						if (ok == 1)
						{
							std::cout << "esame settato con successo" + c->getidcorso() + "\n";
							flag = 1;
						}
						else if(ok==-1)
						{
							std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
							flag = 1;
						}
					}
				}
			}
		}

        }
		i++;
	}
	if (flag == 1)
	{
		i = i + 13;
		if (i < s->getsessgiornivec().size() - 1)
		{
			flag = 0;
			while (i < s->getsessgiornivec().size() && flag == 0)
			{
				if (i == 0)
				{
					if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
					{
						if (s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
						{
							if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
							{
								int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
								if (pos > 0)
								{
									int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
									if (ok == 1)
									{
										std::cout << "esame settato con successo" + c->getidcorso() + "\n";
										flag = 1;
									}
									else if(ok==-1)
									{
										std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
										flag = 1;
									}
								}
							}
						}
					}
				}
				else if (i == 1)
				{
					if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
					{
						if (s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
						{
							if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
							{
								int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
								if (pos > 0)
								{
									int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
									if (ok == 1)
									{
										std::cout << "esame settato con successo" + c->getidcorso() + "\n";
										flag = 1;
									}
									else if(ok==-1)
									{
										std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
										flag = 1;
									}
								}
							}
						}
					}
				}
				else if (i == s1.getsessgiornivec().size() - 1)
				{
					if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
					{
						if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
						{
							if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
							{
								int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
								if (pos > 0)
								{
									int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
									if (ok == 1)
									{
										std::cout << "esame settato con successo" + c->getidcorso() + "\n";
										flag = 1;
									}
									else if(ok==-1)
									{
										std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
										flag = 1;
									}
								}
							}
						}
					}
				}
				else if (i == s1.getsessgiornivec().size() - 2)
				{
					if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
					{
						if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i -1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
						{
							if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
							{
								int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
								if (pos > 0)
								{
									int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
									if (ok == 1)
									{
										std::cout << "esame settato con successo" + c->getidcorso() + "\n";
										flag = 1;
									}
									else if(ok==-1)
									{
										std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
										flag = 1;
									}
								}
							}
						}
					}
				}
				else
				{
					if (s1.getsessgiornivec()[i].getqualegiorno() != "Domenica")
					{
						if (s1.getsessgiornivec()[i - 2].presentecorsostudioid(corsistudio, corsostudioid) != 1 && s1.getsessgiornivec()[i + 2].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i + 1].presentecorsostudioid(corsistudio, corsostudioid) != 1&& s1.getsessgiornivec()[i - 1].presentecorsostudioid(corsistudio, corsostudioid) != 1)
						{
							if (profpresente(c, profs, s1.getsessgiornivec()[i], annoaccademico) == 1)
							{
								int pos = getgiornofreepos(s1.getsessgiornivec()[i], c, annoaccademico);
								if (pos > 0)
								{
									int ok = setesame2(&s1, c, pos, c->getidcorso(), corsostudioid,i);
									if (ok == 1)
									{
										std::cout << "esame settato con successo" + c->getidcorso() + "\n";
										flag = 1;
									}
									else if(ok==-1)
									{
										std::cout << "esame gi¨¤ impostato aggiungo idcorsostudio" + c->getidcorso() + "\n";
										flag = 1;
									}
								}
							}
						}
					}

				}
				i++;
			}
			if (flag == 1)
			{
				*s = s1;
				return 1;
			}
		}

	}
	else
	{
	return -1;

    }

}

int Uni::setesame1(Sessione* s, Corsobig* c, int pos, std::string corsoid, std::string corsostudioid, int i)
{
	if (c->checkesameimpostato() == 1)
	{
		int posi = s->getsessgiornivec()[i].getposiid(corsoid);
		s->setesameaddcorsotudioid(i, posi, corsostudioid);
		return -1;
	
	}
	int count = pos;
	int counti = 0;
	int j;
	for (j = 0; j < s->getsessgiornivec()[i].getfascecorsiid().size(); j++)
	{
		if (s->getsessgiornivec()[i].getfascecorsiid()[j] == "Free")
		{
			counti++;
			s->setesameaddcorsoid(i, j, corsoid);
			s->setesameaddcorsotudioid(i, j, corsostudioid);
		}
		if (counti == count)
		{
			c->impostaesame();
			return 1;
		}
	}
	return -2;

}
int Uni::setesame2(Sessione *s, Corsobig* c, int pos, std::string corsoid, std::string corsostudioid,int i)
{
	if (c->checkesameimpostato2() == 1)
	{
		int posi = s->getsessgiornivec()[i].getposiid(corsoid);
		s->setesameaddcorsotudioid(i, posi, corsostudioid);
		return -1;
	}
	int count = pos;
	int counti = 0;
	int j;
	for (j = 0; j < s->getsessgiornivec()[i].getfascecorsiid().size(); j++)
	{
		if (s->getsessgiornivec()[i].getfascecorsiid()[j] == "Free")
		{
			counti++;
			s->setesameaddcorsoid(i, j, corsoid);
			s->setesameaddcorsotudioid(i, j, corsostudioid);
		}
		if (counti == count)
		{
			c->impostaesame2();
			return 1;
		}
	}
	return -2;
}
int Uni::getgiornofreepos(Giorno g,Corsobig *c,std::string annoaccademico)
{
	int time = c->getexamtime(annoaccademico);
	if (time == -1)
	{
		return -2;
	}
	int pos;
	float dadiv = 120;
	int count = 0;
	int i;
	if (time > 0)
	{
		pos = (int)ceil(time / dadiv);
		for (i = 0; i < g.getfascecorsiid().size(); i++)
		{
			if (g.getfascecorsiid()[i] == "Free")
			{
				count++;
			}
		}
		if (count >= pos)
			return pos;
		else
			return -1;
	}
	return -1;
}
int Uni::profpresente(Corsobig *c, std::vector<Prof> profs, Giorno g, std::string annoaccademico)
{
	int i, j, ok = 1;;
	for (i = 0; i < c->getcorsismall().size(); i++)
	{
		if (c->getcorsismall()[i].getannoaccademico() == annoaccademico)
		{
			std::vector<collabprof> collabprofs = c->getcorsismall()[i].getcollabprofvec();
			for (j = 0; j < collabprofs.size(); j++)
			{
				if (checkcollabproftime(collabprofs[j], profs, g) == -1)
				{
					return -1;
				}
			}
		}
	}
	return 1;

}
int Uni::checkcollabproftime(collabprof p, std::vector<Prof> profs, Giorno g)
{
	int i;
	int pos = getprofpos(p.matricolatit, profs);
	if (profs[pos].getindtimevec().size() > 0)
	{
		for (i = 0; i < profs[pos].getindtimevec().size(); i++)
		{
			if (profs[pos].getindtimevec()[i].anno == g.getanno() && profs[pos].getindtimevec()[i].mese == g.getmese() && profs[pos].getindtimevec()[i].giorno == g.getgiorno())
			{
				return -1;
			}
		}
	}
	
	return 1;
}

//file
int Uni::filework(std::ifstream& file)
{
	std::string base, tmp;
	char c;
	if (!file.is_open()) {
		std::cerr << "errore apertura file" << std::endl;
		return -1;
	}
	return 1;
}