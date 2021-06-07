#ifndef ESAME_FUNCTIONS_H
#define ESAME_FUNCTIONS_H

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "prof.h"
#include "proffunctions.h"


void generateannoesamidata(char* annoaccademico, char* data1, char* data2, char* data3);
int datainto(std::vector<std::string>d1, std::vector<std::string> d2, std::vector<std::string> d3, std::vector<std::string> anno, std::string filename);
std::vector<std::string> getdata(std::vector<std::string> d, int pos);
int getdif(std::vector<std::string>d1, std::vector<std::string> d2);
bool datavalida(int gg, int mm, int aa);
int giornimese(int aa, int mm);
int assoluto(int gg);
bool bisestile(int aa);
int calcolagiorni(int gg, int mm, int aa);
void generatefileindisponibilita(char *filename,char *annoaccademico);
int checkdata(std::string data, std::string anno);
int checkdatainside(std::string data, std::string anno);


#endif
