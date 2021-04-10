#include <iostream>
#include <chrono>
#include <tgmath.h> // pow
#include "matrix.h"

typedef std::chrono::_V2::system_clock::time_point time_point;

inline time_point Now() {
    return std::chrono::high_resolution_clock::now();
}

inline std::chrono::seconds CalcSeconds(time_point t_start, time_point t_stop) {
    return std::chrono::duration_cast<std::chrono::seconds>(t_stop - t_start);
}

int main() {
    for (unsigned int i = 1; i <= 10; i++) {
        // define dimension as 2^i
        unsigned int n = std::pow(2, i);
        std::cout << "Dimensions: " << n << std::endl;

        // type to use for matrices
        typedef double matrix_type;
        
        // generate matrix A
        Matrix<matrix_type> A(n, n);
        A.RandomFill(-10, 10);
        //std::cout << "Matrix A:" << std::endl;
        //A.Print();
        
        // generate matrix B
        Matrix<matrix_type> B(n, n);
        B.RandomFill(-10, 10);
        //std::cout << "Matrix B: " << std::endl;
        //B.Print();

        // variables for time calculation
        time_point start = Now();
        time_point stop = Now();
        auto duration = CalcSeconds(start, stop);

        // normal O(3) multiplication of A and B
        Matrix<matrix_type> M(n, n);
        std::cout << "Mult normal:   ";
        start = Now();
        M = Mult(&A, &B);
        stop = Now();
        duration = CalcSeconds(start, stop);
        std::cout << duration.count() << "s" << std::endl;
        //M.Print();

        // use Strassen's algorithm O(2.8)
        std::cout << "Mult Strassen: ";
        start = Now();
        M = MultStrassen(&A, &B);
        stop = Now();
        duration = CalcSeconds(start, stop);
        std::cout << duration.count() << "s" << std::endl;
        //M.Print();
    }

    return 0;
}