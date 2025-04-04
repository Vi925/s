// 1. (a) Write a program to find FIRST
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void first(int, int);
void format();

int n, i, m;
char a[10][10], ans[10][10];

// Main program
int main() {
    int j;
    printf("Enter no of productions (epsilon (@)): ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("Enter the production no %d: ", i);
        scanf("%s", a[i]);
    }

    // Calculate FIRST for each production
    for (i = 1; i <= n; i++) {
        m = 0;
        first(i, 0);
    }

    // Display productions
    printf("\nThe productions are:");
    for (i = 1; i <= n; i++) {
        printf("\n%s", a[i]);
    }
    printf("\n-------------------------------");

    // Format the result
    format();

    // Display FIRST sets
    for (i = 1; i <= n; i++) {
        if (a[i][0] != ' ') {
            printf("\nfirst(%c) ", a[i][0]);
            for (j = 0; j < m; j++) {
                if (ans[i][j] != ' ') {
                    printf(" %c", ans[i][j]);
                }
            }
        }
    }
    printf("\n");
    return 0;
}

// Recursive function to compute FIRST set
void first(int x, int y) {
    int j, l = 3;
    for (j = 1; j <= n; j++) {
        if (a[j][0] == a[x][y]) {
            if (!isupper(a[j][l]) && a[j][l] != '@') {
                ans[i][m++] = a[j][l];
            } else if (a[j][l] == '@') {
                if (a[x][y + 1] != '\0' && y != 0) {
                    if (isupper(a[x][y + 1])) {
                        first(x, y + 1);
                    } else {
                        ans[i][m++] = a[x][y + 1];
                    }
                } else {
                    ans[i][m++] = '@';
                }
            } else {
                first(j, l);
            }
        }
    }
}

// Function to format the result by removing duplicates
void format() {
    int j, k;
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (a[i][0] == a[j][0]) {
                a[j][0] = ' ';
            }
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 0; j < m; j++) {
            for (k = j + 1; k < m; k++) {
                if (ans[i][j] == ans[i][k]) {
                    ans[i][k] = ' ';
                }
            }
        }
    }
}