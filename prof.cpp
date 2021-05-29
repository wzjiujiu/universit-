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

std::string Prof::generatematricola()
{
	int num = rand() % 100000;
	while (num % 2 != 0)
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
	std::string matricola = "d" + partenum;
	return matricola;
}

void Prof::updatename(std::string profnome)
{
	this->profname = profname;
}
void Prof::updatesurname(std::string profsurname)
{
	this->profsurname = profsurname;
}
void Prof::updateemail(std::string email)
{
	this->eamil = email;
}
