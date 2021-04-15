#ifndef _ARRAY_H
#define _ARRAY_H	1

#include <iostream>
#include <iomanip>
#include <chrono>	// RandomFill seed

template <typename T>
class Array {
	private:
		T* data_;			// content of array
		unsigned int n_;	// dimension of array
		inline void Swap_(unsigned int, unsigned int);
		int Partition_(int, int);
		void QuickSortR_(int, int);
		int Partition_RandPivot_(int, int);
		void QuickSort_RandPivot_(int, int);
	public:
		Array(unsigned int);
		inline void SetValue(unsigned int, T);
		inline T GetValue(unsigned int);
		inline unsigned int Size();
		void CopyTo(Array<T>*);
		void Fill(T);
		void RandomFill(T, T);
		void Init();
		void Print();
		inline void Resize(unsigned int);
		void BubbleSort();
		void BubbleSort_UseMax();
		void SelectionSort();
		void SelectionSort_UseMax();
		void InsetionSort();
		void InsertionSort_UseMin();
		void QuickSort();
		void QuickSort_RandPivot();
};

// Create a array with [n] values
template <typename T>
Array<T>::Array(unsigned int n) {
	n_ = n;
	unsigned int len = sizeof(T) * n;
	data_ = (T *)malloc(len);
}

// Set value at position [m,n] to value [v]
template <typename T>
inline void Array<T>::SetValue(unsigned int p, T val) {
	data_[p] = val;
}

// Get value at position [m,n]
template <typename T>
inline T Array<T>::GetValue(unsigned int p) {
	return data_[p];
}

// Get number of columns or [n]-dimension
template <typename T>
inline unsigned int Array<T>::Size() {
	return n_;
}

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

// Selection Sort
template <typename T>
void Array<T>::SelectionSort_UseMax() {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = n_; i > 0; i--) {
		// Find the minimum element in unsorted array
		max_idx = i;
		for (j = i-1; j >= 0; j--) {
			if (data_[j] > data_[max_idx]) {
				max_idx = j;
			}
		}

		// Swap the found minimum element with the first element
		this->Swap_(max_idx, i);
	}
}

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

template <typename T>
void Array<T>::InsertionSort_UseMin() {
	int key, i, j;

	for (j = n_-1; j >= 0; j--) {
		key = data_[j];
		i = j + 1;
		while (i <= n_ && data_[i] < key) {
			data_[i-1] = data_[i];
			i++;
		}
		data_[i-1] = key;
	}
}

// Helper function for QuickSort
template <typename T>
int Array<T>::Partition_(int low, int high) {
	T pivot = data_[low];
	int p = (low - 1);

	for (int i = low; i <= high; i++) {
		if (data_[i] <= pivot) {
			p++;
			this->Swap_(i, p);
		}
	}
	this->Swap_(low, p);
	return p;
}

// Recursive helper function for QuickSort
template <typename T>
void Array<T>::QuickSortR_(int low, int high) {
	if (low < high) {
		int part_idx = this->Partition_(low, high);
		this->QuickSortR_(low, part_idx-1);
		this->QuickSortR_(part_idx+1, high);
	}
}

// Quick Sort
template <typename T>
void Array<T>::QuickSort() {
	this->QuickSortR_(0, n_-1);
}

// Helper function for QuickSort_RandPivot
template <typename T>
int Array<T>::Partition_RandPivot_(int low, int high) {
	srand(time(nullptr));
	int random = low + rand() % (high - low); 
	this->Swap_(random, high);
	return this->Partition_(low, high);
}

// Recursive helper function for QuickSort_RandPivot
template <typename T>
void Array<T>::QuickSort_RandPivot_(int low, int high) {
	if (low < high) {
		int part_idx = this->Partition_RandPivot_(low, high);
		this->QuickSortR_(low, part_idx-1);
		this->QuickSortR_(part_idx+1, high);
	}
}

// Quick Sort but choose pivot randomly
template <typename T>
void Array<T>::QuickSort_RandPivot() {
	this->QuickSort_RandPivot_(0, n_-1);
}

#endif /* <array.h> included.  */