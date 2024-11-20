#include <stdio.h>
#include <stdlib.h>
#define MAX 100  // Define maximum number of vertices
int adj[MAX][MAX];  // Adjacency matrix
int visited[MAX];   // Visited array
// Function to add an edge to the graph
void addEdge(int v, int w) {
    adj[v][w] = 1;
    adj[w][v] = 1;  // For undirected graph
}
// Breadth First Search (BFS) implementation
void BFS(int startVertex, int n) {
    int queue[MAX], front = -1, rear = -1;
    visited[startVertex] = 1;
    queue[++rear] = startVertex;
    while (front != rear) {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);
        for (int i = 0; i < n; i++) {
            if (adj[currentVertex][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
            }
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
    printf("Enter the start vertex for BFS: ");
    scanf("%d", &startVertex);
    printf("BFS traversal starting from vertex %d:\n", startVertex);
    resetVisited(n);  // Reset visited array before BFS
    BFS(startVertex, n);
    return 0;
}
