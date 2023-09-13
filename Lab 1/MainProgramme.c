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
int* duplicateArray(int* originalArray, int arrSize);

int main()
{
    srand(time(NULL));

    int arrSize[] = {1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000, 1000000, 2500000, 5000000, 7500000, 10000000};
    int temp1 = sizeof(arrSize) / sizeof(int);

    int threshold[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int temp2 = sizeof(threshold) / sizeof(int);

    int* arr, *tempArr;
    int arraySize;
    int results[13][5][19];

    FILE * fpointer = fopen("results_c2_1.csv", "w");
    fprintf(fpointer, "Array Size[N],Threshold[S],Key Comparison 1, Key Comparison 2, Key Comparison 3, Key Comparison 4, Key Comparison 5\n");

    //For different Array Size
    for(int i = 0; i < temp1; i++){
        arraySize = arrSize[i];
        fprintf(fpointer, "%d", arraySize);

        //Do experiment 5 times, calculate average afterwards
        for(int j = 0; j < 5; j++){

            //Make new array every new experiment
            arr = generateArray(arraySize);

            //For different threshold level
            for(int k = 0; k < temp2; k++){

                //Reset key comparison
                keyComparison = 0;

                //Duplicate Array for each threshold
                tempArr = duplicateArray(arr, arraySize);

                //Do merge insertion sort
                hybridSort(tempArr, 0, arraySize -  1, threshold[k]);

                //Store results
                results[i][j][k] = keyComparison;

                free(tempArr);
            }
            printf("%d, %d experiment\n", arraySize, j);
            free(arr);
        }
    }

    //Write to csv file
    for(int i = 0; i < temp1; i++){
        for(int j = 0; j < temp2; j++)
            fprintf(fpointer, "%d,%d,%d,%d,%d,%d,%d\n", arrSize[i], threshold[j], results[i][0][j], results[i][1][j], results[i][2][j], results[i][3][j], results[i][4][j]);
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

    for(int i = 1; i < size; i++){
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

int* duplicateArray(int* originalArray, int arrSize)
{
    int* duplicateArray = (int *)malloc(arrSize * sizeof(int));

    if(duplicateArray == NULL){
        printf("Memory allocation failed");
        return NULL;
    }

    for(int i = 0; i < arrSize; i++)
        duplicateArray[i] = originalArray[i];

    return duplicateArray;
}
