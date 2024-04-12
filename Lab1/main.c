#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() { 
    FILE * file = fopen("hist.txt", "r");
    if (file == NULL) {
        perror("Unable to open the file!");
        return 1;
    }
    char **hist = (char **)malloc(sizeof(char *) * 5);
    char chunk[128];
    int i = 0;

    while(fgets(chunk, sizeof(chunk), file) != NULL){
        chunk[strcspn(chunk, "\n")] = '\0';
        hist[i] = strdup(chunk);
        printf("%s\n", hist[i]);
        i += 1;
    }
    fclose(file);
}