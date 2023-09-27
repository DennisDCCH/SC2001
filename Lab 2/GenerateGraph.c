#include <stdio.h>
#include <stdlib.h>

#define VERTICES 5
#define MAX_WEIGHT 10

// Types of Graph Representation
enum GraphType
{
    ADJ_MATRIX,
    ADJ_LIST
};

typedef struct _listnode
{
    int vertex;
    int weight;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

Graph generateAdjMatrix(int vertices);
void printGraphMatrix(Graph);
void adjM2adjL(Graph*);
void printGraphList(Graph);

int main()
{
    srand(time(NULL));

    Graph g = generateAdjMatrix(VERTICES);
    printGraphMatrix(g);
    adjM2adjL(&g);
    printGraphList(g);

    return 0;
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

    g.type = ADJ_MATRIX;

    return g;
}

void printGraphMatrix(Graph g)
{
    if(g.type == ADJ_LIST){
        printf("Error");
        return;
    }

    for(int i = 0; i < g.V; i++){
        for(int j = 0; j < g.V; j++)
            printf("%d\t", g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printGraphList(Graph g){
    ListNode* temp;

    if(g.type == ADJ_MATRIX){
        printf("Error");
        return;
    }

    for(int i = 0; i < g.V; i++){
        printf("%d:\t", i+1);
        temp = g.adj.list[i];
        while(temp != NULL){
            printf("%d(%d) -> ",temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void adjM2adjL(Graph *g)
{
    ListNode *temp;
    ListNode **list;

    //Ensure that current graph type is matrix not list
    if(g->type == ADJ_LIST){
        printf("Error");
        return;
    }
    //Ensure that there is vertices in the graph
    if(g->V <= 0){
        printf("Empty graph");
        return;
    }

    //Initialize the adjacency list
    list = (ListNode **)malloc(g->V * sizeof(ListNode*));
    for(int i = 0; i < g->V; i++)
        list[i] = NULL;

    //Fill in contents of adjacency list with the destination from source and the cost to reach destination
    for(int i = 0; i < g->V; i++){
        for(int j = 0; j < g->V; j++){
            if(g->adj.matrix[i][j] != 0){
                if(list[i] == NULL){
                    list[i] = (ListNode *)malloc(sizeof(ListNode));
                    list[i]->vertex = j + 1;
                    list[i]->weight = g->adj.matrix[i][j];
                    list[i]->next = NULL;
                    temp = list[i];
                }
                else{
                    temp->next = (ListNode *)malloc(sizeof(ListNode));
                    temp->next->vertex = j + 1;
                    temp->next->weight = g->adj.matrix[i][j];
                    temp->next->next = NULL;
                    temp = temp->next;
                }
            }
        }
    }

    //Change graph representation form
    g->type = ADJ_LIST;

    //free adjMatrix
    for(int i = 0; i < g->V; i++)
        free(g->adj.matrix[i]);
    free(g->adj.matrix);

    g->adj.list = list;
}
