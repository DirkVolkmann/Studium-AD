#ifndef _MATRIX_H
#define _MATRIX_H	1

#include <iostream>
#include <iomanip>
#include <chrono>	// RandomFill seed

// Matrix with [m x n] integer values
template <typename T>
class Matrix {
	private:
		T** data_;
		unsigned int m_, n_;
	public:
		Matrix(unsigned int, unsigned int);
		inline void SetValue(unsigned int, unsigned int, T);
		inline T GetValue(unsigned int, unsigned int);
		inline unsigned int Lines();
		inline unsigned int Columns();
		void Init();
		void Fill(T);
		void Print();
		void Input();
		void RandomFill(T, T);
};

// Create a matrix with [m x n] values
template <typename T>
Matrix<T>::Matrix(const unsigned int m, const unsigned int n) {
	m_ = m;
	n_ = n;
	unsigned int len = sizeof(T *) * m + sizeof(T) * n * m;
    data_ = (T **)malloc(len);
  
    // ptr is now pointing to the first element in of 2D array
    T *ptr = (T *)(data_ + m);
  
    // for loop to point rows pointer to appropriate location in 2D array
    for(unsigned int i = 0; i < m; i++)
        data_[i] = (ptr + n * i);
}

// Set value at position [m,n] to value [v]
template <typename T>
inline void Matrix<T>::SetValue(unsigned int m, unsigned int n, T val) {
	data_[m-1][n-1] = val;
}

// Get value at position [m,n]
template <typename T>
inline T Matrix<T>::GetValue(unsigned int m, unsigned int n) {
	return data_[m-1][n-1];
}

// Get number of Lines or [m]-dimension
template <typename T>
inline unsigned int Matrix<T>::Lines() {
	return m_;
}

// Get number of Columns or [n]-dimension
template <typename T>
inline unsigned int Matrix<T>::Columns() {
	return n_;
}

// Fill matrix with value
template <typename T>
void Matrix<T>::Fill(T val) {
	for (unsigned int i = 0; i < m_; i++) {
		for (unsigned int j = 0; j < n_; j++) {
			data_[i][j] = val;
		}
	}
}

// Initialize matrix with zeros
template <typename T>
void Matrix<T>::Init() {
	this->Fill(0);
}

// Print all matrix values
template <typename T>
void Matrix<T>::Print() {
	for (unsigned int i = 1; i <= m_; i++) {
		for (unsigned int j = 1; j <= n_; j++) {
			std::cout << std::setw(3) << GetValue(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

// Input values to matrix on commandline
template <typename T>
void Matrix<T>::Input() {
	T val;
	std::cout << "Input Matrix (" << m_ << 'x' << n_ << ')' << std::endl;
	for (unsigned int i = 1; i <= m_; i++) {
		for (unsigned int j = 1; j <= n_; j++) {
			std::cout << '[' << i << ',' << j << "]: ";
			std::cin >> val;
			SetValue(i, j, val);
		}
	}
}

// Fill matrix with random values between [min] and [max]
template <typename T>
void Matrix<T>::RandomFill(T min, T max) {
	srand(std::chrono::system_clock::now().time_since_epoch().count());

	// make sure min is min and max is max
	if (min > max) {
		T tmp = min;
		min = max;
		max = tmp;
	}
	// trivial solution
	else if (min == max) {
		this->Fill(min);
	}
	// generate random number within selected range (min to max)
	for (unsigned int i = 0; i < m_; i++) {
		for (unsigned int j = 0; j < n_; j++) {
			data_[i][j] = min + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / (max - min)));
		}
	}
}

// Addition of two matrices
template <typename T>
Matrix<T> Add(Matrix<T> *ma, Matrix<T> *mb) {
	// check dimensions
	if (ma->Lines() != mb->Lines() || ma->Columns() != mb->Columns()) {
		throw std::out_of_range("matrix indices out of range"); 
	}
	// set dimension variables
	unsigned int m = ma->Lines();
	unsigned int n = ma->Columns();
	// new return matrix
	Matrix<T> mc(m, n);
	// do addition
	for (unsigned int i = 1; i <= m; i++) {
		for (unsigned int j = 1; j <= n; j++) {
			mc.SetValue(i, j, (ma->GetValue(i, j) + mb->GetValue(i, j)));
		}
	}
	return mc;
}

// Subtraction of two matrices
template <typename T>
Matrix<T> Sub(Matrix<T> *ma, Matrix<T> *mb) {
	// check dimensions
	if (ma->Lines() != mb->Lines() || ma->Columns() != mb->Columns()) {
		throw std::out_of_range("matrix indices out of range"); 
	}
	// set dimension variables
	unsigned int m = ma->Lines();
	unsigned int n = ma->Columns();
	// new return matrix
	Matrix<T> mc(m, n);
	// do subtraction
	for (unsigned int i = 1; i <= m; i++) {
		for (unsigned int j = 1; j <= n; j++) {
			mc.SetValue(i, j, (ma->GetValue(i, j) - mb->GetValue(i, j)));
		}
	}
	return mc;
}

// Multiplication of two matrices
template <typename T>
Matrix<T> Mult(Matrix<T> *ma, Matrix<T> *mb) {
	// check dimensions
	if (ma->Columns() != mb->Lines()) {
		throw std::out_of_range("matrix indices out of range"); 
	}
	// set dimension variables
	unsigned int n = ma->Lines();
	unsigned int m = ma->Columns();
	unsigned int p = mb->Columns();
	// new return matrix
	Matrix<T> mc(n, p);
	// helper in loop
	T sum = 0;
	// do multiplacion
	for (unsigned int i = 1; i <= n; i++) {
		//std::cout << "mult i " << i << std::endl;
		for (unsigned int j = 1; j <= p; j++) {
			sum = 0;
			for (unsigned int k = 1; k <= m; k++) { 
				sum += ma->GetValue(i, k) * mb->GetValue(k, j);
			}
			mc.SetValue(i, j, sum);
		}
	}
	return mc;
}

// Multiplication of two matrices with Strassen's algorithm
template <typename T>
Matrix<T> MultStrassen(Matrix<T> *ma, Matrix<T> *mb) {
	// check dimensions
	unsigned int n = ma->Columns();
	if (n != ma->Lines() || n != mb->Columns() || n != mb->Lines()) {
		throw std::out_of_range("matrix indices out of range"); 
	}

	// new return matrix C
	Matrix<T> mc(n, n);

	// base case
	if (n == 1) {
		mc = Mult(ma, mb);
		return mc;
	}

	// Initialize sub-matrices A and B
	unsigned int m = n/2;
	Matrix<T> ma11(m, m), ma12(m, m), ma21(m, m), ma22(m, m);
	Matrix<T> mb11(m, m), mb12(m, m), mb21(m, m), mb22(m, m);
	for (unsigned int i = 1; i <= m; i++) {
		for (unsigned int j = 1; j <= m; j++) {
			ma11.SetValue(i, j, ma->GetValue(i,   j  ));
			ma12.SetValue(i, j, ma->GetValue(i,   j+m));
			ma21.SetValue(i, j, ma->GetValue(i+m, j  ));
			ma22.SetValue(i, j, ma->GetValue(i+m, j+m));
			mb11.SetValue(i, j, mb->GetValue(i,   j  ));
			mb12.SetValue(i, j, mb->GetValue(i,   j+m));
			mb21.SetValue(i, j, mb->GetValue(i+m, j  ));
			mb22.SetValue(i, j, mb->GetValue(i+m, j+m));
		}
	}

	// calculate helper-matrices H1-7
	Matrix<T> mh1(m, m), mh2(m, m), mh3(m, m), mh4(m, m), mh5(m, m), mh6(m, m), mh7(m, m);
	// temporary matrices to use as reference
	Matrix<T> mha(m, m), mhb(m, m);
	// H1 = (A11 + A22) * (B11 + B22)
	mha = Add(&ma11, &ma22);
	mhb = Add(&mb11, &mb22);
	mh1 = MultStrassen(&mha, &mhb);
	// H2 = (A21 + A22) * B11
	mha = Add(&ma21, &ma22);
	mh2 = MultStrassen(&mha, &mb11);
	// H3 = A11 * (B12 - B22)
	mhb = Sub(&mb12, &mb22);
	mh3 = MultStrassen(&ma11, &mhb);
	// H4 = A22 * (B21 - B11)
	mhb = Sub(&mb21, &mb11);
	mh4 = MultStrassen(&ma22, &mhb);
	// H5 = (A11 + A12) * B22
	mha = Add(&ma11, &ma12);
	mh5 = MultStrassen(&mha, &mb22);
	// H6 = (A21 - A11) * (B11 + B12)
	mha = Sub(&ma21, &ma11);
	mhb = Add(&mb11, &mb12);
	mh6 = MultStrassen(&mha, &mhb);
	// H7 = (A12 - A22) * (B21 + B22)
	mha = Sub(&ma12, &ma22);
	mhb = Add(&mb21, &mb22);
	mh7 = MultStrassen(&mha, &mhb);

	// calculate resulting matrix C using Strassen's formula
	Matrix<T> mc11(m, m), mc12(m, m), mc21(m, m), mc22(m, m);
	// C11 = H1 + H4 - H5 + H7
	mha = Add(&mh1, &mh4);
	mhb = Sub(&mh7, &mh5);
	mc11 = Add(&mha, &mhb);
	// C12 = H3 + H5
	mc12 = Add(&mh3, &mh5);
	// C21 = H2 + H4
	mc21 = Add(&mh2, &mh4);
	// C22 = H1 - H2 + H3 + H6
	mha = Sub(&mh1, &mh2);
	mhb = Add(&mh3, &mh6);
	mc22 = Add(&mha, &mhb);

	// putting C together and returning result
	for (unsigned int i = 1; i <= m; i++) {
		for (unsigned int j = 1; j <= m; j++) {
			mc.SetValue(i,   j,   mc11.GetValue(i, j));
			mc.SetValue(i,   j+m, mc12.GetValue(i, j));
			mc.SetValue(i+m, j,   mc21.GetValue(i, j));
			mc.SetValue(i+m, j+m, mc22.GetValue(i, j));
		}
	}

	return mc;
}

#endif /* <matrix.h> included.  */