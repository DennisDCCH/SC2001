#include <stdio.h>
#include <stdlib.h>

int randomInt(int max)
{
    return rand() % max + 1;
}

int* generateArray(int seed, int max, int size)
{
    //seed
    srand(seed);

    int* array = (int *)malloc(size * sizeof(int));
    if(array == NULL)
        printf("Memory not allocated!");
    else{
        for(int i = 0; i < size; i++)
            array[i] = randomInt(max);
    }

    return array;
}

int main()
{
    int* arr;

    arr = generateArray(6, 10, 10);

    for(int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
}
