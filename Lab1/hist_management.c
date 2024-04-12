#include "calc.h"

char** allocate_memory(int size, int * counting, const char * fileName) {
    FILE * file = fopen(fileName, "r");

    char **hist = (char **)malloc(sizeof(char *) * size);
    if (hist == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    char chunk[100];
    int i = 0;
    while(fgets(chunk, sizeof(chunk), file) != NULL) {
        chunk[strcspn(chunk, "\n")] = '\0';
        hist[i] = strdup(chunk);
        i += 1;
        *counting += 1;
    }
    for (int j = i; j < size; j++)
    {
        hist[j] = (char *)malloc(sizeof(char) * 10);
        if (hist[j] == NULL)
        {
            perror("Memory allocation failed");
            for (int k = 0; k < j; k++)
            {
                free(hist[k]);
            }
            free(hist);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return hist;
}

void deallocate_memory(char *hist[], int size) {
    for (int i = 0; i < size; i++)
    {
        free(hist[i]);
    }
    free(hist);
}