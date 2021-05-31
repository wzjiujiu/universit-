#ifndef ESAME_INFO_H
#define ESAME_INFO_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include<vector>
#include "prof.h"

class Esameinfo
{
public:
	void addprofindisponibili(Prof p);
	void addorariprofindisponibili(int pos, std::string orario);
	void generaldefine(std::string annoaccademico, std::string datas1, std::string datas2, std::string datas3);

private:
	std::string annoaccademico="";
	std::string datas1="";
	std::string datas2="";
	std::string datas3="";
	std::vector<Prof> profindisponibili;
	std::vector<std::vector<std::string>> orariprofindisponibi;
};


#endif
