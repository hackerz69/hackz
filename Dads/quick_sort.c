#include<stdio.h>
#include<stdlib.h>

int partition(int arr[], int l, int r)
{
    int pivot = arr[r];
    int i = l-1;
    for(int j=l; j<r; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    int tmp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = tmp;
    return i+1;
}
void quickSort(int arr[], int l, int r)
{
    if(l<r)
    {
        int pi = partition(arr,l,r);
        quickSort(arr,l,pi-1);
        quickSort(arr,pi+1,r);
    }
}

int main()
{
    int arr[5] = {5, 4, 3, 2,1};
    quickSort(arr,0,4);
    printf("The sorted array is:\n");
    for(int i=0; i<5; i++)
    {
        printf("%d\t", arr[i]);
    }
    return 0;
}