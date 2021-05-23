#ifndef PROF_H
#define PROF_H
#include <iostream>
#include<string>


class Prof
{
public:
	void define(std::string matricola, std::string profnome, std::string profsurname, std::string email);
	void printdata();
	std::string getname();
	std::string getsurname();
	std::string getmatricola();
	std::string getemail();


private:
	std::string profname = "";
	std::string profsurname = "";
	std::string matricola = "";
	std::string eamil = "";
};


#endif
