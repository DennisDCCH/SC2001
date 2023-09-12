#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int threshold = 10;
int keyComparison = 0;
int maxNumber = 1000;
int trial = 1;

void hybridSort(int arr[], int left, int right);
void insertionSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
int randomInt();
int* generateArray(int size);


int main()
{
    int arrSize[] = {1000, 2000, 4000, 8000, 10000, 16000, 32000, 64000, 100000, 128000, 256000, 512000, 1000000, 1024000, 2048000, 4096000, 8192000, 10000000};
    int temp = sizeof(arrSize) / sizeof(int);
    int* arr;
    int arraySize;

//    for(int j = 0; j < temp; j++){
//        arraySize = arrSize[j];
//        arr = generateArray(arraySize);
//        hybridSort(arr, 0, arraySize - 1);
//        printf("Array Size: %d\nKey Comparison: %d\n\n", arraySize, keyComparison);
//        keyComparison = 0;
//        free(arr);
//    }

    for(int i = 0; i < 100; i++){
        arraySize = 10;
        arr = generateArray(arraySize);
        for(int j = 0; j < 10; j++)
            printf("%d ", arr[j]);
        printf("\n");
        free(arr);
    }

    return 0;
}

//Merge insertion Sort Algorithm
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

    int *tempLeftArray = (int *)malloc(leftSize * sizeof(int));
    int *tempRightArray = (int *)malloc(rightSize * sizeof(int));
    if(tempLeftArray == NULL || tempRightArray == NULL){
        printf("Memory not allocated!");
        exit(1);
    }

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

    free(tempLeftArray);
    free(tempRightArray);
}

//Array Generator
int randomInt()
{
    return rand() % maxNumber + 1;
}

int* generateArray(int size)
{
    //seed
    srand(time(NULL));

    int* array = (int *)malloc(size * sizeof(int));
    if(array == NULL){
        printf("Memory not allocated!");
        exit(1);
    }
    else{
        for(int i = 0; i < size; i++)
            array[i] = randomInt();
    }

    return array;
}
