#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// file print first n lines
void filePrintN(FILE *fp, int n)
{
    int i = 0;
    char ch;
    printf("\nPrinting First %d Lines.\n\n", n);
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            i++;
        printf("%c", ch);
        if (i == n)
            break;
    }
    printf("\n");
}

// no of lines in file
int noOfLinesF(FILE *fp)
{
    FILE *f = fp;
    int l = 0;
    char ch;
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch == '\n')
            l++;
    }
    return ++l;
}

// file print last n lines
void filePrintRN(FILE *fp, int n)
{
    int i = 1, l, startprinting;
    char ch;
    l = noOfLinesF(fp);
    startprinting = (l - n) + 1;
    fseek(fp, 0, SEEK_SET);
    printf("\nPrinting Last %d Lines.\n\n", n);
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            i++;
            // printf("\nlineno %d\n",i);
        }

        if (i >= startprinting)
        {
            printf("%c", ch);
        }
    }

    printf("\n");
}

// print all lines
void printAllF(FILE *fp)
{
    char ch;
    printf("\nPrinting All Lines In The File.\n\n");
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");
}

int main(void)
{
    char input[100], cmd[50], par1[50], par2[50], temp[50];
    int i, j, count;
    FILE *fp = NULL;
    while (1)
    {
    start:
        input[0] = '\0';
        cmd[0] = '\0';
        par1[0] = '\0';
        par2[0] = '\0';
        i = 0;
        count = 0;
        printf("\n[myshell] ");
        fgets(input, 100, stdin);
        if (strcmp(input, "exit\n") == 0 || strcmp(input, "quit\n") == 0)
        {
            return 0;
        }
        else
        {

            while (input[i] != '\n' && input[i] != '\0')
            {
                j = 0;
                while (input[i] != ' ' && input[i] != '\n' && input[i] != '\0')
                {
                    temp[j] = input[i];
                    j++;
                    i++;
                }
                temp[j] = '\0';
                count++;
                if (count == 1)
                {
                    strcpy(cmd, temp);
                }
                else if (count == 2)
                {
                    strcpy(par1, temp);
                }
                else if (count == 3)
                {
                    strcpy(par2, temp);
                }
                else
                {
                    printf("\nERROR: TOO MANY ARGUMENTS.\n");
                    goto start;
                }
                i++;
            }
            // printf("\ncmd: %s\n",cmd);
            // printf("\npar1: %s\n",par1);
            // printf("\npar2: %s\n",par2);
            if (strcmp(cmd, "typeline") == 0)
            {
                if (strcmp(par1, "n") == 0)
                {
                    fp = fopen(par2, "r");
                    if (fp == NULL)
                    {
                        printf("\nERROR: NO SUCH FILE EXISTS.\n");
                        goto start;
                    }
                    else
                    {
                        filePrintN(fp, 2);
                    }
                }
                else if (strcmp(par1, "-n") == 0)
                {
                    fp = fopen(par2, "r");
                    if (fp == NULL)
                    {
                        printf("\nERROR: NO SUCH FILE EXISTS.\n");
                        goto start;
                    }
                    else
                    {
                        // printf("\nlines: %d\n",noOfLinesF(fp));
                        filePrintRN(fp, 2);
                    }
                }
                else if (strcmp(par1, "a") == 0)
                {
                    fp = fopen(par2, "r");
                    if (fp == NULL)
                    {
                        printf("\nERROR: NO SUCH FILE EXISTS.\n");
                        goto start;
                    }
                    else
                    {
                        printAllF(fp);
                    }
                }
                else
                {
                    printf("\nERROR: INVALID PARAMETER 1.\n");
                    goto start;
                }
            }
            else
            {
                printf("\nERROR: INVALID COMMAND.\n");
                goto start;
            }
        }
    }
}