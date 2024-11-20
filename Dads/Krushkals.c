#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge edge[MAX];
};

// A structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// Function prototypes for union-find
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);

// Function to compare two edges for sorting by their weights
int compare(const void *a, const void *b) {
    struct Edge *a1 = (struct Edge *)a;
    struct Edge *b1 = (struct Edge *)b;
    return a1->weight > b1->weight;
}

// Kruskal's Algorithm
void KruskalMST(struct Graph *graph) {
    int V = graph->V;
    struct Edge result[MAX];  // This will store the resultant MST
    int e = 0;  // Index for result[]
    int i = 0;  // Index for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    // Allocate memory for creating V subsets
    struct subset *subsets = (struct subset *)malloc(V * sizeof(struct subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle, include it in the result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the MST
    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d \n", result[i].src, result[i].dest, result[i].weight);
    }

    free(subsets);
}

// Find the subset of an element i (uses path compression)
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two subsets x and y (uses union by rank)
void Union(struct subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int main() {
    int V, E;
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    graph->V = V;
    graph->E = E;

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    printf("Minimum Spanning Tree using Kruskal's Algorithm:\n");
    KruskalMST(graph);

    free(graph);
    return 0;
}
