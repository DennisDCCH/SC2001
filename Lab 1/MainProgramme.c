#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int keyComparison = 0;
int maxNumber = 1000;
int trial = 1;

void hybridSort(int arr[], int left, int right, int threshold);
void insertionSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
int randomInt();
int* generateArray(int size);


int main()
{
    int arrSize[] = {1000, 2000, 4000, 8000, 10000, 16000, 32000, 64000, 100000, 128000, 256000, 512000, 1000000, 1024000, 2048000, 4096000, 8192000, 10000000};
    int temp1 = sizeof(arrSize) / sizeof(int);
    int threshold[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int temp2 = sizeof(threshold) / sizeof(int);
    int* arr;
    int arraySize;

    FILE * fpointer = fopen("results_c2_1.csv", "w");
    fprintf(fpointer, "Array Size,Threshold[S],Key Comparison\n");

    for(int i = 0; i < temp1; i++){
        for(int j = 0; j < temp2; j++){
            arraySize = arrSize[i];
            arr = generateArray(arraySize);
            hybridSort(arr, 0, arraySize - 1, threshold[j]);
            printf("Array Size: %d\nThreshold: %d\nKey Comparison: %d\n\n", arraySize, threshold[j], keyComparison);
            fprintf(fpointer, "%d,%d,%d\n", arraySize, threshold[j], keyComparison);
            keyComparison = 0;
            free(arr);
        }
    }

    fclose(fpointer);

    return 0;
}

//Merge insertion Sort Algorithm
void hybridSort(int arr[], int left, int right, int threshold)
{
    if(right - left > threshold){
        int mid  = (left + right) / 2;

        //recursive
        hybridSort(arr, left, mid, threshold);
        hybridSort(arr, mid + 1, right, threshold);

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
