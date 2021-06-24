#include "portal.h"

void Portal::portalrun(int argc, char** argv)
{
	Uni universita;
	std::vector<Studente> listastudenti;
	char* filename;
	std::vector<Prof> listprofessori;
	std::vector<Aula> listaule;
	std::vector<Corsobig> listcorsi, listcorsi1;
	std::vector<Corsostudio> listcorsistudio;
	char* val;
	if (argc <= 2)
	{
		printf("pochi argomenti.. esco\n");
		exit(0);
	}
	if (argc == 3)
	{
		if (strcmp(argv[1], "-a:s") == 0)
		{
			filename = _strdup(argv[2]);
			listastudenti = universita.getstudenti(filename);
			val = _strdup("db_studenti.txt");
			universita.generetedbstudenti(val, listastudenti);
			free(val);
			free(filename);
			std::cout << "successo!";
		}
		else if (strcmp(argv[1], "-a:d") == 0)
		{
			filename = _strdup(argv[2]);
			listprofessori = universita.getprofs(filename);
			val = _strdup("db_professori.txt");
			universita.generetedbprofessori(val, listprofessori);
			free(filename);
			free(val);
			std::cout << "successo!";
		}
		else if (strcmp(argv[1], "-a:a") == 0)
		{
			filename = _strdup(argv[2]);
			listaule = universita.getaule(filename);
			val = _strdup("db_aule.txt");
			universita.generetedbaule(val, listaule);
			free(filename);
			free(val);
		}
		else if (strcmp(argv[1], "-a:c") == 0)
		{
			filename = _strdup(argv[2]);
			universita.getcorsi(filename, &listcorsi);
			val = _strdup("db_corsi.txt");
			universita.generatedbcorsi(val, listcorsi);
			free(filename);
			free(val);
		}
		else if (strcmp(argv[1], "-a:f") == 0)
		{
			filename = _strdup(argv[2]);
			listcorsistudio = universita.getcorsostudiolist(filename);
			val = _strdup("db_corsi_studio.txt");
			universita.generatedbcorsistudio(val, listcorsistudio);
			free(filename);
			free(val);
		}
		
	}
}