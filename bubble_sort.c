#include<stdio.h>
void bubble_sort(int arr[], int n)
{
    // Bubble Sort
    for (int i = n; i > 0; i--)
    {
        for (int k = 0; k < i - 1; k++)
        {
            int temp;
            if (arr[k] > arr[k + 1])
            {
                temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
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
    bubble_sort(arr,6);
    return 0;
}