#ifndef PROF_FUNCTIONS
#define PROF_FUNCTIONS
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "prof.h"
#define BUF 500

std::vector<Prof>getprofs(char* filename);
void generetedbprofessori(char* filename, std::vector<Prof>listaprofessori);
std::vector<Prof>getprofsfromdb(FILE *fp);
std::vector<Prof> updateprof(char* filename);

#endif
