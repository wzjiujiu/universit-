#include <stdio.h>

#define N 500
#define BUF 500
#include "portal.h"


using namespace std;


int main(int argc, char** argv)
{
	//Portal p;
	//p.portalrun(argc, argv);
	Uni universita;
	vector<Studente> listastudenti;
	char *filename;
	vector<Prof> listprofessori;
	vector<Aula> listaule;
	vector<Corsobig> listcorsi,listcorsi1;
	vector<Corsostudio> listcorsistudio;
	char* val;
	
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
	int flag = 1;
	filename = _strdup("studenti.txt");
    listastudenti = universita.getstudenti(filename);
	val = _strdup("db_studenti.txt");
	universita.generetedbstudenti(val, listastudenti);
	free(val);
	val = _strdup("update_studenti.txt");
	listastudenti = universita.updatestudent(val);
	free(val);
	val = _strdup("db_studenti.txt");
	universita.generetedbstudenti(val, listastudenti);
	free(filename);
	//set prof
	filename = _strdup("professori.txt");
	listprofessori = universita.getprofs(filename);
	free(val);
	val = _strdup("db_professori.txt");
	universita.generetedbprofessori(val, listprofessori);
	listprofessori = universita.updateprof(_strdup("update_profs.txt"));
	universita.generetedbprofessori(_strdup("db_professori.txt"), listprofessori);
	free(filename);
	//set aule
	filename = _strdup("aule.txt");
	listaule = universita.getaule(filename);
	universita.generetedbaule(_strdup("db_aule.txt"), listaule);
	free(filename);
	filename = _strdup("corsi.txt");
	universita.getcorsi(filename,&listcorsi);
	universita.generatedbcorsi(_strdup("db_corsi.txt"), listcorsi);
	free(filename);
	filename = _strdup("corsi_studio.txt");
	listcorsistudio = universita.getcorsostudiolist(filename);
	universita.generatedbcorsistudio(_strdup("db_corsi_studio.txt"), listcorsistudio);
	universita.generateannoesamidata(_strdup("2019-2020"), _strdup("2020-1-12|2020-2-29"), _strdup("2020-6-6|2020-7-30"), _strdup("2020-9-1|2020-9-30"));
	universita.generatefileindisponibilita(_strdup("indisponibile.txt"), _strdup("2019-2020"));
	universita.inseriscicorso(_strdup("corsi_insert.txt"),&listcorsi1,&flag);
	if (flag == 1)
	{
		universita.generatedbcorsi(_strdup("db_corsi.txt"), listcorsi1);
	}
	universita.generateesami("2019-2020", "sessione_esami_2020.txt");
	
		//}
	//}*/	
}






