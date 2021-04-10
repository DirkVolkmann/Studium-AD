#include <iostream>
#include "array.h"

// Main
int main() {
	unsigned int n = 10;
	typedef int array_type;

	Array<array_type> a(n);
	Array<array_type> b(n);
	Array<array_type> c(n);

	a.RandomFill(0, 20);
	a.CopyTo(&b);
	a.CopyTo(&c);

	std::cout << "Array A: " << std::endl;
	a.Print();
	std::cout << "Array B: " << std::endl;
	b.Print();
	std::cout << "Array C: " << std::endl;
	c.Print();

	a.BubbleSort();
	b.SelectionSort();
	c.QuickSort();
	std::cout << std::endl;

	std::cout << "Array A: " << std::endl;
	a.Print();
	std::cout << "Array B: " << std::endl;
	b.Print();
	std::cout << "Array C: " << std::endl;
	c.Print();

	return 0;
}