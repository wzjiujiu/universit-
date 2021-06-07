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

std::string Studente::generatematricola()
{
	int dif;
	int num = rand() % 100000;
	while ((num % 2 !=0))
	{
		num = rand() % 100000;
	}
	if (num < 100000)
	{
		if (num < 10)
		{
			num = num * 100000;
		}
		else if (num < 100)
		{
			num = num * 10000;
		}
		else if (num < 1000)
		{
			num = num * 1000;

		}
		else if (num < 10000)
		{
			num = num * 100;
		}
		else if (num < 100000)
		{
			num = num * 10;
		}
	
	}
	std::stringstream ss;
	ss << num;
	std::string partenum = ss.str();
	std::string matricola = "s" + partenum;
	return matricola;
}

void Studente::updatename(std::string studentname)
{
	this->studentname = studentname;
}
void Studente::updatesurname(std::string surname)
{
	this->surname = surname;
}
void Studente::updteemail(std::string email)
{
	this->eamil = email;
}