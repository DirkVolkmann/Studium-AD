#include <iostream>
#include "array.h"

int main() {
	unsigned int size = 10;
	typedef int array_type;

	Array<array_type> a(size);

	int init_array[] = {-5,13,-32,7,-3,17,23,12,-35,19};
	for (int idx = 0; idx < size; idx++) {
		a.SetValue(idx, init_array[idx]);
	}

	std::cout << "array initial:" << std::endl;
	a.Print();
	std::cout << std::endl;

	a.HeapSortShow();

	std::cout << std::endl;
	std::cout << "array sorted:" << std::endl;
	a.Print();

	return 0;
}