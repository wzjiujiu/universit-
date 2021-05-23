#include "studente.h"

void Studente::define(std::string matricola, std::string nome, std::string cognome, std::string email)
{
	this->studentname = nome;
	this->surname = cognome;
	this->matricola = matricola;
	this->eamil= email;
}

void Studente::printdata()
{
	if (this->studentname == "" && this->surname == "")
	{
		printf("nothing to print");
	}
	std::cout << this->studentname << std::endl;
	std::cout << this->surname << std::endl;
}

std::string Studente::getname()
{
	return this->studentname;
}
std::string Studente::getsurname()
{
	return this->surname;
}
std::string Studente::getmatricola()
{
	return this->matricola;
}
std::string Studente::getemail()
{
	return this->eamil;
}
