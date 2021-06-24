#ifndef PROF_H
#define PROF_H
#include <iostream>
#include<string>
#include <sstream>
#include <vector>
typedef struct d
{
	int anno;
	int giorno;
	int mese;
}ind;


class Prof
{
public:
	void define(std::string matricola, std::string profnome, std::string profsurname, std::string email);
	void printdata();
	std::string getname();
	std::string getsurname();
	std::string getmatricola();
	std::string getemail();
	std::string generatematricola();
	void updatename(std::string profnome);
	void updatesurname(std::string profsurname);
	void updateemail(std::string email);
	ind createind(int anno, int mese, int giorno);
	void addindtime(ind indtime);
	std::vector<ind> getindtimevec();


private:
	std::string profname = "";
	std::string profsurname = "";
	std::string matricola = "";
	std::string eamil = "";
    std::vector<ind> indtime;
};


#endif
