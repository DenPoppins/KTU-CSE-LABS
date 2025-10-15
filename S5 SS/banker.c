#include <stdio.h>
int main() {
    int n, m, i, j, k;
   
    printf("Enter the number of processes: ");
    scanf("%d", &n);
   
    printf("Enter the number of resources: ");
    scanf("%d", &m);
   
    int alloc[n][m], max[n][m], avail[m];
   
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter the Maximum need Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    int finish[n], safeSeq[n];
   
    for (i = 0; i < n; i++)
        finish[i] = 0;

    int need[n][m];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
printf("THE NEED MATRIX:\n");
for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
        printf("%d ", need[i][j]);
    }
    printf("\n");
}

    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                   
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state! Deadlock detected.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

return 0;
}