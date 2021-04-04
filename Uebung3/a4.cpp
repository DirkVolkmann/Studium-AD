#include <iostream>
#include <iomanip>
#include <vector>

int FuncRec(unsigned int n, unsigned int m) {
	if (n == 0) {
		return m + 1;
	}
	else if (m == 0) {
		return FuncRec(n - 1, 1);
	}
	return FuncRec(n - 1, FuncRec(n, m - 1));
}

int FuncIte(unsigned int n, unsigned int m) {
	std::vector<unsigned int> stack_n;
	stack_n.push_back(n);
	do {
		if (n == 0) {
			n = stack_n.back();
			stack_n.pop_back();
			m++;
			continue;
		}
		else if (m == 0) {
			n--;
			m = 1;
			continue;
		}
		stack_n.push_back(n - 1);
		m--;
	} while (stack_n.size());
	return m;
}

/*int FuncIte(unsigned int n, unsigned int m) {
	std::vector<unsigned int> stack_n, stack_m;
	stack_n.push_back(n);
	stack_m.push_back(m);
	do {
		n = stack_n.back();
		stack_n.pop_back();
		m = stack_m.back();
		stack_m.pop_back();
		if (n == 0) {
			stack_m.push_back(m + 1);
			continue;
		}
		else if (m == 0) {
			stack_n.push_back(n - 1);
			stack_m.push_back(1);
			continue;
		}
		stack_n.push_back(n - 1);
		stack_n.push_back(n);
		stack_m.push_back(m - 1);
	} while (stack_n.size());
	return stack_m.back();
}*/

int main() {
	for (unsigned int i = 0; i < 100; i++) {
		for (unsigned int j = 0; j < 10; j++) {
			std::cout << "f(" << i << ',' << j << ") = ";
			//std::cout << FuncRec(i, j) << std::endl;
			std::cout << FuncIte(i, j) << std::endl;
		}
	}
	//std::cout << FuncIte(4, 1) << std::endl;
	//std::cout << FuncRec(4, 1) << std::endl;

	return 0;
}