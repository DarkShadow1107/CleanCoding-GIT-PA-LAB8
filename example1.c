#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int numVertices;
    NODE **adjList;
    int *visited;
} GRAPH;

NODE *createNode(int data) {
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(GRAPH *graph, int src, int dest) {
    // Add edge from src to dest
    NODE *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

GRAPH *createGraph(int numVertices) {
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->numVertices = numVertices;
    graph->adjList = malloc(numVertices * sizeof(NODE *));
    graph->visited = malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void dfs(GRAPH *graph, int startVertex) {
    graph->visited[startVertex] = 1;
    printf("Visited %d\n", startVertex);

    NODE *adjList = graph->adjList[startVertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->data;
        if (graph->visited[connectedVertex] == 0) {
            dfs(graph, connectedVertex);
        }
        adjList = adjList->next;
    }
}

void freeGraph(GRAPH *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        NODE *node = graph->adjList[i];
        while (node) {
            NODE *tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(graph->adjList);
    free(graph->visited);
    free(graph);
}

int main() {
    int numVertices = 5;
    GRAPH *graph = createGraph(numVertices);

    // Adding predefined edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Perform DFS starting from vertex 0
    printf("Starting DFS from vertex 0:\n");
    dfs(graph, 0);

    // Free all allocated memory
    freeGraph(graph);

    return 0;
}
