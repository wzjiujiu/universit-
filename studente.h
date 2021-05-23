#ifndef STUDENTE_H
#define STUDENTE_H
#include <string>
#include<iostream>

class Studente
{
public:
	
	void define(std::string matricola,std::string nome, std::string cognome,std::string email);
	void printdata();
	std::string getname();
	std::string getsurname();
	std::string getmatricola();
	std::string getemail();



private:
	std::string studentname = "";
	std::string surname = "";
	std::string matricola = "";
	std::string eamil = "";
};



#endif
