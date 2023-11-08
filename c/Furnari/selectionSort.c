#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            // select the min element in each loop
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        // put min at the correct position
        swap(&arr[min_index], &arr[i]);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[5] = {5, 1, 4, 2, 3};
    selectionSort(arr, 5);
    printf("Selection Sort: ");
    printArray(arr, 5);
}