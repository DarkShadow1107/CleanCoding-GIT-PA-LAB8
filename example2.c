#include <stdio.h>
#include <stdlib.h>

// Define the node structure for the adjacency list
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

// Define the graph structure
typedef struct Graph {
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GPH;

// Function to create a new node
NODE *create_node(int v) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Function to create a graph
GPH *create_graph(int vertices) {
    GPH *graph = (GPH *)malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = (NODE **)malloc(vertices * sizeof(NODE *));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to the graph (undirected)
void add_edge(GPH *graph, int src, int dest) {
    // Add edge from src to dest
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    // Add edge from dest to src (since the graph is undirected)
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// DFS function
void DFS(GPH *graph, int vertex) {
    NODE *adj_list = graph->adjacency_lists[vertex];
    NODE *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Function to check if queue is empty
int is_empty(NODE *queue) {
    return queue == NULL;
}

// Enqueue function
void enqueue(NODE **queue, int value) {
    NODE *new_node = create_node(value);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Dequeue function
int dequeue(NODE **queue) {
    if (is_empty(*queue)) {
        return -1; // Return -1 if the queue is empty
    }
    NODE *temp = *queue;
    int result = temp->data;
    *queue = temp->next;
    free(temp);
    return result;
}

// BFS function
void BFS(GPH *graph, int start) {
    NODE *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges;
    printf("How many vertices does the graph have? ");
    scanf("%d", &nr_of_vertices);

    printf("How many edges does the graph have? ");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);

    printf("Add %d edges (format: src dest): \n", nr_of_edges);
    for (int i = 0; i < nr_of_edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    int starting_vertex;
    printf("Starting vertex for DFS? ");
    scanf("%d", &starting_vertex);
    printf("DFS Traversal: ");
    DFS(graph, starting_vertex);
    printf("\n");

    // Reset visited array for BFS
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }

    printf("Starting vertex for BFS? ");
    scanf("%d", &starting_vertex);
    printf("BFS Traversal: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
