#include <iostream>
#include "array.h"

int main() {
	unsigned int n = 10;
	typedef int array_type;

	Array<array_type> a(n);
	Array<array_type> b(n);
	Array<array_type> c(n);
	Array<array_type> d(n);
	Array<array_type> e(n);
	Array<array_type> f(n);
	Array<array_type> g(n);
	Array<array_type> h(n);

	a.RandomFill(0, 20);
	a.CopyTo(&b);
	a.CopyTo(&c);
	a.CopyTo(&d);
	a.CopyTo(&e);
	a.CopyTo(&f);
	a.CopyTo(&g);
	a.CopyTo(&h);

	std::cout << "Array (unsorted): " << std::endl;
	a.Print();

	a.BubbleSort();
	b.SelectionSort();
	c.InsetionSort();
	d.QuickSort();
	e.BubbleSort_UseMax();
	f.SelectionSort_UseMax();
	g.InsertionSort_UseMin();
	h.QuickSort_RandPivot();
	
	std::cout << std::endl;

	std::cout << "Array A (BubbleSort): " << std::endl;
	a.Print();
	std::cout << "Array B (SelectionSort): " << std::endl;
	b.Print();
	std::cout << "Array C (InsetionSort): " << std::endl;
	c.Print();
	std::cout << "Array D (QuickSort): " << std::endl;
	d.Print();
	std::cout << "Array E (BubbleSort_UseMax): " << std::endl;
	e.Print();
	std::cout << "Array F (SelectionSort_UseMax): " << std::endl;
	f.Print();
	std::cout << "Array G (InsertionSort_UseMin): " << std::endl;
	g.Print();
	std::cout << "Array H (QuickSort_RandPivot): " << std::endl;
	h.Print();

	return 0;
}