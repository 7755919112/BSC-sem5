#include<stdio.h>
#include<stdlib.h>
//convert string to integers
void toIntArray(int *arr,char* ch[],int argc)
{
    int i;
    for(i=0;i<argc;i++)
    {
        arr[i]=atoi(ch[i+1]);
    }
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
//binary search program
int binary_search(int arr[], int left, int right, int target) {  
    while (left <= right) {  
        int mid = left + (right - left) / 2;  
  
        if (arr[mid] == target) {  
            return mid;  
        } else if (arr[mid] < target) {  
            left = mid + 1;  
        } else {  
            right = mid - 1;  
        }  
    }  
  
    return -1;  // Target not found  
}
int main(int argc,char *argv[])
{
    int *arr,ele,result;
    //printf("%s %d",argv[1],argc);
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ...", argv[0]);
        return 1;
    }
    arr=(int*)malloc(sizeof(int)*(argc-1));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    toIntArray(arr,argv,(argc-1));
    printf("Enter the element to search:  ");
    scanf("%d",&ele);
    result=binary_search(arr,0,argc-1,ele);
    if(result==-1){
        printf("\nElement not found.\n");
        
    }
    else{
        printf("\nElement  found at index %d.\n",result);
    }
    return 0;
}