#include<stdio.h>
#include<stdlib.h>

void insertion_sort(int arr[], int n)
{
    // Insertion Sort
    for (int i = 1; i < n; i++)
    {
        for (int l = i; l >= 1; l--)
        {
            if (arr[l - 1] > arr[l])
            {
                int temp;
                temp = arr[l - 1];
                arr[l - 1] = arr[l];
                arr[l] = temp;
            }
        }
    }
    // Printing the sorted array
    printf("The sorted array is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[6] = {12, 45, 23, 51, 19, 8};
    insertion_sort(arr,6);
    return 0;
}