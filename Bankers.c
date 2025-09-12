#include <stdio.h>
#include <stdlib.h>

int alloc[10][10], max[10][10], need[10][10], i, j, n, m;

void read(int a[10][10]) {
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}
void calculate() {
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}
void banker() {
    int avail[10], finished[10], flag, k, s, safeseq[10], index = 0;

    for (i = 0; i < n; i++) {
        finished[i] = 0;
    }
    printf("\nEnter the Available number of Resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    printf("\nProcess\t   Allocation\t   Max\t\t   Need\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t   ", i + 1);
        for (j = 0; j < m; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\t   ");
        for (j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t   ");
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    for (s = 0; s < n; s++) {
        for (i = 0; i < n; i++) {
            flag = 0;
            if (finished[i] == 0) {
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    finished[i] = 1;
                    safeseq[index] = i;
                    index++;
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                }
            }
        }
    }
    flag = 1;
    for (i = 0; i < n; i++) {
        if (finished[i] == 0) {
            printf("\nThe system is NOT in a safe state.\n");
            flag = 0;
            break;
        }
    }
    if (flag == 1) {
        printf("\nThe system is in a SAFE state.\n");
        printf("Safe sequence is: ");
        for (i = 0; i < n; i++) {
            printf("P[%d] ", safeseq[i] + 1);
        }
        printf("\n");
    }
}
int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);
    printf("Enter the Max Matrix (%d x %d):\n", n, m);
    read(max);
    printf("Enter the Allocation Matrix (%d x %d):\n", n, m);
    read(alloc);
    calculate();
    banker();
    return 0;
}
