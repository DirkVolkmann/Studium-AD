#include <iostream>

void hashLinear(int *hash, int hash_size, int *values, int values_size) {
    for (int i = 0; i < values_size; i++) {
        int value = values[i];
        int index = value % hash_size;
        while (1) {
            if (hash[index] == -1) {
                hash[index] = value;
                break;
            }
            index = ++index % hash_size;
        }
    }
}

void hashQuadratic(int *hash, int hash_size, int *values, int values_size) {
    const int c1 = 1;
    const int c2 = 3;

    for (int i = 0; i < values_size; i++) {
        int value = values[i];
        int index = value;
        int multi = 0;
        while (1) {
            index = (value + c1 * multi + c2 * multi * multi) % hash_size;
            if (hash[index] == -1) {
                hash[index] = value;
                break;
            }
            multi++;
        }
    }
}

inline int h1(int s) {
    return s;
}

inline int h2(int s, int m) {
    return 1 + (s % (m - 1)); // Aufgabe
}

void hashDouble(int *hash, int hash_size, int *values, int values_size) {
    for (int i = 0; i < values_size; i++) {
        int value = values[i];
        int index = value;
        int multi = 0;
        while (1) {
            index = (h1(value) + multi * h2(value, hash_size)) % hash_size;
            if (hash[index] == -1) {
                hash[index] = value;
                break;
            }
            multi++;
        }
    }
}

void printHash(int *hash, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << hash[i];
        if (i == size - 1) std::cout << std::endl;
        else std::cout << " | ";
    }
}

int main() {
    const int size_values = 9;
    int values[] = {10,22,31,4,15,28,17,88,59};
    
    const int size_hash = 11;
    int hash1[size_hash];
    int hash2[size_hash];
    int hash3[size_hash];

    for (int i = 0; i < size_hash; i++) {
        hash1[i] = -1;
        hash2[i] = -1;
        hash3[i] = -1;
    }

    hashLinear(hash1, size_hash, values, size_values);
    hashQuadratic(hash2, size_hash, values, size_values);
    hashDouble(hash3, size_hash, values, size_values);

    std::cout << "Linear:" << std::endl;
    printHash(hash1, size_hash);
    std::cout << "Quardratisch:" << std::endl;
    printHash(hash2, size_hash);
    std::cout << "Doppelt:" << std::endl;
    printHash(hash3, size_hash);
}