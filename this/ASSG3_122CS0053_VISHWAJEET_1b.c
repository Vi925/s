// 1. (b) (b) Write a program to find FOLLOW
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 10

char p[MAX_PRODUCTIONS][MAX_LENGTH], fol[MAX_PRODUCTIONS][MAX_LENGTH];
int n, m;

void follow(int, int);
void first(int, int);

int main() {
    int i;
    
    printf("Enter number of productions: ");
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++) {
        printf("Enter production no %d: ", i);
        scanf("%s", p[i]);
    }
    
    for (i = 1; i <= n; i++) {
        m = 0;
        follow(i, 0);
    }
    
    for (i = 1; i <= n; i++) {
        printf("\nFollow(%c): %s", p[i][0], fol[i]);
    }
    printf("\n");
    
    return 0;
}

// Function to find FOLLOW set
void follow(int x, int y) {
    int u, v;
    
    if (p[x][y] == p[1][0]) {
        fol[x][m++] = '$';
    }
    
    for (u = 1; u <= n; u++) {
        for (v = 3; v < strlen(p[u]); v++) {
            if (p[u][v] == p[x][y]) {
                if (islower(p[u][v + 1])) {
                    fol[x][m++] = p[u][v + 1];
                } else if (isupper(p[u][v + 1])) {
                    first(u, v + 1);
                } else {
                    follow(u, 0);
                }
            }
        }
    }
}

// Function to find FIRST set
void first(int x, int y) {
    int u;
    
    for (u = 1; u <= n; u++) {
        if (p[u][0] == p[x][y]) {
            if (islower(p[u][3])) {
                fol[x][m++] = p[u][3];
            } else {
                first(u, 3);
            }
        }
    }
}
