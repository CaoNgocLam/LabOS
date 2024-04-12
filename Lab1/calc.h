#ifndef _baseCal_H_
#define _baseCal_H_
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void calculate(float ANS, char *hist[], int counting, const char * ansFile, const char * histFile);
char** allocate_memory(int size, const char * fileName);
void deallocate_memory(char *hist[], int size);

#endif
