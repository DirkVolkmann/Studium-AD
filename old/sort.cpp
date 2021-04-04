#include <bits/stdc++.h>
using namespace std;

#define CLOCKS_TO_SECS(clocks) ((double)(clocks)/CLOCKS_PER_SEC)
#define N 150000
#define N_FACTOR (N > 10000 ? 1000 : 1)
#define N_SMALL (N/N_FACTOR)

// Allgemeine Hilfsfunktion
void generateRandomArray(int a[], int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        a[i] = rand() % 1999 - 1000;
    }
}

void printArray(int a[], int length) {
    for (int i = 0; i < length; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void printTime(clock_t c) {
    cout << "Takte: " << c << endl;
    cout << "Dauer: " << CLOCKS_TO_SECS(c) << " Sekunden" << endl;
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// Bubble Sort
void bubbleSort(int a[], int length) {
    int i, j, tmp;
    for (i = 0; i < length - 1; i++) {
        for (j = 0; j < length - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// Quick Sort
int partition (int a[], int low, int high) {  
    int pivot = a[high];
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++) {  
        if (a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int part_index = partition(a, low, high);
        quickSort(a, low, part_index - 1);
        quickSort(a, part_index + 1, high);
    }
}

// Main
int main() {
    int array_b[N], array_q[N];
    clock_t takte;
    double seconds, actions;
    unsigned long long int actions_per_min, sorts_per_min;

    //cout << "Array generieren: ";
    generateRandomArray(array_b, N);
    //printArray(array_b, N);
    copy(begin(array_b), end(array_b), begin(array_q));

    cout << "Sortieren von " << N << " Zahlen..." << endl;

    /*
        Berechnung der Sortierungen pro Minute:
        - Über average case Formel die ausgeführten Aktionen berechnen
        - Rechne hoch auf Aktionen pro Minute
        - Formel umkehren und zurück auf sortierte Elemente
    */

    // Quick Sort
    cout << "Quick Sort" << endl;
    takte = clock();
    quickSort(array_q, 0, N - 1);
    takte = clock() - takte;
    printTime(takte);
    // average case O(n*log(n))
    actions = N_SMALL * log(N_SMALL);                           // ausgeführte Aktionen (average case)
    actions_per_min = actions * (60/CLOCKS_TO_SECS(takte));     // Aktionen pro Minute
    sorts_per_min = pow(2, (actions_per_min/N_SMALL));          // Sortierungen pro Minute
    sorts_per_min *= N_FACTOR;
    cout << "Sortierungen pro Minute: " << sorts_per_min  << endl;

    // Bubble Sort
    cout << "Bubble Sort" << endl;
    takte = clock();
    bubbleSort(array_b, N);
    takte = clock() - takte;
    printTime(takte);
    // average case O(n^2)
    actions = N_SMALL * N_SMALL;                                // ausgeführte Aktionen (average case)
    actions_per_min = actions * (60/CLOCKS_TO_SECS(takte));     // Aktionen pro Minute
    sorts_per_min = sqrt(actions_per_min);                      // Sortierungen pro Minute
    sorts_per_min *= N_FACTOR;
    cout << "Sortierungen pro Minute: " << sorts_per_min  << endl;

    return 0;
}