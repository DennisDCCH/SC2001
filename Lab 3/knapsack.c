#include <stdio.h>
#include <stdlib.h>

int knapsack(int noItems, int weight[], int profit[], int maxCapacity)
{
    int table[noItems + 1][maxCapacity + 1];

    for(int i = 0; i < noItems + 1;i++){
        for(int j = 0; j < maxCapacity + 1; j++){
            if(i == 0 || j == 0)
                table[i][j] = 0;
            else{
                int temp = j - weight[i - 1];
                if(temp < 0){
                    table[i][j] = table[i - 1][j];
                }
                else{
                    if(table[i - 1][j] > table[i - 1][temp] + profit[i - 1])
                        table[i][j] = table[i - 1][j];
                    else
                        table[i][j] = table[i - 1][temp] + profit[i - 1];
                }
            }
        }
    }

    for(int i = 0; i < noItems + 1; i++){
        for(int j = 0; j < maxCapacity + 1; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return table[noItems + 1][maxCapacity + 1];
}

int main()
{
    int weight[] = {2, 1, 3, 2};
    int profit[] = {12, 10, 20, 15};
    int noItems = sizeof(weight) / sizeof(weight[0]);
    int maxCapacity = 5;

    knapsack(noItems, weight, profit, maxCapacity);

    int weight1[] = {4, 6, 8};
    int profit1[] = {7, 6, 9};
    int noItems1 = sizeof(weight) / sizeof(weight[0]);
    int maxCapacity1 = 14;

    knapsack(noItems1, weight1, profit1, maxCapacity1);

    int weight2[] = {5, 6, 8};
    int profit2[] = {7, 6, 9};
    int noItems2 = sizeof(weight) / sizeof(weight[0]);
    int maxCapacity2 = 14;

    knapsack(noItems2, weight2, profit2, maxCapacity2);
}
