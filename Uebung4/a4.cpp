#include <iostream>
#include <chrono>
#include "array.h"

#define DONE -1
#define BUBBLE_SORT 0
#define QUICK_SORT 1

typedef std::chrono::_V2::system_clock::time_point time_point;

inline time_point Now() {
    return std::chrono::high_resolution_clock::now();
}

inline std::chrono::seconds CalcSeconds(time_point t_start, time_point t_end) {
    return std::chrono::duration_cast<std::chrono::seconds>(t_end - t_start);
}

// Main
int main() {
	unsigned int n_max = 1000000000;	// max size of array
	unsigned int n_start = 1000;		// start size of array
	unsigned int n_current = n_start;	// current size of array
	unsigned int n_over = n_start;		// array size sorted too slow
	unsigned int n_short = 0;			// array size sorted too fast
	unsigned int sort_seconds = 10;		// target sorting time in s
	
	// define arrays for sorting
	typedef int array_type;
	Array<array_type> base(n_max);
	Array<array_type> a(1);
	Array<array_type> b(1);

	// fill base array randomly
	base.RandomFill(-1000000, 1000000);

	// timing variables
	auto start = Now();
    auto end = Now();
    auto duration = CalcSeconds(start, end);

	unsigned int sorted_final[2] = { 0 };
	int action = BUBBLE_SORT;

	while (1) {
		if (action == BUBBLE_SORT) {
			std::cout << "BubbleSort " << n_current << " elements: ";

			a.Resize(n_current);
			base.CopyTo(&a);

			start = Now();
			a.BubbleSort();
			end = Now();

			duration = CalcSeconds(start, end);
			std::cout << duration.count() << "s" << std::endl;

			sorted_final[action] = n_current;
		}
		else if (action == QUICK_SORT) {
			std::cout << "QuickSort " << n_current << " elements: ";

			b.Resize(n_current);
			base.CopyTo(&b);

			start = Now();
			b.QuickSort();
			end = Now();

			duration = CalcSeconds(start, end);
			std::cout << duration.count() << "s" << std::endl;

			sorted_final[action] = n_current;
		}
		else {
			break;
		}

		if (duration.count() == sort_seconds) {
			// reset dimensions
			n_current = n_start;
			n_over = n_start;
			n_short = 0;
			// next action
			action = action == BUBBLE_SORT ? QUICK_SORT : DONE;
			continue;
		}

		// Duration too short or too long?
		if (duration.count() < sort_seconds) {
			n_short = n_current;
		}
		else {
			n_over = n_current;
		}

		// calculate dimension for next run
		if (n_short >= n_over) {
			n_current *= 2;
		}
		else {
			n_current = n_short + (n_over - n_short) / 2;
		}
	}

	std::cout << "Elements sorted in " << sort_seconds << " seconds:" << std::endl;
	std::cout << "BubbleSort: " << sorted_final[BUBBLE_SORT] << std::endl;
	std::cout << "QuickSort:  " << sorted_final[QUICK_SORT]  << std::endl;

	return 0;
}