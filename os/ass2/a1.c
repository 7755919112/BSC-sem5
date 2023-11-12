#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
int charInFile(char c[])
{

    FILE *fp = fopen(c, "r");
    int count = 0;
    char ch;
    if (fp == NULL)
    {
        printf("\nNo such File Exists.\n");
        return -1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {

        if (ch != ' ' && ch != '\n')
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}

int wordsInFile(char c[])
{

    int count = 0;
    char ch;
    FILE *fp = fopen(c, "r");
    if (fp == NULL)
    {
        printf("\nNo such File Exists.\n");
        return -1;
    }
    while ((ch = fgetc(fp)) != EOF)
    {

        if (ch == ' ' || ch == '\n')
        {

            count++;
        }
    }

    fclose(fp);
    return count + 1;
}
int linesInFile(char c[])
{

    FILE *fp = fopen(c, "r");
    int count = 0;
    char ch;
    if (fp == NULL)
    {
        printf("\nNo such File Exists.\n");
        return -1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {

        if (ch == '\n')
        {

            count++;
        }
    }
    fclose(fp);
    return count + 1;
}
int main()
{
    char cmd[100], func[50], p1[50], p2[50], temp[50];
    int i, j, count, ch;
    pid_t pid;
start:
    while (1)
    {
        i = 0;
        count = 0;
        strcpy(cmd, "\0");
        strcpy(func, "\0");
        strcpy(p1, "\0");
        strcpy(p2, "\0");
        strcpy(temp, "\0");
        printf("\n[myshell]$ ");

        fgets(cmd, 100, stdin);

        if (strcmp(cmd, "exit\n") == 0)
        {
            return 0;
        }

        else
        {
            while (cmd[i] != '\0' && cmd[i] != '\n')
            {
                j = 0;
                strcpy(temp, "\0");
                while (cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != ' ')
                {
                    temp[j] = cmd[i];
                    j++;
                    i++;
                }
                count++;
                i++;
                temp[j] = '\0';

                if (count == 1)
                {
                    strcpy(func, temp);
                }
                else if (count == 2)
                {
                    strcpy(p1, temp);
                }
                else if (count == 3)
                {
                    strcpy(p2, temp);
                }
                else
                {
                    printf("\nERROR:TOO MANY ARGUMENTS.\n");
                    goto start;
                }
            }

            if (strcmp(func, "count") == 0)
            {

                if (strcmp(p1, "c") == 0)
                {
                    pid = fork();
                    if (pid < 0)
                    {
                        printf("\nFailed in Fork\n");
                        exit(0);
                    }
                    else if (pid == 0)
                    {
                        // child process
                        printf("\nChild Process Running.\n");
                        ch = charInFile(p2);
                        if (ch == -1)
                            goto start;
                        else
                            printf("\nTotal Number of Characters in File: %d\n", ch);
                    }
                    else
                    {
                        // parent process
                        wait(NULL);
                    }
                }

                else if (strcmp(p1, "w") == 0)
                {
                    pid = fork();
                    if (pid < 0)
                    {
                        printf("\nFailed in Fork\n");
                        exit(0);
                    }
                    else if (pid == 0)
                    {
                        // child process
                        printf("\nChild Process Running.\n");
                        ch = wordsInFile(p2);
                        if (ch == -1)
                            goto start;
                        else
                            printf("\nTotal Number of Words in File: %d\n", ch);
                    }
                    else
                    {
                        // parent process
                        wait(NULL);
                    }
                }
                else if (strcmp(p1, "l") == 0)
                {
                    pid = fork();
                    if (pid < 0)
                    {
                        printf("\nFailed in Fork\n");
                        exit(0);
                    }
                    else if (pid == 0)
                    {
                        // child process
                        printf("\nChild Process Running.\n");
                        ch = linesInFile(p2);
                        if (ch == -1)
                            goto start;
                        else
                            printf("\nTotal Number of Lines in File: %d\n", ch);
                    }
                    else
                    {
                        // parent process
                        wait(NULL);
                    }
                }
                else
                {
                    printf("\nERROR:Invalid Arguments.\n");
                    goto start;
                }
            }
            else
            {
                printf("\nERROR:Invalid Command.\n");
                goto start;
            }
        }
    }

    return 0;
}