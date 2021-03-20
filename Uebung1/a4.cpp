#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

#define RANDOM_FILL_MAX 100
#define NOW std::chrono::high_resolution_clock::now()
#define CALC_US(t_start, t_stop) (std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start))
#define ADD 0
#define MULT 1
#define DONE 2

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
        //std::cout << "mult i " << i << std::endl;
        for (unsigned int j = 0; j < n; j++) {
            for (unsigned int k = 0; k < m; k++) { 
                MC.set_value(i, j, (MA->get_value(i, k)*MB->get_value(k, j)));
            }
        }
    }
    return MC;
}

int main() {
    // initialize random number generator
    std::srand(unsigned(std::time(nullptr)));

    // dimensions
    auto dim_start = 1000, dim = dim_start, dim_over = dim_start, dim_short = 0;

    // variables for time calculation
    auto start = NOW;
    auto stop = NOW;
    auto duration = CALC_US(start, stop);

    // other variables
    auto duration_goal = 100000;    // duration goal in us
    /**
     * Duration goal is 1s to save time for testing
     */
    auto duration_margin = 10000;   // duration can be over or under margin
    auto action = ADD;              // current action (add, mult)
    unsigned int dims_final[2];     // final dimension for time goal per action

    while (1) {

        /**
         * Init all variables
         */

        Matrix A(dim, dim);
        A.random_fill();

        Matrix B(dim, dim);
        B.random_fill();

        Matrix C(dim, dim);
        C.init();

        if (action == ADD) {

            /**
             * Addition
             */

            std::cout << "[ADD] " << dim << " dimensions in ";
            
            start = NOW;

            C = add(&A, &B);

            stop = NOW;
            duration = CALC_US(start, stop);
            std::cout << duration.count() << "us" << std::endl;

        }
        else if (action == MULT) {

            /**
             * Multiplication
             */

            std::cout << "[MULT] " << dim << " dimensions in ";

            start = NOW;

            C = mult(&A, &B);

            stop = NOW;
            duration = CALC_US(start, stop);
            std::cout << duration.count() << "us" << std::endl;

        }
        else {
            // exit loop when all calculations are done
            break;
        }

        /**
         * Calculate next dimension or exit
         */

        // Final time reached within margin?
        if (duration.count() >= duration_goal-duration_margin && duration.count() <= duration_goal+duration_margin) {
            // save current dimension as final
            dims_final[action] = dim;
            // reset dimensions
            dim = dim_start;
            dim_over = dim_start;
            dim_short = 0;
            // next action
            action = action == ADD ? MULT : DONE;
            continue;
        }

        // Duration too short or too long?
        if (duration.count() < duration_goal) {
            dim_short = dim;
        }
        else {
            dim_over = dim;
        }

        // calculate dimension for next run
        if (dim_short >= dim_over) {
            dim *= 2;
        }
        else {
            dim = dim_short + (dim_over - dim_short) / 2;
        }

    }

    std::cout << "Maximum dimensions in " << duration_goal << "us" << std::endl;
    std::cout << "Add:  " << dims_final[ADD] << std::endl;
    std::cout << "Mult: " << dims_final[MULT] << std::endl;

    return 0;
}