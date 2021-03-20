#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>

#define RANDOM_FILL_MAX 100

class Matrix {
    private:
        std::vector<int> _data;
        unsigned int _m, _n;
    public:
        Matrix(unsigned int m, unsigned int n);
        void set_value(unsigned int m, unsigned int n, int v);
        int get_value(unsigned int m, unsigned int n);
        unsigned int lines();
        unsigned int columns();
        void init();
        void print();
        void input();
        void random_fill();
};

void Matrix::set_value(unsigned int m, unsigned int n, int v) {
    _data[m*_n+n] = v;
}

int Matrix::get_value(unsigned int m, unsigned int n) {
    return _data[m*_n+n];
}

unsigned int Matrix::lines() {
    return _m;
}

unsigned int Matrix::columns() {
    return _n;
}

Matrix::Matrix(unsigned int m, unsigned int n) {
    _m = m;
    _n = n;
    _data.resize(_m*_n);
}

void Matrix::init() {
    std::fill(_data.begin(), _data.end(), 0);
}

void Matrix::print() {
    for (unsigned int i = 0; i < _m; i++) {
        for (unsigned int j = 0; j < _n; j++) {
            std::cout << std::setw(3) << get_value(i, j) << " ";
        }
        printf("\n");
    }
}

void Matrix::input() {
    int val;
    std::cout << "Input Matrix (" << _m << 'x' << _n << ')' << std::endl;
    for (unsigned int i = 0; i < _m; i++) {
        for (unsigned int j = 0; j < _n; j++) {
            std::cout << '[' << i+1 << ',' << j+1 << "]: ";
            std::cin >> val;
            set_value(i, j, val);
        }
    }
}

void Matrix::random_fill() {
    //std::srand(unsigned(std::time(nullptr)));
    std::generate(_data.begin(), _data.end(), []() {
        return rand() % RANDOM_FILL_MAX;
    });
}

Matrix add(Matrix *MA, Matrix *MB) {
    // check dimensions
    if (MA->lines() != MB->lines() || MA->columns() != MB->columns()) {
        throw std::out_of_range("matrix indices out of range"); 
    }
    // set dimension variables
    unsigned int m = MA->lines();
    unsigned int n = MA->columns();
    // new return matrix
    Matrix MC(m, n);
    // do addition
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            MC.set_value(i, j, (MA->get_value(i, j)+MB->get_value(i, j)));
        }
    }
    return MC;
}

Matrix mult(Matrix *MA, Matrix *MB) {
    // check dimensions
    if (MA->columns() != MB->lines()) {
        throw std::out_of_range("matrix indices out of range"); 
    }
    // set dimension variables
    unsigned int l = MA->lines();
    unsigned int m = MA->columns();
    unsigned int n = MB->columns();
    // new return matrix
    Matrix MC(l, n);
    // do multiplacion
    for (unsigned int i = 0; i < l; i++) {
        for (unsigned int j = 0; j < n; j++) {
            for (unsigned int k = 0; k < m; k++) { 
                MC.set_value(i, j, (MA->get_value(i, k)*MB->get_value(k, j)));
            }
        }
    }
    return MC;
}

int main() {
    std::srand(unsigned(std::time(nullptr)));

    printf("Matrix A:\n");
    Matrix A(3, 3);
    A.init();
    A.random_fill();
    A.print();

    printf("Matrix B:\n");
    Matrix B(3, 3);
    B.init();
    B.random_fill();
    B.print();

    printf("Matrix A+B:\n");
    Matrix C(A.lines(), A.columns());
    C = add(&A, &B);
    C.print();

    printf("Matrix A*B:\n");
    Matrix D(A.lines(), B.columns());
    D = mult(&A, &B);
    D.print();

    return 0;
}