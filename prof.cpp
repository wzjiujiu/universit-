#include "prof.h"

void Prof::define(std::string matricola, std::string profnome, std::string profsurname, std::string email)
{
	this->profname = profnome;
	this->profsurname = profsurname;
	this->matricola = matricola;
	this->eamil = email;
}

void Prof::printdata()
{
	if (this->profname == "" && this->profsurname == "")
	{
		printf("nothing to print");
	}
	std::cout << this->profname << std::endl;
	std::cout << this->profsurname << std::endl;
}

std::string Prof::getname()
{
	return this->profname;
}
std::string Prof::getsurname()
{
	return this->profsurname;
}
std::string Prof::getmatricola()
{
	return this->matricola;
}
std::string Prof::getemail()
{
	return this->eamil;
}
