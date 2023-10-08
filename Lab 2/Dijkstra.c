#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 10000
#define MAX_WEIGHT 10

union GraphForm{
    int **matrix;
};

typedef struct _graph{
    int V;
    int E;
    union GraphForm adj;
}Graph;

void dijkstra(Graph *g, int source);
Graph generateAdjMatrix(int vertices);
void printGraphMatrix(Graph g);

int main()
{
    srand(time(NULL));
    clock_t start_time, end_time;

    Graph g;
    double results[5];
    double sum, average;

    /*
    //generating only 1 graph and checking the correctness of implementation
    g = generateAdjMatrix(10);
    printGraphMatrix(g);
    dijkstra(&g, 1);
    */

    //Generating empirical results for analysis
    FILE * fpointer = fopen("lab2_result_1.csv", "a");
    fprintf(fpointer, "Vertices (V), Time 1, Time 2, Time 3, Time 4, Time 5, Average Time\n");

    for(int vertices = 100; vertices <= MAX_VERTICES; vertices += 100){
        printf("%d\n", vertices);
        sum = 0;

        for(int i = 0; i < 5; i++){
            g = generateAdjMatrix(vertices);

            start_time = clock();
            dijkstra(&g, 1);
            end_time = clock();

            results[i] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            // Clean up the memory for the adjacency matrix
            for (int i = 0; i < g.V; i++) {
                free(g.adj.matrix[i]);
            }
            free(g.adj.matrix);
        }

        for(int i = 0; i < 5; i++){
            sum += results[i];
        }
        average = sum / 5;
        fprintf(fpointer, "%d, %f, %f, %f, %f, %f, %f\n", vertices, results[0], results[1], results[2], results[3], results[4], average);
    }

    fclose(fpointer);

}

void dijkstra(Graph *g, int source)
{
    int *shortestDist = malloc(g->V * sizeof(int));
    int *visited = malloc(g->V * sizeof(int));
    int *predecessor = malloc(g->V * sizeof(int));

    //set shortestDistance from source as -1 and visited to 0
    for(int i = 0; i < g->V; i++){
        visited[i] = 0;
        shortestDist[i] = -1;
        predecessor[i] = -1;
    }

    //set source vertex as visited
    visited[source - 1] = 0;

    //set distance from source to source as 0
    shortestDist[source - 1] = 0;

    //set predecessor of source to itself
    predecessor[source - 1] = source;

    //Set starting vertex
    int current = source - 1;
    for(int i = 1; i < g->V; i++){
        for(int j = 0; j < g->V; j++){
            /*
            Conditions to check for before updating distance

            1. The destination vertex have not been visited before
            2. There is an edge between currentVertex and destination vertex
            3. The cost of source to currentVertex + currentVertex to destinationVertex
               is less than source to destination vertex
            4. Update if first time going to the destination vertex
            */

            //Condition 1
            if(visited[j] == 0){
                //Condition 2
                if(g->adj.matrix[current][j] != 0){
                    //Condition 3 + 4
                    if(shortestDist[j] == -1 || shortestDist[current] + g->adj.matrix[current][j] < shortestDist[j]){
                        shortestDist[j] = shortestDist[current] + g->adj.matrix[current][j];
                        predecessor[j] = current + 1;
                    }
                }
            }
        }

        /* Find next vertex to continue with
        Conditions to check to pick new vertex to continue with
        1. This new vertex must have an edge with a previously visited vertex
        2. This new vertex must not be visited before
        3. The new vertex must have the shortestDistance from source
        4. Update smallest distance for the first time
        */

        int smallestDist = -1;
        for(int j = 0; j < g->V; j++){
            if(shortestDist[j] != -1){
                if(visited[j] == 0){
                    if(shortestDist[j] < smallestDist || smallestDist == -1){
                        current = j;
                        smallestDist = shortestDist[j];
                    }
                }
            }
        }

        //Set new vertex as visited
        visited[current] = 1;
    }


    //Print the shortest distance from source to all vertex
    printf("Source: %d\n", source);
    printf("Vertex | Cost | Predecessor\n");
    for(int i = 0; i < g->V; i++){
        printf("   %d   |  %d   |    %d\n", i + 1, shortestDist[i], predecessor[i]);
    }

}

Graph generateAdjMatrix(int vertices)
{
    Graph g;
    g.V = vertices;
    g.E = 0;

    //Initialize adjacency matrix
    g.adj.matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        g.adj.matrix[i] = (int*)malloc(vertices * sizeof(int));
    }

    //Fill in the contents of the adjacency matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                g.adj.matrix[i][j] = 0;
            else{
                g.adj.matrix[i][j] = rand() % (MAX_WEIGHT + 1);
                g.E++;
            }
        }
    }

    return g;
}

void printGraphMatrix(Graph g)
{
    for(int i = 0; i < g.V; i++){
        for(int j = 0; j < g.V; j++)
            printf("%d\t", g.adj.matrix[i][j]);
        printf("\n");
    }

}
