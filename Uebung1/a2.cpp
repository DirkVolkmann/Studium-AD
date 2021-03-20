#include <stdio.h>
#include <stdlib.h>
#include <vector>

void sieve(int k) {
    std::vector<char> a(k);
    std::fill(a.begin(), a.end(), 1);
    a[0] = 0;
    for (int i = 1; i < k; i++) {
        if (a[i] == 0) {
            continue;
        }
        int i_val = i+1;
        for (int j=i+i_val; j<k; j+=i_val) {
            a[j] = 0;
        }
    }
    // Ausgabe der Tabelle
    for (int i = 0; i < k; i++) {
        int i_val = i+1;
        printf("%6d:%d | ", i_val, a[i]);
        if ((i_val)%10 == 0) {
            printf("\n");
        }
    }
}

int main() {
    int k = 100000;
    
    printf("Finde Primzahlen bis %d...\n", k);
    sieve(k);

    return 0;
}