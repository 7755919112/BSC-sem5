#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
//input array elements
void inputArray(int *arr,int n)
{
    int i;
    printf("\nAccepting Array Elemants.\n");
    printf("\nEnter %d elements of the Array:\n",n);
    for(i=0;i<n;i++)
    {
        printf("[%d] : ",i);
        scanf("%d",&arr[i]);
    }
    printf("\n");
}
//display Array
void displayArray(int *arr, int n)
{
    int i;
    printf("\nDisplaying the Array.\n");
    for (i = 0; i < n; i++)
    {
        printf("\n[%d]: %d", i, arr[i]);
    }
    printf("\n");
}
//bubble sort
void bubblesort(int *arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//tostring func
void tostring(char c[],int n)
{
    int x=n,l=0,i;
    while(x!=0)
    {
        l++;
        x/=10;
    }
    c[l]='\0';
    for(i=l-1;i>=0;i--)
    {
        c[i]=(n%10)+'0';
        n/=10;
    }
}
int main()
{
    int n,*arr,i;
    pid_t pid;
    char **ch;
    char path[100]="/home/maruti/Documents/osExams/ass1/binarysearch";
    printf("\nEnter the number of elements in Array:  ");
    scanf("%d",&n);
    arr=(int*)malloc(sizeof(int)*n);
    inputArray(arr,n);
    bubblesort(arr,n);
    displayArray(arr,n);
    pid=fork();
    if(pid==-1)
    {
        printf("\nFork failed.\n");
        return 0;
    }
    else if(pid==0){
        //child process
        char *arg[n+1];
        arg[0]=(char*)"binarysearch";
        for( i=0;i<n;i++)
        {
            char *string = malloc (sizeof(char) * (20));
            tostring(string,arr[i]);
            arg[i+1] = string;
        }
        arg[n+1] = NULL;
        execve(path,arg,NULL);
    }
    else{
        //parent process
        wait(NULL);
        printf("\nParent done with execution. Terminating.\n");
    }
    
    return 0;
}