#include <stdio.h>
#define MAX 100  // Define maximum number of vertices
int adj[MAX][MAX];  // Adjacency matrix
int visited[MAX];   // Visited array
// Function to add an edge to the graph
void addEdge(int v, int w) {
    adj[v][w] = 1;
    adj[w][v] = 1;  // For undirected graph
}
// Depth First Search (DFS) implementation
void DFS(int vertex, int n) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < n; i++) {
        if (adj[vertex][i] == 1 && visited[i] == 0) {
            DFS(i, n);
        }
    }
}
// Reset visited array for reusing
void resetVisited(int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}
int main() {
    int n, e, v1, v2, startVertex;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    printf("Enter the edges (vertex pairs):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &v1, &v2);
        addEdge(v1, v2);
    }
    printf("Enter the start vertex for DFS: ");
    scanf("%d", &startVertex);
    printf("DFS traversal starting from vertex %d:\n", startVertex);
    resetVisited(n);  // Reset visited array before DFS
    DFS(startVertex, n);
    return 0;
}
