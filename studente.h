#ifndef STUDENTE_H
#define STUDENTE_H
#include <string>
#include<iostream>
#include<sstream>

class Studente
{
public:
	
	void define(std::string matricola,std::string nome, std::string cognome,std::string email);
	void printdata();
	std::string getname();
	std::string getsurname();
	std::string getmatricola();
	std::string getemail();
	std::string generatematricola();
	void updatename(std::string studentname);
	void updatesurname(std::string surname);
	void updteemail(std::string email);


private:
	std::string studentname = "";
	std::string surname = "";
	std::string matricola = "";
	std::string eamil = "";
};



#endif
