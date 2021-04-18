#include <iostream>
#include "array.h"

int main() {
	unsigned int size = 10;
	typedef int array_type;

	Array<array_type> a(size);
	Array<array_type> b(size);

	int init_array[] = {-5,13,-32,7,-3,17,23,12,-35,19};
	for (int idx = 0; idx < size; idx++) {
		a.SetValue(idx, init_array[idx]);
		b.SetValue(idx, init_array[idx]);
	}

	/**
	 * Merge Sort
	 */

	std::cout << "### Merge Sort ###" << std::endl;
	std::cout << std::endl;
	std::cout << "array initial:" << std::endl;
	a.Print();
	std::cout << std::endl;

	a.MergeSortShow();

	std::cout << std::endl;
	std::cout << "array sorted:" << std::endl;
	a.Print();

	/**
	 * Heap Sort
	 */

	std::cout << "### Heap Sort ###" << std::endl;
	std::cout << std::endl;
	std::cout << "array initial:" << std::endl;
	b.Print();
	std::cout << std::endl;

	b.HeapSortShow();

	std::cout << std::endl;
	std::cout << "array sorted:" << std::endl;
	b.Print();

	return 0;
}