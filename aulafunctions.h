#ifndef AULA_FUNCTIONS_H
#define AULA_FUNCTIONS_H
#include "aula.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#define BUF 500


std::vector<Aula>getaule(char* filename);
std::vector<Aula>getaulefromdb(FILE* fp);
void generetedbaule(char* filename, std::vector<Aula>listaule);


#endif
