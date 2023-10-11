#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_VERTICES 4000

typedef struct AdjListNode {
    int vertex;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Define structure for the graph
typedef struct Graph {
    int numVertices;
    AdjListNode** adjLists;
} Graph;


AdjListNode* createNode(int vertex, int weight) {
    AdjListNode* newNode = malloc(sizeof(AdjListNode));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(AdjListNode*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

typedef struct MinHeapNode {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct MinHeap {
    int size;       // Number of heap nodes present currently
    int capacity;   // Capacity of min heap
    int *pos;       // This is needed for decreaseKey()
    MinHeapNode **array;
} MinHeap;

MinHeapNode* newMinHeapNode(int vertex, int distance) {
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    newNode->vertex = vertex;
    newNode->distance = distance;
    return newNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->distance < minHeap->array[smallest]->distance) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->distance < minHeap->array[smallest]->distance) {
        smallest = right;
    }

    if (smallest != idx) {
        //Swap positions
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        //Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);


    return root;
}

//int isInMinHeap(MinHeap* minHeap, int vertex) {
//    if (minHeap->pos[vertex] < minHeap->size) {
//        return 1;
//    }
//    return 0;
//}

void decreaseKey(MinHeap* minHeap, int vertex, int distance) {
    int i = minHeap->pos[vertex];
    minHeap->array[i]->distance = distance;

    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }

}


void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void dijkstra(Graph* graph, int src, int *d[], int *pi[]){
    int max = 2147483647;
    int *S[graph->numVertices];
    MinHeapNode * ExtractNode;
    AdjListNode *  currentNode;

    for(int i=0; i<graph->numVertices; i++) {
        d[i] = malloc(sizeof(int));
        pi[i] = malloc(sizeof(int));
        S[i] = malloc(sizeof(int));

        *d[i] = max;
        *pi[i] = -1;
        *S[i] = 0;
    }

    MinHeap * minHeap = createMinHeap(graph->numVertices);
    for(int i=0; i<graph->numVertices; i++){
        MinHeapNode * node = newMinHeapNode(i, *d[i]);
        minHeap->size++;
        minHeap->capacity = graph->numVertices;
        minHeap->array[i] = node;
        minHeap->pos[i] = i;
    }

    *d[src] = 0;
    decreaseKey(minHeap, src, *d[src]);

    while(!isEmpty(minHeap)){
        ExtractNode = extractMin(minHeap);
        *S[ExtractNode->vertex] = 1;

        currentNode = graph->adjLists[ExtractNode->vertex];
        while(currentNode != NULL){
//            if(*S[currentNode->vertex] != 1 && *d[currentNode->vertex] > *d[ExtractNode->vertex] + currentNode->weight){
//                *d[currentNode->vertex] = *d[ExtractNode->vertex] + currentNode->weight;
//                *pi[currentNode->vertex] = ExtractNode->vertex;
//                decreaseKey(minHeap, currentNode->vertex, *d[currentNode->vertex]);
//            }
            if(*S[currentNode->vertex] != 1) {
                int potential_distance = *d[ExtractNode->vertex] == INT_MAX ? INT_MAX : *d[ExtractNode->vertex] + currentNode->weight;
                if(*d[currentNode->vertex] > potential_distance) {
                    *d[currentNode->vertex] = potential_distance;
                    *pi[currentNode->vertex] = ExtractNode->vertex;
                    decreaseKey(minHeap, currentNode->vertex, *d[currentNode->vertex]);
                }
            }

            currentNode = currentNode->next;
        }
    }

}

void addRandomEdges(Graph* graph, int numVertices, int numEdges) {
    int addedEdges = 0;
    int src, dest, weight;

    // Set up a 2D array to keep track of added edges
    int ** addedEdgeMatrix = (int**) malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        addedEdgeMatrix[i] = (int *) malloc(numVertices * sizeof(int));
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            addedEdgeMatrix[i][j] = 0;
        }
    }

    // Seed the random number generator
    srand(time(NULL));

    while (addedEdges < numEdges) {
        src = rand() % numVertices;
        dest = rand() % numVertices;
        weight = rand() % 100 + 1; // Assuming weights between 1 and 100

        if (src != dest && addedEdgeMatrix[src][dest] == 0) {
            addEdge(graph, src, dest, weight);
            addedEdgeMatrix[src][dest] = 1;
            addedEdges++;
        }
    }

    // Free up the addedEdgeMatrix
    for (int i = 0; i < numVertices; i++) {
        free(addedEdgeMatrix[i]);
    }
    free(addedEdgeMatrix);
}

void generateCompleteGraph(Graph *g)
{
    for(int src = 0; src < g->numVertices; src++){
        for(int dest = 0; dest < g->numVertices; dest++){
            if(src != dest){
                int weight = rand() % 100 + 1;
                addEdge(g, src, dest, weight);
            }
        }
    }
}

int main(){
    srand(time(NULL));
    clock_t start_time, end_time;

    Graph* graph;
    double edges;
    double results[5];
    double sum, average, density;

    /*
    // Generating only 1 graph and checking the correctness of implementation
    int vertices = 10;
    Graph* graph = createGraph(vertices);
    addRandomEdges(graph, graph->numVertices, vertices * (vertices - 1));

    int *d[graph->numVertices];
    int *pi[graph->numVertices];

    dijkstra(graph, 0, d, pi);
    printf("Vertex  |  MinDistance  |  Predecessor \n");
    for(int i=0; i < vertices; i++){
        printf("   %d    |       %d       |      %d  \n", i, *d[i],  *pi[i]);
    }
    */

    /*
    FILE * fpointer = fopen("lab2_result_4.csv", "w");
    fprintf(fpointer, "Vertices (V),Edges (E),Time 1,Time 2,Time 3,Time 4,Time 5,Average Time\n");

    for(int vertices = 100; vertices <= MAX_VERTICES; vertices += 100){
        printf("%d\n", vertices);
        sum = 0;

        density = 0.25
        edges = (vertices * (vertices - 1)) * density;
        for(int i = 0; i < 5; i++){
            graph = createGraph(vertices);
            generateCompleteGraph(graph);
            //addRandomEdges(graph, graph->numVertices, edges);
            int *d[graph->numVertices];
            int *pi[graph->numVertices];

            start_time = clock();
            dijkstra(graph, 0, d, pi);
            end_time = clock();

            results[i] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            for(int j = 0; j < vertices; j++){
                free(graph->adjLists[j]);
            }
            free(graph->adjLists);
        }

        for(int i = 0; i < 5; i++){
            sum += results[i];
        }
        average = sum / 5;

        fprintf(fpointer, "%d, %d, %f, %f, %f, %f, %f, %f\n", vertices, edges, results[0], results[1], results[2], results[3], results[4], average);
    }

    fclose(fpointer);
    */
    FILE * fpointer = fopen("lab2_result_4.csv", "w");
    fprintf(fpointer, "Vertices (V),Edges (E),Time 1,Time 2,Time 3,Time 4,Time 5,Average Time\n");

    for(int edges = (2000 * 1999) / 4; edges < (2000 * 1999); edges += 20000){
        printf("%d\n", edges);
        sum = 0;

        for(int i = 0; i < 5; i++){
            graph = createGraph(2000);
            addRandomEdges(graph, graph->numVertices, edges);
            int *d[graph->numVertices];
            int *pi[graph->numVertices];

            start_time = clock();
            dijkstra(graph, 0, d, pi);
            end_time = clock();

            results[i] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            for(int j = 0; j < 2000; j++){
                free(graph->adjLists[j]);
            }
            free(graph->adjLists);
        }

        for(int i = 0; i < 5; i++){
            sum += results[i];
        }
        average = sum / 5;

        fprintf(fpointer, "%d, %d, %f, %f, %f, %f, %f, %f\n", 2000, edges, results[0], results[1], results[2], results[3], results[4], average);
    }

    fclose(fpointer);
    return 0;
}
