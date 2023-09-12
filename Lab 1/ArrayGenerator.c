#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxNumber = 10;

int randomInt()
{
    return rand() % maxNumber + 1;
}

int* generateArray(int size)
{
    //seed
    srand(time(NULL));

    int* array = (int *)malloc(size * sizeof(int));
    if(array == NULL)
        printf("Memory not allocated!");
    else{
        for(int i = 0; i < size; i++)
            array[i] = randomInt();
    }

    return array;
}

int main()
{
    int* arr;

    arr = generateArray(10);

    for(int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
}
