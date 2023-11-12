#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    pid=fork();
    char path[]="/home/maruti/Documents/osExams/ass1/a1";
    char *argv[2];
    argv[0]=(char*)"a1";
    argv[1]=NULL;
    if(pid==-1){
        printf("\nFork failed.\n");
        return 1;
    }
    else if(pid==0){
        //child process
        execve(path,argv,NULL);
    }
    else{
        //parent process
        
        wait(NULL);
        printf("\nHello this is parent.");
        printf("\nParent is terminating.\n");
    }
    return 0;
}