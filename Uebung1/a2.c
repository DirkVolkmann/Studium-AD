#include <stdio.h>
#include <stdlib.h>

void checkPrimeTo(int k) {
    char prime;
    int col = 1;
    
    // geraden Sonderfall ausgeben
    if ( k >= 2 ) {
        printf("%5d", 2);
        col++;
    }

    // jetzt müssen nur noch ungerade Zahlen geprüft werden
    for (int i = 3; i <= k; i+=2) {
        // Es wird von einer Primzahl ausgegangen
        // und versucht diese Annahme zu widerlegen
        prime = 1;
        for (int j = 3; j < i; j+=2) {
            if (i % j == 0) {
                prime = 0;
                break;
            }
        }
        // bei gefundener Primzahl folgt die Ausgabe
        if (prime == 1) {
            if (col == 1) {
                printf("%5d", i);
                col++;
            }
            else if (col == 10) {
                printf(", %5d\n", i);
                col = 1;
            }
            else {
                printf(", %5d", i);
                col++;
            }
        }
    }
}

int main() {
    int k = 100000;
    
    printf("Finde Primzahlen bis %d...\n", k);
    checkPrimeTo(k);

    return 0;
}