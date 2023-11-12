#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
int main()
{
    pid_t p;
    int n;
    p=fork();
    
    if(p==0)
    {
        //child process
        errno=0;
        n=nice(-20);
        printf("\nreturn value of nice child:%d\n",n);
        if(errno!=0 && n==-1)
        {
            printf("\nError in nice() call child.%d\n",n);
        }
        printf("\nI am Child Process.\n");

        
    }
    else{
        //parent process
        errno=0;
        n=nice(19);
        printf("\nreturn value of nice parent:%d\n",n);
        if(errno!=0 && n==-1)
        {
            printf("\nError in nice() call parent.%d\n",n);
        }
        printf("\nI am Parent Process.\n");
    }
    return 0;
}