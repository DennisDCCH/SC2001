#include <stdio.h>
#include <stdlib.h>

int threshold = 5;
int keyComparison = 0;

int main()
{
    int arr[] = {2, 5, 1, 6, 7, 3, 8, 4, 9};
    int mostRightIndex = sizeof(arr) / sizeof(int) - 1;

    hybridSort(arr, 0, mostRightIndex);

    for(int i = 0; i <= mostRightIndex; i++)
        printf("%d ", arr[i]);

    printf("\n%d", keyComparison);
}

void hybridSort(int arr[], int left, int right)
{
    if(right - left > threshold){
        int mid  = (left + right) / 2;

        //recursive
        hybridSort(arr, left, mid);
        hybridSort(arr, mid + 1, right);

        //combine the 2 sub arrays
        merge(arr, left, mid, right);
    }
    else
        insertionSort(arr, left, right);
}

void insertionSort(int arr[], int left, int right)
{
    int item;
    int size = right - left + 1;

    for(int i = 0; i < size; i++){
        item = arr[i + left];
        for(int j = i; j > 0; j--){
            keyComparison++;
            if(arr[j + left] < arr[j - 1 + left]){
                arr[j + left] = arr[j - 1 + left];
                arr[j - 1 + left] = item;
            }
            else
                break;
        }
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int tempLeftArray[leftSize], tempRightArray[rightSize];

    for(int i = 0; i < leftSize; i++)
        tempLeftArray[i] = arr[left + i];

    for(int i = 0; i < rightSize; i++)
        tempRightArray[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while(i < leftSize && j < rightSize){
        keyComparison++;
        if(tempLeftArray[i] <= tempRightArray[j])
            arr[k++] = tempLeftArray[i++];
        else
            arr[k++] = tempRightArray[j++];
    }

    while(i < leftSize)
        arr[k++] = tempLeftArray[i++];

    while(j < rightSize)
        arr[k++] = tempRightArray[j++];
}
