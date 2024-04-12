#include "calc.h"

int main()
{
    FILE * file = fopen("ans.txt", "r");
    const char * fileName = "ans.txt";
    const char * histFile = "hist.txt";
    float ANS;
    fscanf(file, "%f", &ANS);
    fclose(file);
    int counting = 0;
    char **hist = allocate_memory(5, &counting, histFile);

    if (hist == NULL) {
        return EXIT_FAILURE;
    }

    calculate(ANS, hist, counting, fileName, histFile);

    deallocate_memory(hist, 5);

    return 0;
}