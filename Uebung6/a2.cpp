#include <iostream>
#include "linkedlist.h"

int main() {
    LinkedList<int> myll;

    myll.Append(10);
    myll.Append(13);
    myll.Append(11);
    myll.Append(12);

    myll.Print();
    myll.QuickSort();
    myll.Print();

	return 0;
}