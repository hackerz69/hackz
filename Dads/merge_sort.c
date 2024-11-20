#include<stdio.h>
#include<stdlib.h>
void merge(int arr[], int f, int mid, int l)
{
    int n1 = mid - f + 1; // size of the 1st temp. array
    int n2 = l - mid; // size of the 2nd temp. array
// temporary arrays
    int a[n1];
    int b[n2];
// storing the elements from the main array into the two temporary arrays in 2 parts
    for(int i=0; i<n1; i++)
    {
        a[i] = arr[f+i]; // this is left part
    }    
    for(int i=0; i<n2; i++)
    {
        b[i] = arr[mid+1+i]; // this is the right part
    }
// sorting and merging the elements in the main array
    int i=0, j=0, k=f;
    while(i<n1 && j<n2)
    {
        if(a[i]<b[j])
        {
            arr[k] = a[i];
            k++;
            i++;
        }
        else
        {
            arr[k] = b[j];
            k++;
            j++;
        }
    }
    while(i<n1)
    {
        arr[k] = a[i];
        k++;
        i++;
    }
    while(j<n2)
    {
        arr[k] = b[j];
        k++;
        j++;
    }
}
void mergeSort(int arr[], int f, int l)
{
    if(f<l)
    {
        // dividing the array in two parts
        int mid = (f + l) / 2;
        mergeSort(arr,f,mid); // this is the left part
        mergeSort(arr,mid+1,l); // this is the right part
        merge(arr,f,mid,l); // this function merges the sorted parts
    }
}
int main()
{
    int arr[8] = {6, 3, 9, 5, 2, 8, 7, 1};
    mergeSort(arr,0,8);
    printf("The sorted array is:\n");
    for(int i=0; i<8-; i++)
    {
        printf("%d\t", arr[i]);
    }
    return 0;
}