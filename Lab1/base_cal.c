#include "calc.h"

void calculate(float ANS, char *hist[], int counting, const char * ansFile, const char * histFile)
{
    FILE *fileAns = fopen(ansFile, "w");
    
    while (true)
    {
        char expression[20], num1[20], oper[20], num2[20];
        printf(">> ");
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n")] = '\0';

        if (strcmp(expression, "EXIT") == 0)
        {
            FILE *fileHist = fopen(histFile, "w");
            for(int i = 0; i < counting; i++) {
                fprintf(fileHist, "%s\n", hist[i]);
            }
            fclose(fileHist);
            printf("Exiting program.\n");
            break;
        }
        else if (strcmp(expression, "HIST") == 0)
        {
            for (int i = 0; i < counting; i++)
            {
                printf("%s\n", hist[i]);
            }
            continue;
        }

        sscanf(expression, "%s %s %s", num1, oper, num2);

        float a, b;
        a = (strcmp(num1, "ANS") == 0) ? ANS : atof(num1);
        b = (strcmp(num2, "ANS") == 0) ? ANS : atof(num2);
        float res = ANS;
        if (strcmp(oper, "+") == 0)
        {
            res = a + b;
        }
        else if (strcmp(oper, "-") == 0)
        {
            res = a - b;
        }
        else if (strcmp(oper, "*") == 0)
        {
            res = a * b;
        }
        else if (strcmp(oper, "/") == 0)
        {
            if (b == 0)
            {
                printf("MATH ERROR\n");
                continue;
            }
            res = a / b;
        }
        else
        {
            printf("SYNTAX ERROR\n");
            continue;
        }
        FILE * file = fopen(ansFile, "w+");
        ANS = res;
        char result[10];
        if (res == (int)res)
        {
            int a = (int)res;
            sprintf(result, "%d", a);
            printf("%d\n", (int)res);
            fprintf(file, "%d\n", a); 
        }
        else
        {
            sprintf(result, "%.2f", res);
            printf("%.2f\n", res);
            fprintf(file, "%.2f\n", res); 
        }
        fclose(file);
        strcat(expression, " = ");
        strcat(expression, result);

        if (counting == 5)
        {
            for (int i = 1; i < 5; i++)
            {
                strcpy(hist[i - 1], hist[i]);
            }
            counting = 4;
        }
        strcpy(hist[counting], expression);
        counting++;
    }
    fclose(fileAns);
}