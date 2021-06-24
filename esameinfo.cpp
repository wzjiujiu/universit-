#include "esameinfo.h"


void Esameinfo::addprofindisponibili(Prof p)
{
	this->profindisponibili.push_back(p);
}

void Esameinfo::addorariprofindisponibili(int pos, std::string orario)
{
	this->orariprofindisponibi[pos].push_back(orario);
}

void Esameinfo::generaldefine(std::string annoaccademico, std::string datas1, std::string datas2, std::string datas3)
{
	this->annoaccademico = annoaccademico;
	this->datas1 = datas1;
	this->datas2 = datas2;
	this->datas3 = datas3;
}