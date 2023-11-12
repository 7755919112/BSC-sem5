#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<dirent.h>
void displayFileNames(char str[]){
    DIR *directory;
    struct dirent *entry;
    directory=opendir(str);
    printf("\nDisplaying file name in the directory.\n\n");
    while((entry=readdir(directory))!=NULL){
        if(entry->d_type==DT_REG){
            printf("%s\n",entry->d_name);
        }
    }
}
int noOfEntriesInDirectory(char str[]){
    int count=0;
    DIR *directory;
    struct dirent *entry;
    directory=opendir(str);
    while((entry=readdir(directory))!=NULL)
    {
        //printf("%s:%d\n",entry->d_name,entry->d_type);
        count++;
    }
    return count;
}
void displayInodeNumber(char str[]){
    DIR *directory;
    struct dirent *entry;
    directory=opendir(str);
    printf("\nDisplaying file name in the directory.\n\n");
    while((entry=readdir(directory))!=NULL){
        if(entry->d_type==8){
            printf("%ld : %s\n",entry->d_ino,entry->d_name);
        }
    }
}
int main()
{
    char cmd[100], func[50], p1[50], p2[50], temp[50];
    int i, j, count, ch;
    pid_t pid;
    char *arg[3];
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

            if (strcmp(func, "list") == 0)
            {

                if (strcmp(p1, "f") == 0)
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
                        // system("ls -n");
                        displayFileNames(p2);
                    }
                    else
                    {
                        // parent process
                        wait(NULL);
                    }
                }

                else if (strcmp(p1, "n") == 0)
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
                        ch=noOfEntriesInDirectory(p2);
                        printf("\nNumber of entries in file: %d",ch);
                    }
                    else
                    {
                        // parent process
                        wait(NULL);
                    }
                }
                else if (strcmp(p1, "i") == 0)
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
                        displayInodeNumber(p2);
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