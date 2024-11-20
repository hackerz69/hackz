#include <stdio.h>
void selection_sort(int arr[], int n)
{
    // Selection Sort
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int temp;
            if (arr[j] < arr[i])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
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
    // Array elements
    int arr1[5] = {45, 23, 51, 19, 8};
    // Invoking the sorting methods
    selection_sort(arr1,5);
    return 0;
}