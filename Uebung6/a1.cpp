#include <iostream>
#include <chrono>
#include <vector>
#include "array.h"

typedef std::chrono::_V2::system_clock::time_point time_point;
typedef std::chrono::seconds s;
typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds us;

inline time_point Now() {
    return std::chrono::high_resolution_clock::now();
}

template <typename T_time>
inline T_time CalcTime(time_point t_start, time_point t_end) {
    return std::chrono::duration_cast<T_time>(t_end - t_start);
}

int main() {
    // timing stuff
    typedef us T_time;
    std::string str_time = "us";
	auto start = Now();
    auto end = Now();
    auto duration = CalcTime<T_time>(start, end);

    // variable length
    std::vector<unsigned int> size_vals = {10, 200, 300, 400, 500, 1000, 5000, 10000, 50000, 100000};
    //std::vector<unsigned int> size_vals = {100'000'000};

    // array stuff
    const unsigned int min = 1000;
    const unsigned int max = 10000;
    typedef int T_array;
    Array<T_array> a(0);
    Array<T_array> b(0);
    Array<T_array> c(0);

    for (auto i = size_vals.begin(); i != size_vals.end(); ++i) {

        unsigned int size = *i;
        std::cout << "### Array size is " << size << " ###" << std::endl;
        
        a.Resize(size);
        b.Resize(size);
        c.Resize(size);

        a.RandomFill(min, max);
        a.CopyTo(&b);
        a.CopyTo(&c);

        //a.Print();

        std::cout << "Heap Sort: ";
        start = Now();
        a.HeapSort();
        end = Now();
        duration = CalcTime<T_time>(start, end);
        std::cout << duration.count() << str_time << std::endl;
        //a.Print();

        std::cout << "Count Sort: ";
        start = Now();
        b.CountSort(max);
        end = Now();
        duration = CalcTime<T_time>(start, end);
        std::cout << duration.count() << str_time << std::endl;
        //b.Print();

        std::cout << "Map Sort: ";
        start = Now();
        c.MapSort(1.25);
        end = Now();
        duration = CalcTime<T_time>(start, end);
        std::cout << duration.count() << str_time << std::endl;
        //c.Print();

        /**
         * Conclusion:
         * - HeapSort is fastest with small and slowest with big arrays
         * - CountSort will perform best in comparison with bigger arrays
         * - MapSort will perform best in comparison with smaller arrays
         */
    }

	return 0;
}