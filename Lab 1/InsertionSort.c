#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[] = {5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(int);

    insertionSort(arr, size);
    printArray(arr, size);
}

void insertionSort(int arr[], int size)
{
    int item;
    for(int i = 1; i < size; i++){
        item = arr[i];
        for(int j = i; j > 0; j--){
            if(arr[j] < arr[j - 1]){
                arr[j] = arr[j - 1];
                arr[j - 1] = item;
            }
            else
                break;
        }
    }
}

void printArray(int arr[], int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
}
