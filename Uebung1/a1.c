#include <stdio.h>
#include <stdlib.h>

// größter gemeinsamer Teiler
int ggT(int x, int y) {
    while(x != y) {
        if(x > y) {
            x -= y;
        }
        else {
            y -= x;
        }
    }
    return x;
}

// größter gemeinsamer Teiler rekursiv
// vermutlich langsamer als ggT
int ggTrek(int x, int y) {
    if(x != y) {
        if(x > y) {
            x -= y;
        }
        else {
            y -= x;
        }
        return ggTrek(x, y);
    }
    return x;
}

// kleinstes gemeinsames Vielfaches
int kgV(int x, int y) {
    int a = x;
    int b = y;
    while(x != y) {
        if(x < y) {
            x += a;
        }
        else {
            y += b;
        }
    }
    return x;
}

int main() {
    
    for(int a = 30; a <= 40; a++) {
        for(int b = 30; b <= 40; b++) {
            printf("a = %d, b = %d\n", a, b);
            printf("ggT: %d\n", ggT(a, b));
            printf("ggT: %d (rekursiv)\n", ggTrek(a, b));
            printf("kgV: %d\n", kgV(a, b));
            printf("a*b: %d\n\n", a*b); // gleich ggT*kgV
        }
    }
    
    return 0;
}