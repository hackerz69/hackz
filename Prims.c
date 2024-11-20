#include <stdio.h>
#include <limits.h>
#define MAX 100
#define INF INT_MAX
int graph[MAX][MAX]; // Adjacency matrix for the graph
// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[], int n) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}
// Prim's Algorithm to find MST
void primMST(int n) {
    int parent[MAX];   // Array to store constructed MST
    int key[MAX];      // Key values used to pick minimum weight edge
    int mstSet[MAX];   // To represent the set of vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }
    // Start from the first vertex
    key[0] = 0;       // Start with the first vertex (arbitrary)
    parent[0] = -1;   // First node is always the root of the MST
    // MST will have n vertices
    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;  // Add the picked vertex to the MST set
        // Update key and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }
    // Print the MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}
int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    printf("Minimum Spanning Tree using Prim's Algorithm:\n");
    primMST(n);
    return 0;
}
