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
