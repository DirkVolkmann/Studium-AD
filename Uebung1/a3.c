#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    int m;
    int n;
    int **data;
} Matrix;

Matrix Init(int m, int n) {
    Matrix M;

    M.m = m;
    M.n = n;

    M.data = malloc( m * sizeof(int) );;
    for (int i = 0; i < m; i++) {
        M.data[i] = malloc( n * sizeof(int) );
        for (int j = 0; j < n; j++) {
            M.data[i][j] = 0;
        }
    }

    return M;
}

void Print(Matrix *M) {
    for (int m = 0; m < M->m; m++) {
        for (int n = 0; n < M->n; n++) {
            printf("%d ", M->data[m][n]);
        }
        printf("\n");
    }
}

void Input(Matrix *M) {
    for (int m = 0; m < M->m; m++) {
        printf("Eingabe Zeile %d\n", m+1);
        for (int n = 0; n < M->n; n++) {
            printf("Zahl %d: ", n+1);
            scanf("%d", &M->data[m][n]);
        }
    }
}

Matrix Add(Matrix *A, Matrix *B) {
    if (A->m != B->m || A->n != B->n) {
        return Init(0, 0);
    }

    Matrix M = Init(A->m, A->n);

    for (int m = 0; m < A->m; m++) {
        for (int n = 0; n < A->n; n++) {
            M.data[m][n] = A->data[m][n] + B->data[m][n];
        }
    }

    return M;
}

Matrix Mult(Matrix *A, Matrix *B) {
    if (A->m != B->m || A->n != B->n) {
        return Init(0, 0);
    }

    Matrix M = Init(A->m, A->n);

    for (int m = 0; m < A->m; m++) {
        for (int n = 0; n < A->n; n++) {
            M.data[m][n] = A->data[m][n] * B->data[m][n];
        }
    }

    return M;
}

int main() {
    printf("Matrix A:\n");
    Matrix A = Init(2, 2);
    Input(&A);
    
    printf("Matrix B:\n");
    Matrix B = Init(2, 2);
    Input(&B);

    printf("A + B:\n");
    Matrix M = Add(&A, &B);
    Print(&M);

    printf("A * B:\n");
    M = Mult(&A, &B);
    Print(&M);

    return 0;
}