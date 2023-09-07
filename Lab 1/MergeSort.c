#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int mostRightIndex = sizeof(arr) / sizeof(int) - 1;

    mergeSort(arr, 0, mostRightIndex);

    for(int i = 0; i <= mostRightIndex; i++)
        printf("%d ", arr[i]);
}

void mergeSort(int arr[], int left, int right)
{
    if(right - left > 0){
        int mid  = (left + right) / 2;

        //recursive
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //combine the 2 sub arrays
        merge(arr, left, mid, right);
    }
    else
        return;
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
