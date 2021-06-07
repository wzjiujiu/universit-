#include "aula.h"

void Aula::define(std::string aulaid, std::string aulatipo, std::string denominazione, int capienzamax, int capienzaexam)
{
	this->aulaid = aulaid;
	this->aulatipo = aulatipo;
	this->denominazione = denominazione;
	this->capienzamax = capienzamax;
	this->capienzaexam = capienzaexam;
}

std::string Aula:: getaulaid()
{
	return this->aulaid;
}
std::string Aula:: getaulatipo()
{
	return this->aulatipo;
}
std::string Aula::getdenominazione()
{
	return this->denominazione;
}
int Aula::getcapienzamax()
{
	return this->capienzamax;
}
int Aula::getcapenzaexam()
{
	return this->capienzaexam;
}

std::string Aula:: generateidaula()
{
	int num1 = rand() % 10;
	int num2 = rand() % 10;
	char alpha = 'A' + rand() % 26;
	char alpha1 = 'A' + rand() % 26;
	
	std::stringstream ss,ss1;
	ss << num1;
	std::string numero1 = ss.str();
	ss1 << num2;
	std::string numero2 = ss1.str();
	std::string let1(1,alpha);
	std::string let2(1, alpha1);

	std::string aulaid = numero1 + let1 + let2 + numero2;
	return aulaid;
}