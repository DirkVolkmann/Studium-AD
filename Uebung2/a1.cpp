#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <vector>

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

// Speicheradresse zu Programcounter
#define ADDR_TO_PC(val) ((val - 1) * 4)
// Programcounter zu Speicheradresse
#define PC_TO_ADDR(pc) (pc / 4 + 1)

// Jedes Element eines String von ASCII in Integer umwandeln
void string_ascii_to_int(std::string *s) {
	for (int i = 0; i < s->length(); i++) {
		if (s->at(i) >= '0' && s->at(i) <= '9')
			s->at(i) -= '0';
		else if (s->at(i) >= 'a' && s->at(i) <= 'f')
			s->at(i) -= ('a' - 10);
		else if (s->at(i) >= 'A' && s->at(i) <= 'F')
			s->at(i) -= ('A' - 10);
	}
}

// Klasse um "endlosen" Speicher zu simulieren
class Memory {
	private:
		std::vector<int> _data;
		void _make_address_save(unsigned int);
	public:
		int get_value(unsigned int);
		template<typename T>
		void set_value(T, unsigned int);
		void set_value(int&, unsigned int);
		void set_value(std::istream&, unsigned int);
};

// Benötigten Speicher für beliebige Adresse allokieren
void Memory::_make_address_save(unsigned int address) {
	if (address >= _data.size()) {
		_data.resize(address + 1);
	}
}

// Wert aus dem Speicher lesen
int Memory::get_value(unsigned int address) {
	// Gibt std::out_of_range Fehler, wenn Speicher nicht zugewiesen ist
	return _data.at(address);
}

// Wert in den Speicher schreiben
void Memory::set_value(int& value, unsigned int address) {
	_make_address_save(address);
	_data[address] = value;
}


// Wert aus stdin lesen und in den Speicher schreiben
void Memory::set_value(std::istream& stream, unsigned int address) {
	int value;
	stream >> value;
	set_value(value, address);
}

int main() {
	// Speicher für eingelesenes Programm
	std::string prog;
	// "Endloser" Speicher für Variablen des Programms
	Memory memory;
	// Akkumulator/Register für Rechenergebnisse
	int akku = 0;
	// Programm-Counter
	int pc = 0;
	// Aktueller Befehl
	int command = HLT;
	// Aktueller Wert
	int value = 0x99;

	// Programm aus Datei einlesen
	std::ifstream file;
	file.open("a1.txt");
	file >> prog;
	file.close();
	string_ascii_to_int(&prog);

	// Überschrift für Ausgabe
	// add. = address (dec),
	// com. = command (hex),
	// val. = value (hex)
	std::cout << "add. com. val." << std::endl;

	while (1) {
		// Befehl und Wert aus Programm lesen
		command = (prog[pc]) * 16 + (prog[pc + 1]);
		value = (prog[pc + 2]) * 16 + (prog[pc + 3]);

		// Ausgabe der aktuellen Zeile, Befehl und Wert
		std::cout << std::setfill('0') << std::setw(3) << std::dec << PC_TO_ADDR(pc) << ": 0x"
			<< std::setw(2) << std::hex << command << " 0x"
			<< std::setw(2) << std::hex << value << std::endl << std::dec;

		// Verarbeitung der Befehle
		switch (command) {
			// Addition (Akku + Mem)
			case ADD:
				akku += memory.get_value(value);
				break;
			// Subtraktion (Akku + Mem)
			case SUB:
				akku -= memory.get_value(value);
				break;
			// Multiplikation (Akku * Mem)
			case MUL:
				akku *= memory.get_value(value);
				break;
			// Division (Akku / Mem)
			case DIV:
				akku /= memory.get_value(value);
				break;
			// Wert laden (Akku = Mem)
			case LDA:
				akku = memory.get_value(value);
				break;
			// Wert laden (Akku = Const)
			case LDK:
				akku = value;
				break;
			// Wert speichern (Mem = Akku)
			case STA:
				memory.set_value(akku, value);
				break;
			// Eingabe aus stdin in Mem speichern (dezimal)
			case INP:
				std::cout << " in: ";
				memory.set_value(std::cin, value);
				break;
			// Ausgabe von Mem nach stdout (dezimal)
			case OUT:
				std::cout << "out: " << memory.get_value(value) << std::endl;
				break;
			// Programm beenden
			case HLT:
				return 0;
				break;
			// Sprung zu Adresse (ohne Kondition)
			case JMP:
				pc = ADDR_TO_PC(value);
				continue;
			// Sprung zu Adresse (Akku ist 0)
			case JEZ:
				if (akku == 0) {
					pc = ADDR_TO_PC(value);
					continue;
				}
				break;
			// Sprung zu Adresse (Akku nicht 0)
			case JNE:
				if (akku != 0) {
					pc = ADDR_TO_PC(value);
					continue;
				}
				break;
			// Sprung zu Adresse (Akku ist negativ)
			case JLZ:
				if (akku <  0) {
					pc = ADDR_TO_PC(value);
					continue;
				}
				break;
			// Sprung zu Adresse (Akku <= 0)
			case JLE:
				if (akku <= 0) {
					pc = ADDR_TO_PC(value);
					continue;
				}
				break;
			// Sprung zu Adresse (Akku größer 0)
			case JGZ:
				if (akku >  0) {
					pc = ADDR_TO_PC(value);
					continue;
				}
				break;
			// Sprung zu Adresse (Akku >= 0)
			case JGE:
				if (akku >= 0) {
					pc = ADDR_TO_PC(value);
					continue;
				}
				break;
		}
		// Programm-Counter hochzählen
		pc += 4;
	}

	return 0;
}