#include "esamefunctions.h"

void generateannoesamidata(char* annoaccademico, char* data1, char* data2, char* data3)
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

int datainto(std::vector<std::string>d1, std::vector<std::string> d2, std::vector<std::string> d3, std::vector<std::string> anno, std::string filename)
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
std::vector<std::string> getdata(std::vector<std::string> d, int pos)
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

int getdif(std::vector<std::string>d1, std::vector<std::string> d2)
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

int giornimese(int aa, int mm)
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

bool datavalida(int gg, int mm, int aa)
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

int calcolagiorni(int gg, int mm, int aa)//calcola i giorni dal 01011900 fino al ggmmaa
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
bool bisestile(int aa)
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

int assoluto(int gg)
{
	if (gg < 0)
		return -gg;
	else
		return gg;
}

void generatefileindisponibilita(char* filename, char* annoaccademico)
{
	int i,ok1;
	bool ok;
	std::vector<std::string> vect,anni;
	char* res;
	char buf[BUF];
	std::vector<Prof> listaprofs;
	std::string annoacca(annoaccademico);
    std::string name = annoacca + "_indisponibilit¨¤.txt";
	FILE* fp,*fp1;
	fp = fopen("db_professori.txt", "r");
	if (fp == NULL)
	{
		printf("non c'¨¨ database dei prof, non posso avere file di indisponibilit¨¤\n");
		exit(0);
	}
	else
	{
		listaprofs = getprofsfromdb(fp);
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
			if(ok1==1)
			fprintf(fp, "%s ", vect[i].c_str());
		}
		fprintf(fp, "\n");
		vect.clear();

	}
	fclose(fp);
	return;
	
}

int checkdata(std::string data, std::string anno)
{
	std::vector<std::string> datai;
	std::stringstream ss1(data);
	while (ss1.good())
	{
		std::string substr;
		getline(ss1, substr, '|');
		datai.push_back(substr);
	}
	int ok=checkdatainside(datai[0],anno);
	int ok1=checkdatainside(datai[1],anno);
	if (ok == 1 && ok == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}

int checkdatainside(std::string data, std::string anno)
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
