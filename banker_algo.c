#include <stdio.h>
#include <stdlib.h>
int main() {
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resources

    // Allocation matrix
    int allocation[5][3] = { { 0, 1, 0 },   // P0
                             { 2, 0, 0 },   // P1
                             { 3, 0, 2 },   // P2
                             { 2, 1, 1 },   // P3
                             { 0, 0, 2 } }; // P4

    // Maximum matrix
    int max[5][3] = { { 7, 5, 3 },          // P0
                      { 3, 2, 2 },          // P1
                      { 9, 0, 2 },          // P2
                      { 2, 2, 2 },          // P3
                      { 4, 3, 3 } };        // P4

    // Available resources
    int available[3] = { 3, 3, 2 };

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    printf("Process\t\tResource A\tResource B\tResource C\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t", i);
        for (j = 0; j < m; j++) {
            printf("%d\t\t", need[i][j]);
        }
        printf("\n");
    }

    // Banker's Algorithm
    int y = 0;
    printf("Step\tProcess\t\tAvailable\tAllocation\tNeed\t\tAvailable After\n");
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    // Print available before
                    printf("%d\tP%d\t\t", ind + 1, i);
                    for (y = 0; y < m; y++) {
                        printf("%d ", available[y]);
                    }

                    printf("\t\t");
                    // Print allocation
                    for (y = 0; y < m; y++) {
                        printf("%d ", allocation[i][y]);
                    }

                    printf("\t\t");
                    // Print need
                    for (y = 0; y < m; y++) {
                        printf("%d ", need[i][y]);
                    }

                    printf("\t\t");

                    // Update available resources after allocation
                    for (y = 0; y < m; y++) {
                        available[y] += allocation[i][y];
                    }

                    // Print available after
                    for (y = 0; y < m; y++) {
                        printf("%d ", available[y]);
                    }

                    printf("\n");
                    ans[ind++] = i;
                    f[i] = 1;
                }
            }
        }
    }
    printf("\nThe safe sequence is: \n");
    for (i = 0; i < n - 1; i++) {
        printf(" P%d ->", ans[i]);
    }
    printf(" P%d\n", ans[n - 1]);
    return 0;
}