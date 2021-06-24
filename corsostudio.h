#ifndef CORSO_STUDIO_H
#define CORSO_STUDIO_H
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
typedef struct s
{
	std::vector<std::string> idcorsivet;
	int sem;
	
}semestre;


class Corsostudio
{
public:
	void generaldefine(std::string idcorsostudio, std::string tipo);
	std::string generateidcorsostudio();
	semestre definesemestre(std::vector<std::string> corsivet, int sem);
	std::string getid();
	std::string gettipo();
	void addcorsispenti(std::string id);
	void addcorsistudio(semestre s);
	void printsemestri(std::ofstream *fout);
	std::string returnstring(semestre s);
	void printcorsispenti(std::ofstream* fout);
	std::vector<semestre> getcorsistudio();
private:
	std::string idcorsostudio;
	std::vector<semestre> corsistudio;
	std::vector<std::string> corsispenti;
	std::string tipo;
};

#endif

