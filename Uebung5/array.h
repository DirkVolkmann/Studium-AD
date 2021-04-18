#ifndef _ARRAY_H
#define _ARRAY_H	1

#include <iostream>
#include <iomanip>
#include <chrono>	// RandomFill seed

template <typename T>
class Array {
	private:
		/**
		 * Data
		 */

		T* data_;			// content of array
		unsigned int n_;	// dimension of array

		/**
		 * Functions
		 */

		// shared
		inline void Swap_(unsigned int, unsigned int);

		// InsertionSort
		void InsertionSortR_(int);

		// QuickSort
		int Partition_(int, int);
		int Partition_RandPivot_(int, int);
		void QuickSortR_(int, int);
		void QuickSort_RandPivot_(int, int);

		// MergeSort
		void Merge_(int, int, int);
		//void MergeShow_(int, int, int);
		void MergeSortR_(int, int);
		void MergeSortRShow_(int, int);

		// HeapSort
		void Heapify_(int, int, int);
		void BuildHeap_(int, int);
		void HeapifyShow_(int, int, int);
		void BuildHeapShow_(int, int);
		void PrintHeap_();

	public:
		/**
		 * General functions
		 */

		// constructor
		Array(unsigned int);

		// get/set
		inline void SetValue(unsigned int, T);
		inline T GetValue(unsigned int);
		inline unsigned int Size();

		// other functions
		void CopyTo(Array<T>*);
		void Fill(T);
		void RandomFill(T, T);
		void Init();
		void Print();
		inline void Resize(unsigned int);

		/**
		 * Sorting algorithms
		 */

		// BubbleSort
		void BubbleSort();
		void BubbleSort_UseMax();

		//SelectionSort
		void SelectionSort();
		void SelectionSort_UseMax();

		// InsertionSort
		void InsetionSort();
		void InsertionSort_UseMin();
		void InsertionSort_Rec();

		// QuickSort
		void QuickSort();
		void QuickSort_RandPivot();

		// MergeSort
		void MergeSort();
		void MergeSortShow();
		void MergeSort_Ite();

		// HeapSort
		void HeapSort();
		void HeapSortShow();
};

// Create a array with [n] values
template <typename T>
Array<T>::Array(unsigned int n) {
	n_ = n;
	unsigned int len = sizeof(T) * n;
	data_ = (T *)malloc(len);
}

// Set value at position [p] to value [val]
template <typename T>
inline void Array<T>::SetValue(unsigned int p, T val) {
	data_[p] = val;
}

// Get value at position [p]
template <typename T>
inline T Array<T>::GetValue(unsigned int p) {
	return data_[p];
}

// Get number of possible elements in array
template <typename T>
inline unsigned int Array<T>::Size() {
	return n_;
}

// Copy current array into another
// - If the target array is too big remaining values wont be set
// - If the target array is too small only values up to target size will be used
template <typename T>
void Array<T>::CopyTo(Array<T>* arr) {
	unsigned int n = 0;
	if (this->Size() <= arr->Size()) {
		n = this->Size();
	}
	else {
		n = arr->Size();
	}
	for (unsigned int i = 0; i < n; i++) {
		arr->SetValue(i, data_[i]);
	}
}

// Fill array with value
template <typename T>
void Array<T>::Fill(T val) {
	for (unsigned int i = 0; i < n_; i++) {
			data_[i] = val;
	}
}

// Fill array with random values between [min] and [max]
template <typename T>
void Array<T>::RandomFill(T min, T max) {
	srand(std::chrono::system_clock::now().time_since_epoch().count());

	max++;

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
	for (unsigned int i = 0; i < n_; i++) {
		data_[i] = min + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / (max - min)));
	}
}

// Initialize array with zeros
template <typename T>
void Array<T>::Init() {
	this->Fill(0);
}

// Print all array values
template <typename T>
void Array<T>::Print() {
	for (unsigned int i = 0; i < n_; i++) {
		std::cout << data_[i];
		if (i+1 != n_) {
			std::cout << " | ";
		}
	}
	std::cout << std::endl;
}

// Resize Array to size [n] and reallocate memory
template <typename T>
inline void Array<T>::Resize(unsigned int n) {
	n_ = n;
	unsigned int len = sizeof(T) * n;
	data_ = (T *)realloc(data_, len);
}

// Helper function to swap two elements
template <typename T>
inline void Array<T>::Swap_(unsigned int index1, unsigned int index2) {
	T tmp = data_[index1];
	data_[index1] = data_[index2];
	data_[index2] = tmp;
}

// Bubble Sort
template <typename T>
void Array<T>::BubbleSort() {
	unsigned int i, j;
	for (i = 0; i < n_-1; i++) {
		for (j = 0; j < n_-i-1; j++) {
			if (data_[j] > data_[j+1]) {
				this->Swap_(j, j+1);
			}
		}
	}
}

// Bubble Sort but maximum moves back
template <typename T>
void Array<T>::BubbleSort_UseMax() {
	unsigned int i, j;
	for (i = n_; i > 1; i--) {
		for (j = 0; j < i-1; j++) {
			if (data_[j] > data_[j+1]) {
				this->Swap_(j, j+1);
			}
		}
	}
}

// Selection Sort
template <typename T>
void Array<T>::SelectionSort() {
	unsigned int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n_-1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n_; j++) {
			if (data_[j] < data_[min_idx]) {
				min_idx = j;
			}
		}

		// Swap the found minimum element with the first element
		this->Swap_(min_idx, i);
	}
}

// Selection Sort but swap maximum instead of minimum
template <typename T>
void Array<T>::SelectionSort_UseMax() {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = n_-1; i > 0; i--) {
		// Find the maximum element in unsorted array
		max_idx = i;
		for (j = i-1; j >= 0; j--) {
			if (data_[j] > data_[max_idx]) {
				max_idx = j;
			}
		}

		// Swap the found maximum element with the first element
		this->Swap_(max_idx, i);
	}
}

// InsertionSort
template <typename T>
void Array<T>::InsetionSort() {
	int key = 0, i, j;

	for (j = 1; j < n_; j++) {
		key = data_[j];
		i = j - 1;
		while (i >= 0 && data_[i] > key) {
			data_[i+1] = data_[i];
			i--;
		}
		data_[i+1] = key;
	}
}

// Insetion Sort but move minimum to front
template <typename T>
void Array<T>::InsertionSort_UseMin() {
	int key, i, j;

	for (j = n_-2; j >= 0; j--) {
		key = data_[j];
		i = j + 1;
		while (i < n_ && data_[i] < key) {
			data_[i-1] = data_[i];
			i++;
		}
		data_[i-1] = key;
	}
}

template <typename T>
void Array<T>::InsertionSortR_(int n) {
	// Recursion base case
	if (n <= 1) {
		return;
	}

	// Call recursion for n-1
	this->InsertionSortR_(n-1);

	int key = data_[n-1];
	int i = n-2;
	while (i >= 0 && data_[i] > key) {
		data_[i+1] = data_[i];
		i--;
	}
	data_[i+1] = key;
}

template <typename T>
void Array<T>::InsertionSort_Rec() {
	this->InsertionSortR_(n_);
}

// Helper function for QuickSort
template <typename T>
int Array<T>::Partition_(int first, int last) {
	T pivot = data_[first];
	int p = (first - 1);

	for (int i = first; i <= last; i++) {
		if (data_[i] <= pivot) {
			p++;
			this->Swap_(i, p);
		}
	}
	this->Swap_(first, p);
	return p;
}

// Recursive helper function for QuickSort
template <typename T>
void Array<T>::QuickSortR_(int first, int last) {
	if (first < last) {
		int part_idx = this->Partition_(first, last);
		this->QuickSortR_(first, part_idx-1);
		this->QuickSortR_(part_idx+1, last);
	}
}

// QuickSort
template <typename T>
void Array<T>::QuickSort() {
	this->QuickSortR_(0, n_-1);
}

// Helper function for QuickSort_RandPivot
template <typename T>
int Array<T>::Partition_RandPivot_(int first, int last) {
	srand(time(nullptr));
	int random = first + rand() % (last - first); 
	this->Swap_(random, last);
	return this->Partition_(first, last);
}

// Recursive helper function for QuickSort_RandPivot
template <typename T>
void Array<T>::QuickSort_RandPivot_(int first, int last) {
	if (first < last) {
		int part_idx = this->Partition_RandPivot_(first, last);
		this->QuickSortR_(first, part_idx-1);
		this->QuickSortR_(part_idx+1, last);
	}
}

// Quick Sort but choose pivot randomly
template <typename T>
void Array<T>::QuickSort_RandPivot() {
	this->QuickSort_RandPivot_(0, n_-1);
}

// Helper function for MergeSort
template <typename T>
void Array<T>::Merge_(int first, int last, int middle) {
	int i, n = last - first + 1;
	int arr1_first = first, arr1_last = middle - 1;
	int arr2_first = middle, arr2_last = last;
	int *arr_new = new int[n];

	for (i = 0; i < n; i++) {
		if (arr1_first <= arr1_last) {
			if (arr2_first <= arr2_last) {
				if (data_[arr1_first] <= data_[arr2_first]) {
					arr_new[i] = data_[arr1_first++];
				}
				else {
					arr_new[i] = data_[arr2_first++];
				}
			}
			else {
				arr_new[i] = data_[arr1_first++];
			}
		}
		else {
			arr_new[i] = data_[arr2_first++];
		}
	}

	for (i = 0; i < n; i++) {
		data_[first + i] = arr_new[i];
	}

	delete [] arr_new;
}

// Recursive helper function for MergeSort
template <typename T>
void Array<T>::MergeSortR_(int first, int last) {
	if (first < last) {
		int middle = (first + last + 1) / 2;
		MergeSortR_(first, middle - 1);
		MergeSortR_(middle, last);
		Merge_(first, last, middle);
	}
}

// Merge Sort
template <typename T>
void Array<T>::MergeSortShow() {
	MergeSortRShow_(0, n_-1);
}

// Recursive helper function for MergeSort
template <typename T>
void Array<T>::MergeSortRShow_(int first, int last) {
	std::cout << "MergeSort(" << first << "," << last << ")" << std::endl;
	if (first < last) {
		int middle = (first + last + 1) / 2;
		MergeSortRShow_(first, middle - 1);
		MergeSortRShow_(middle, last);
		std::cout << "Merge(" << first << "," << last << "," << middle << ")" << std::endl;
		Merge_(first, last, middle);
	}
}

// Merge Sort
template <typename T>
void Array<T>::MergeSort() {
	MergeSortR_(0, n_-1);
}

// Merge Sort iterative
template <typename T>
void Array<T>::MergeSort_Ite() {
	int last_index = n_ - 1;
	int first, last, middle, iterator;
	for (iterator = 1; iterator <= last_index; iterator *= 2) {
		for (first = 0; first < last_index; first += iterator*2) {
			middle = std::min(first + iterator - 1, last_index);
			last = std::min(first + iterator * 2 - 1, last_index);

			std::cout << "f: [" << first << "] l: [" << last << "] m: [" << middle << "]" << std::endl;
			Merge_(first, last, middle);
		}
	}
}

// Helper function for HeapSort
template <typename T>
void Array<T>::Heapify_(int first, int last, int root) {
	int largest = root;
	int left  = first + (root - first) * 2 + 1;
	int right = first + (root - first) * 2 + 2;
	
	if (left <= last && data_[left] > data_[largest]) {
		largest = left;
	}

	if (right <= last && data_[right] > data_[largest]) {
		largest = right;
	}

	if (largest != root) {
		this->Swap_(root, largest);
		this->Heapify_(first, last, largest);
	}
}

// Helper function for HeapSort
template <typename T>
void Array<T>::BuildHeap_(int first, int last) {
	int n = last - first + 1;
	for (int i = first + (n - 2) / 2; i >= first; i--) {
		this->Heapify_(first, last, i);
	}
}

// Heap Sort
template <typename T>
void Array<T>::HeapSort() {
	int first = 0;
	int last = n_ - 1;
	this->BuildHeap_(first, last);
	for (int i = last; i > first; i--) {
		this->Swap_(first, i);
		this->Heapify_(first, i-1, first);
	}
}

// Helper function for HeapSort
template <typename T>
void Array<T>::HeapifyShow_(int first, int last, int root) {
	int largest = root;
	int left  = first + (root - first) * 2 + 1;
	int right = first + (root - first) * 2 + 2;

	std::cout << "root: " << data_[root] << std::endl;
	if (left < n_) {
		std::cout << "left: " << data_[left];
		if (right < n_) {
			std::cout << " | right: " << data_[right];
		}
		std::cout << std::endl;
	}
	
	if (left <= last && data_[left] > data_[largest]) {
		largest = left;
	}

	if (right <= last && data_[right] > data_[largest]) {
		largest = right;
	}

	if (largest != root) {
		std::cout << "-> swap " << data_[root] << " and " << data_[largest] << std::endl;
		this->Swap_(root, largest);
		this->HeapifyShow_(first, last, largest);
	}
	else {
		std::cout << "-> root already largest" << std::endl;
	}
}

// Helper function for HeapSortShow
template <typename T>
void Array<T>::BuildHeapShow_(int first, int last) {
	std::cout << "### buidling heap ###" << std::endl;
	int n = last - first + 1;
	for (int i = first + (n - 2) / 2; i >= first; i--) {
		std::cout << "start heapify with index [" << i << "]" << std::endl;
		this->HeapifyShow_(first, last, i);
	}
	std::cout << std::endl;
}

// Heap Sort but show steps
template <typename T>
void Array<T>::HeapSortShow() {
	std::cout << "unsorted tree:" << std::endl;
	this->PrintHeap_();
	std::cout << std::endl;

	int first = 0;
	int last = n_ - 1;

	this->BuildHeapShow_(first, last);

	std::cout << "tree after build:" << std::endl;
	this->PrintHeap_();
	std::cout << std::endl;

	for (int i = last; i > first; i--) {
		std::cout << "### sorting run " << last-i+1 << " of " << last << " ###" << std::endl;
		std::cout << "swap [" << first << "] and [" << i << "] (" << data_[first] << " and " << data_[i] << ")" << std::endl;
		this->Swap_(first, i);
		this->HeapifyShow_(first, i-1, first);
		std::cout << std::endl << "tree after run:" << std::endl;
		this->PrintHeap_();
		std::cout << std::endl;
	}
}

// Print array as heap/tree
template <typename T>
void Array<T>::PrintHeap_() {
	// calculate indentations for first line
	int indents = 1;
	int rest = n_ - indents;
	while (rest > 0) {
		indents *= 2;
		rest -= indents;
	}

	// other variables
	int vals_in_line = 1;
	int idx_min = 0;
	int idx_max = 0;

	while (1) {
		for (int i = idx_min; i <= idx_max; i++) {
			// print left indentations
			for (int j = 0; j < indents - 1; j++) {
				std::cout << "    ";
			}

			/*if (i == idx_min && i != idx_max) {
				std::cout << " ";
			}*/

			// print value
			std::cout << std::setw(4) << data_[i];

			/*if (i+1 <= idx_max && i+1 < n_) {
				std::cout << "  ";
			}*/

			// print right indentations
			for (int j = 0; j < indents; j++) {
				std::cout << "    ";
			}
			if (i == idx_max) {
				std::cout << std::endl;
			}

			// return condition
			if (i+1 >= n_) {
				std::cout << std::endl;
				return;
			}
		}

		// calculate variables for next run
		indents /= 2;
		vals_in_line *= 2;
		idx_min = vals_in_line - 1;
		idx_max = vals_in_line * 2 - 2;
	}
}

#endif /* <array.h> included.  */