#ifndef STUDENTEFUNCTIONS_H
#define STUDENTEFUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "studente.h"
#include <vector>
#define BUF 500
#define N 500

void generetedbstudenti(char* filename, std::vector<Studente>listastudenti);
std::vector <Studente> getstudenti(char* filename);
std::vector<Studente>getstudentsfromdb(FILE* fp);
std::vector<Studente> updatestudent(char* filename);

#endif
