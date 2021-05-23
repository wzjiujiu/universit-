#ifndef AULA_H
#define AULA_H
#include <iostream>
#include <string>

class Aula
{
public:
	void define(std::string aulaid, std::string aulatipo, std::string denominazione, int capienzamax, int capienzaexam);
	std::string getaulaid();
	std::string getaulatipo();
	std::string getdenominazione();
	int getcapienzamax();
	int getcapenzaexam();

private:
	std::string aulaid = "";
	std::string aulatipo = "";
	std::string denominazione = "";
	int capienzamax = -1;
	int capienzaexam = -1;

};

#endif
