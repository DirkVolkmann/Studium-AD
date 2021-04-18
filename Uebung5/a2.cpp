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
    Array<array_type> i(n);
    Array<array_type> j(n);
    Array<array_type> k(n);
	Array<array_type> l(n);

	a.RandomFill(-99, 99);
	a.CopyTo(&b);
	a.CopyTo(&c);
	a.CopyTo(&d);
	a.CopyTo(&e);
	a.CopyTo(&f);
	a.CopyTo(&g);
	a.CopyTo(&h);
    a.CopyTo(&i);
    a.CopyTo(&j);
    a.CopyTo(&k);
	a.CopyTo(&l);

	std::cout << "Array (unsorted): " << std::endl;
	a.Print();

	a.BubbleSort();
	b.SelectionSort();
	c.InsetionSort();
	d.QuickSort();
	e.BubbleSort_UseMax();
	f.SelectionSort_UseMax();
	g.InsertionSort_UseMin();
	h.InsertionSort_Rec();
	i.QuickSort_RandPivot();
    j.MergeSort();
    k.MergeSort_Ite();
    l.HeapSort();
	
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
	std::cout << "Array H (InsertionSort_Rec): " << std::endl;
	h.Print();
	std::cout << "Array H (QuickSort_RandPivot): " << std::endl;
	i.Print();
    std::cout << "Array I (MergeSort): " << std::endl;
	j.Print();
    std::cout << "Array J (MergeSort_Ite): " << std::endl;
	k.Print();
    std::cout << "Array K (HeapSort): " << std::endl;
	l.Print();

	return 0;
}