#include <stdio.h>
#include <limits.h>

#define MAX 100  // Maximum number of vertices

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra's algorithm for a graph represented using an adjacency matrix
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[V];     // Output array. dist[i] will hold the shortest distance from src to i
    int visited[V];  // visited[i] will be 1 if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited, V);

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it is not visited, there is an edge from u to v,
            // and the total weight of path from src to v through u is smaller than current dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

// Main function
int main() {
    int V;  // Number of vertices
    int graph[MAX][MAX];
    int source;

    // Input number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Input adjacency matrix representation of the graph
    printf("Enter the adjacency matrix (enter 0 if there is no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input the source vertex
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    // Run Dijkstra's algorithm
    dijkstra(graph, V, source);

    return 0;
}
