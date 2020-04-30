#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix {
    int m;
    int n;
    int **data;
} Matrix;

Matrix Init(int m, int n) {
    Matrix M;

    M.m = m;
    M.n = n;

    M.data = malloc( m * n * sizeof(int) );
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
        //printf("Eingabe Zeile %d\n", m+1);
        for (int n = 0; n < M->n; n++) {
            //printf("Zahl %d: ", n+1);
            //scanf("%d", &M->data[m][n]);
            
            // Zufallszahl für Tests verwenden
            M->data[m][n] = rand();
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

void PrintTime(clock_t takte, int size) {
    int ms = (double)takte/CLOCKS_PER_SEC*1000;

    printf("Takte: %ld\n", takte);
    printf("Zeit: %d ms\n", ms);
    printf("Pro Minute: %f\n", (double)60000 / ms);
}

int main() {
    // Zufallszahl-Generator initialisieren (für Tests)
    srand(time(NULL));
    clock_t takte;

    int matrix_m = 10000;
    int matrix_n = matrix_m;
    long gesamt = matrix_m * matrix_n;

    //printf("Matrix A:\n");
    Matrix A = Init(matrix_m, matrix_n);
    Input(&A);
    
    //printf("Matrix B:\n");
    
    Matrix B = Init(matrix_m, matrix_n);
    Input(&B);

    printf("A + B:\n");
    takte = clock();
    Matrix M = Add(&A, &B);
    takte = clock() - takte;
    //Print(&M);
    PrintTime(takte, matrix_m);

    printf("\n");

    printf("A * B:\n");
    takte = clock();
    M = Mult(&A, &B);
    takte = clock() - takte;
    //Print(&M);
    PrintTime(takte, matrix_m);

    printf("\n");

    return 0;
}