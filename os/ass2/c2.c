#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int searchFirstOccourance(FILE *fp, char *str)
{
    char temp[10];
    int word = 0;
    while ((fscanf(fp, "%10s", temp)) != EOF)
    {
        word++;
        if (strcmp(temp, str) == 0)
            return word;
    }
    return -1;
}

void searchAllOccourance(FILE *fp, char *str)
{
    char temp[10];
    int word = 0;
    printf("\nPrinting The Occourance Of The Word.\n");
    while ((fscanf(fp, "%10s", temp)) != EOF)
    {
        word++;
        if (strcmp(temp, str) == 0)
            printf("\nOccourance Found At %d\n", word);
    }
}

int countOccourance(FILE *fp, char *str)
{
    char temp[10];
    int word = 0, count = 0;
    while ((fscanf(fp, "%10s", temp)) != EOF)
    {
        word++;
        if (strcmp(temp, str) == 0)
            count++;
    }
    return count;
}

int main(void)
{
    char input[100], cmd[50], par1[50], par2[50], par3[50], temp[50];
    int i, j, count, f, ret;
    FILE *fp = NULL;
    while (1)
    {
    start:
        i = 0;
        count = 0;
        input[0] = '\0';
        cmd[0] = '\0';
        par1[0] = '\0';
        par2[0] = '\0';
        par3[0] = '\0';
        temp[0] = '\0';
        printf("\n[myshell]$ ");
        fgets(input, 100, stdin);
        if (strcmp(input, "exit\n") == 0)
            exit(0);
        while (input[i] != '\n' && input[i] != '\0')
        {
            j = 0;
            while (input[i] != ' ' && input[i] != '\0' && input[i] != '\n')
            {
                temp[j] = input[i];
                i++;
                j++;
            }
            temp[j] = '\0';
            i++;
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
            else if (count == 4)
            {
                strcpy(par3, temp);
            }
            else
            {
                printf("\nERROR: TOO MANY ARGUMENTS.\n");
                goto start;
            }
        }
        if (strcmp(cmd, "search") == 0)
        {
            if (strcmp(par1, "f") == 0)
            {
                f = fork();
                if (f == 0)
                {
                    fp = fopen(par2, "r");
                    if (fp == NULL)
                    {
                        printf("\nERROR: NO SUCH FILE EXISTS.\n");
                        goto start;
                    }
                    else
                    {
                        ret = searchFirstOccourance(fp, par3);
                        if (ret == -1)
                        {
                            printf("\nNO Occourance Of The Word Found.\n");
                        }
                        else
                        {
                            printf("\nOccourance Of The Word Found At %d.\n", ret);
                        }
                    }
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    printf("\nChild Process Done With Execution.\n");
                }
            }
            else if (strcmp(par1, "a") == 0)
            {
                f = fork();
                if (f == 0)
                {
                    fp = fopen(par2, "r");
                    if (fp == NULL)
                    {
                        printf("\nERROR: NO SUCH FILE EXISTS.\n");
                        goto start;
                    }
                    else
                    {
                        searchAllOccourance(fp, par3);
                    }
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    printf("\nChild Process Done With Execution.\n");
                }
            }
            else if (strcmp(par1, "c") == 0)
            {
                f = fork();
                if (f == 0)
                {
                    fp = fopen(par2, "r");
                    if (fp == NULL)
                    {
                        printf("\nERROR: NO SUCH FILE EXISTS.\n");
                        goto start;
                    }
                    else
                    {
                        ret = countOccourance(fp, par3);
                        printf("\nOccourance count: %d\n", ret);
                    }
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    printf("\nChild Process Done With Execution.\n");
                }
            }
            else
            {
                printf("\nERROR: INVALID ARGUMENTS.\n");
                goto start;
            }
        }
        else
        {
            printf("\nERROR: INVALID COMMAND.\n");
            goto start;
        }
    }
    return 0;
}