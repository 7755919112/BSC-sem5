#include<stdio.h>
#include<unistd.h>
int main()
{
    int pid;
    pid=fork();
    if(pid<0)
    {
        printf("\nFailed in creating Child Process.\n");
    }
    else if(pid==0){
        printf("\nI am Child Process.\n");
        printf("\nChild Process ID: %d\n",getpid());
    }
    else{
        printf("\nI am Parent Process.\n");
        printf("\nParent Process ID: %d\n",getpid());
    }
    return 0;
}