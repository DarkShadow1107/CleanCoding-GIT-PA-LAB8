#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    int* visited;
    Node** adjacencyList;
} Graph;

// Function Prototypes
Node* createNode(int);
Graph* createGraph(int);
void addEdge(Graph*, int, int);
void DFS(Graph*, int);
void BFS(Graph*, int);
void freeGraph(Graph*);
void printGraph(Graph*);

Node* createNode(int vertex) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->numVertices = vertices;
    graph->adjacencyList = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    if (!graph->adjacencyList || !graph->visited) {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Helper functions for queue operations
int is_empty(Node* head) {
    return head == NULL;
}
void enqueue(Node** head, int value) {
    Node* new_node = createNode(value);
    if (!*head) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node** head) {
    if (is_empty(*head)) {
        return -1;
    }
    Node* temp = *head;
    *head = (*head)->next;
    int result = temp->vertex;
    free(temp);
    return result;
}

void DFS(Graph* graph, int startVertex) {
    Node* adjacencyList = graph->adjacencyList[startVertex];
    Node* temp = adjacencyList;
    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex) {
    Node* queue = NULL;
    int currentVertex;
    enqueue(&queue, startVertex);
    graph->visited[startVertex] = 1;

    while (!is_empty(queue)) {
        currentVertex = dequeue(&queue);
        printf("%d ", currentVertex);
        Node* temp = graph->adjacencyList[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjacencyList[i];
        while (temp) {
            Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph->adjacencyList);
    free(graph->visited);
    free(graph);
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjacencyList[v];
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Graph* graph = createGraph(6); // Example graph with 6 vertices

    // Manually adding edges for demonstration
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("DFS Starting from Vertex 0:\n");
    DFS(graph, 0);

    for (int i = 0; i < graph->numVertices; i++) { // Reset visited for BFS
        graph->visited[i] = 0;
    }

    printf("\nBFS Starting from Vertex 0:\n");
    BFS(graph, 0);
    printf("\n");

    freeGraph(graph);
    return 0;
}
