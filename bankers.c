#include <stdio.h>
#include <string.h>

#define MAX_P 10
#define MAX_R 10

int n, m;
int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
int avail[MAX_R], finish[MAX_P], safe[MAX_P];

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) { buf[0] = '\0'; return; }
    buf[strcspn(buf, "\r\n")] = '\0';
}

void pauseEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

void calcNeed() {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

void showMatrix(const char *title, int mat[MAX_P][MAX_R]) {
    int i, j;
    printf("\n--- %s ---\n", title);
    printf("     ");
    for (j = 0; j < m; j++) printf("R%d ", j);
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("P%d  ", i);
        for (j = 0; j < m; j++) printf("%d  ", mat[i][j]);
        printf("\n");
    }
}

void showAvailable() {
    int j;
    printf("\n--- Available Resources ---\n");
    for (j = 0; j < m; j++) printf("R%d: %d\n", j, avail[j]);
}

void loadDefault() {
    n = 5; m = 4;
    int a[5][4] = {{0,1,0,0},{2,0,0,1},{3,0,1,0},{2,1,1,0},{0,0,2,1}};
    int mx[5][4] = {{0,3,0,2},{3,2,2,1},{3,0,2,2},{4,2,2,0},{0,0,3,2}};
    int av[4] = {2,3,1,3};
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            alloc[i][j] = a[i][j];
            max[i][j] = mx[i][j];
        }
        finish[i] = 0;
    }
    for (j = 0; j < m; j++) avail[j] = av[j];
    calcNeed();
}

void bankers() {
    int work[MAX_R], i, j, k, count = 0, found;
    for (j = 0; j < m; j++) work[j] = avail[j];
    for (i = 0; i < n; i++) finish[i] = 0;
    while (count < n) {
        found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j]) break;
                if (j == m) {
                    for (k = 0; k < m; k++) work[k] += alloc[i][k];
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) break;
    }
    printf("\n--- Banker's Safety Check ---\n");
    if (count < n) {
        printf("System is NOT in a safe state.\n");
    } else {
        printf("System is in a SAFE state.\nSafe sequence: ");
        for (i = 0; i < n; i++) printf("P%d ", safe[i]);
        printf("\n");
    }
    pauseEnter();
}

int main() {
    char ch[16], tmp[16];
    int i, j;
    loadDefault();
    printf("Banker's Algorithm - Warehouse Deadlock Avoidance\n");
    printf("Press Enter to continue...");
    readLine(tmp, sizeof(tmp));
    while (1) {
        printf("\n====== Main Menu ======\n");
        printf("1. Show Allocation Matrix\n2. Show Maximum Matrix\n");
        printf("3. Show Need Matrix\n4. Show Available Resources\n");
        printf("5. Run Banker's Safety Check\n0. Exit\n");
        printf("Enter your choice: ");
        readLine(ch, sizeof(ch));
        if (strcmp(ch, "0") == 0) { printf("Exiting...\n"); break; }
        if (strcmp(ch, "1") == 0) showMatrix("Allocation Matrix", alloc);
        else if (strcmp(ch, "2") == 0) showMatrix("Maximum Matrix", max);
        else if (strcmp(ch, "3") == 0) showMatrix("Need Matrix", need);
        else if (strcmp(ch, "4") == 0) showAvailable();
        else if (strcmp(ch, "5") == 0) bankers();
        else printf("Invalid choice (0-5).\n");
        pauseEnter();
    }
    return 0;
}
