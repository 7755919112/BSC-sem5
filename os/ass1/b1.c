#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
// accept array function
void acceptArray(int *arr, int n)
{
    int i;
    printf("\nEnter %d elements.\n", n);
    for (i = 0; i < n; i++)
    {
        printf("\n[%d]: ", i);
        scanf("%d", &arr[i]);
    }
    printf("\n");
}

// display array function
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
// bubble sort function
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
//insertion sort
void insertionsort(int *arr,int n)
{
     int i, key, j;
    for (i = 1; i < n; i++) 
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
//main function
int main()
{
    int n, *arr;
    pid_t pid;
    printf("\nEnter the number of integers:  ");
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    acceptArray(arr, n);
    displayArray(arr, n);
    pid = fork();
    if (pid == 0)
    {
        // child process
        insertionsort(arr,n);
        printf("\nDisplaying Childs Sorted Array.\n");
        displayArray(arr,n);
    }
    else
    {
        // parent process
        bubblesort(arr,n);
        wait(NULL);
        printf("\nDisplaying Parents Sorted Array.\n");
        displayArray(arr,n);
    }
    return 0;
}
