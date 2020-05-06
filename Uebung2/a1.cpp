#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

#define ADD 0x01
#define SUB 0x02
#define MUL 0x03
#define DIV 0x04
#define LDA 0x05
#define LDK 0x06
#define STA 0x07
#define INP 0x08
#define OUT 0x09
#define HLT 0x0A
#define JMP 0x0B
#define JEZ 0x0C
#define JNE 0x0D
#define JLZ 0x0E
#define JLE 0x0F
#define JGZ 0x10
#define JGE 0x11

#define MEM_SIZE 256

#define VAL_TO_PC(val) ((val - 1) * 4)

int main() {
    string s, test;
    int command, value, pc = 0, akku = 0, memory[MEM_SIZE] = {0};
    char done = 0;

    // Datei einlesen
    ifstream file;
    file.open("a1.txt");
    file >> s;
    file.close();

    // ASCII in Integer umwandeln
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            s[i] -= '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            s[i] -= ('a' - 10);
        else if (s[i] >= 'A' && s[i] <= 'F')
            s[i] -= ('A' - 10);
    }

    while (!done) {
        // Befehl und Wert aus Programm lesen
        command = (s[pc]) * 16 + (s[pc + 1]);
        value = (s[pc + 2]) * 16 + (s[pc + 3]);

        // Ausgabe der aktuellen Zeile, Befehl und Wert
        cout << dec << pc/4+1 << ": " << hex << command  << " " << value << endl << dec;

        // Verarbeitung der Befehle
        switch (command) {
            case ADD: akku += memory[value]; break;
            case SUB: akku -= memory[value]; break;
            case MUL: akku *= memory[value]; break;
            case DIV: akku /= memory[value]; break;
            case LDA: akku = memory[value]; break;
            case LDK: akku = value; break;
            case STA: memory[value] = akku; break;
            case INP: cout << "In: "; cin >> memory[value]; break;
            case OUT: cout << "Out: " << memory[value] << endl; break;
            case HLT: done = 1; break;
            case JMP: pc = VAL_TO_PC(value); continue;
            case JEZ: if (akku == 0) { pc = VAL_TO_PC(value); continue; } else break;
            case JNE: if (akku != 0) { pc = VAL_TO_PC(value); continue; } else break;
            case JLZ: if (akku <  0) { pc = VAL_TO_PC(value); continue; } else break;
            case JLE: if (akku <= 0) { pc = VAL_TO_PC(value); continue; } else break;
            case JGZ: if (akku >  0) { pc = VAL_TO_PC(value); continue; } else break;
            case JGE: if (akku >= 0) { pc = VAL_TO_PC(value); continue; } else break;
        }
        // Programm-Counter hochzählen
        pc += 4;
    }

    return 0;
}