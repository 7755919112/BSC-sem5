#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        printf("\nFork failed.\n");
        return 0;
    }
    else if(pid==0){
        //child process
        printf("\nI am child process : %d and my parent id : %d\n",getpid(),getppid());
        //wait(NULL);
        sleep(1);
        printf("\nI am child process : %d and my parent id : %d\n",getpid(),getppid());
    }
    else{
        //parent process
        printf("\nI am Parent process : %d and my parent id : %d\n",getpid(),getppid());
    }
    return 0;
}
