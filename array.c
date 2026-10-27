#include <stdio.h>

void arraybuilder(int x[5][2]) {   
    int i, j;
    printf("Enter elements for the matrix (5x2):\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            scanf("%d", &x[i][j]);
        }
    }
}

int addition(int a[5][2], int b[5][2]) {
    int i, j, m[5][2];
    

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            m[i][j] = a[i][j] + b[i][j];
        }
    } 
    printf("\nResulting Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d\t", m[i][j]);
        }
        printf("\n"); 
    }

    return 0; 
}
int multiplication(int a[5][2], int b[5][2]) {
    int i, j;
    int x[5][2] = {};
    

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            x[i][j] += a[i][j] * b[i][j];
        }
    } 
    printf("\nResulting Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d\t", x[i][j]);
        }
        printf("\n"); 
    }
    return 0; 
}
int main() {
    int a[5][2], b[5][2];
    arraybuilder(a);
    arraybuilder(b);
    addition(a, b);
    multiplication(a,b);
    return 0;
}