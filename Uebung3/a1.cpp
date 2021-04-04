#include <iostream>
#include <iomanip>
#include "matrix.h"

int MaxPartialSum2D(Matrix* matrix) {
	int max = INT32_MIN;
    int sum = 0;
	unsigned int n = matrix->Columns();
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n-i; j++) {
			for (unsigned int k = 0; k < n-i; k++) {
				sum = 0;
				for (unsigned int l = 0; l <= i; l++) {
					for (unsigned int m = 0; m <= i; m++) {
						sum += matrix->GetValue(j+l, k+m);
					}
				}
				if (sum > max) {
					max = sum;
				}
			}
		}
	}
	return max;
}

int main() {
	const unsigned int kDimension = 4;
	
	Matrix ma(kDimension, kDimension);
	ma.RandomFill(-99, 99);
	
    std::cout << "matrix:" << std::endl;
	ma.Print();

	int max = MaxPartialSum2D(&ma);
    std::cout << "max partial sum 2d: " << max << std::endl;

    return 0;
}