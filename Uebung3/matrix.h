#ifndef _MATRIX_H
#define _MATRIX_H	1

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

// Matrix with [m x n] integer values
class Matrix {
	private:
		std::vector<int> data_;
		unsigned int m_, n_;
	public:
		Matrix(unsigned int, unsigned int);
		void SetValue(unsigned int, unsigned int, int);
		int GetValue(unsigned int, unsigned int);
		unsigned int Lines();
		unsigned int Columns();
		void Init();
		void Print();
		void Input();
		void RandomFill(int, int);
};

// Create a matrix with [m x n] values
Matrix::Matrix(const unsigned int m, const unsigned int n) {
	m_ = m;
	n_ = n;
	data_.resize(m_*n_);
}

// Set value at position [m,n] to value [v]
void Matrix::SetValue(unsigned int m, unsigned int n, int val) {
	data_.at(m*n_+n) = val;
}

// Get value at position [m,n]
int Matrix::GetValue(unsigned int m, unsigned int n) {
	return data_.at(m*n_+n);
}

// Get number of Lines or [m]-dimension
unsigned int Matrix::Lines() {
	return m_;
}

// Get number of Columns or [n]-dimension
unsigned int Matrix::Columns() {
	return n_;
}

// Initialize matrix with zeros
void Matrix::Init() {
	std::fill(data_.begin(), data_.end(), 0);
}

// Print all matrix values
void Matrix::Print() {
	for (unsigned int i = 0; i < m_; i++) {
		for (unsigned int j = 0; j < n_; j++) {
			std::cout << std::setw(3) << GetValue(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

// Input values to matrix on commandline
void Matrix::Input() {
	int val;
	std::cout << "Input Matrix (" << m_ << 'x' << n_ << ')' << std::endl;
	for (unsigned int i = 0; i < m_; i++) {
		for (unsigned int j = 0; j < n_; j++) {
			std::cout << '[' << i+1 << ',' << j+1 << "]: ";
			std::cin >> val;
			SetValue(i, j, val);
		}
	}
}

// Fill matrix with values up to [max]
void Matrix::RandomFill(int min, int max) {
	// seed random number generator with current time
	std::srand(unsigned(std::time(nullptr)));
	// make sure min is min and max is max
	if (min > max) {
		int tmp = min;
		min = max;
		max = tmp;
	}
	// can't "% 0" and trivial solution
	else if (min == max) {
		std::fill(data_.begin(), data_.end(), min);
	}
	// generate random number within selected range (max - min)
	// and shift it accordingly (+ min)
	std::generate(data_.begin(), data_.end(), [min, max]() {
		return rand() % (max - min) + min;
	});
}

// Addition of two matrices
Matrix Add(Matrix *ma, Matrix *mb) {
	// check dimensions
	if (ma->Lines() != mb->Lines() || ma->Columns() != mb->Columns()) {
		throw std::out_of_range("matrix indices out of range"); 
	}
	// set dimension variables
	unsigned int m = ma->Lines();
	unsigned int n = ma->Columns();
	// new return matrix
	Matrix mc(m, n);
	// do addition
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < n; j++) {
			mc.SetValue(i, j, (ma->GetValue(i, j)+mb->GetValue(i, j)));
		}
	}
	return mc;
}

// Multiplication of two matrices
Matrix Mult(Matrix *ma, Matrix *mb) {
	// check dimensions
	if (ma->Columns() != mb->Lines()) {
		throw std::out_of_range("matrix indices out of range"); 
	}
	// set dimension variables
	unsigned int l = ma->Lines();
	unsigned int m = ma->Columns();
	unsigned int n = mb->Columns();
	// new return matrix
	Matrix mc(l, n);
	// do multiplacion
	for (unsigned int i = 0; i < l; i++) {
		//std::cout << "mult i " << i << std::endl;
		for (unsigned int j = 0; j < n; j++) {
			for (unsigned int k = 0; k < m; k++) { 
				mc.SetValue(i, j, (ma->GetValue(i, k)*mb->GetValue(k, j)));
			}
		}
	}
	return mc;
}

#endif /* <matrix.h> included.  */