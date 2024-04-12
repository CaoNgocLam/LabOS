#include "calc.h"

char** allocate_memory(int size, const char * fileName) {
    FILE * file = fopen(fileName, "rb+");
    fclose(file);

    char **hist = (char **)malloc(sizeof(char *) * size);
    if (hist == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        hist[i] = (char *)malloc(sizeof(char) * 10);
        if (hist[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; j++)
            {
                free(hist[j]);
            }
            free(hist);
            return NULL;
        }
    }
    
    return hist;
}

void deallocate_memory(char *hist[], int size) {
    for (int i = 0; i < size; i++)
    {
        free(hist[i]);
    }
    free(hist);
}